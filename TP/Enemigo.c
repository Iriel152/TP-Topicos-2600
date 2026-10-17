#include "Enemigo.h"
void Enemigo_RellenarVec(tVector *v, int cant)
{
    int i;
    tEnemigo enemigo;

    enemigo.pos.x = 0;
    enemigo.pos.y = 0;
    enemigo.direccion = 0;
    enemigo.esta_vivo = E_VIVO;
    enemigo.velocidad = 600;
    enemigo.valor = 200;
    enemigo.rebotes = 3;
    enemigo.lado = 0;

    for(i = 0 ; i < cant ; i++)
        Comunes_InsertarVector(v, &enemigo);
}
void Enemigo_AparicionRandom(tMapa *m, tVector *v, tPersonaje *p)
{
    int fila, columna, i;
    tEnemigo *enemigo;
    enemigo = (tEnemigo*)v->vec;

    for(i = 0 ; i < v->ce ; i++)
    {
        ValidarEspacio(m, p, v, i, &fila, &columna);
        (enemigo + i)->pos.x = columna;
        (enemigo + i)->pos.y = fila;
    }
}
void ValidarEspacio(tMapa *m, tPersonaje *p, tVector *v_enemigo, int limite, int *fila, int *columna)
{
    int x, y, i, superpuesto;
    tEnemigo *enemigo;

    x = p->pos.x;
    y = p->pos.y;

    enemigo = (tEnemigo*)v_enemigo->vec;

    do
    {
        superpuesto = 0;
        *fila = Comunes_ObtenerNumeroAleatorio(1, m->filas - 2);
        *columna = Comunes_ObtenerNumeroAleatorio(1, m->columnas - 2);

        for(i = 0 ; i < limite ; i++)
        {
            if((enemigo + i)->pos.x == *columna && (enemigo + i)->pos.y == *fila)
            {
                superpuesto = 1;
                break;
            }
        }
    }while(m->celdas[*fila][*columna] != DM_VACIO || (*columna == x && *fila == y) || superpuesto == 1);
}
void EnemigoMovimientoxTiempo(DWORD ahora, tVector *v, tMapa *mapa, DWORD *tiempo_enemigo, tPersonaje *p)
{
    int i, movimiento;
    tEnemigo *enemigo;

    enemigo = (tEnemigo*)v->vec;
    movimiento = 0;

    for(i = 0 ; i < v->ce ; i++)
    {
        if(ahora - (*tiempo_enemigo) >= (enemigo + i)->velocidad &&
           (enemigo + i)->esta_vivo == E_VIVO)
        {
            Enemigo_Direccion(enemigo + i);
            Enemigo_MoverRandom(mapa, enemigo + i, p, v);
            Enemigo_DanioaPJ(enemigo + i, p, ahora);
            movimiento = 1;
        }
    }
    if(movimiento == 1)
        *tiempo_enemigo = ahora;
}
void Enemigo_Direccion(tEnemigo *enemigo)
{
    if(enemigo->direccion == 0)
    {
        enemigo->direccion = Comunes_ObtenerNumeroAleatorio(1,2);
        enemigo->lado = Comunes_ObtenerNumeroAleatorio(1,2);
    }

    if(enemigo->rebotes <= 0)
    {
        if(enemigo->direccion == 1)
            enemigo->direccion = 2;
        else
            enemigo->direccion = 1;

        enemigo->rebotes = 4;
    }
}
void Enemigo_MoverRandom(tMapa *mapa, tEnemigo *enemigo, tPersonaje *personaje, tVector *v)
{
    int nuevaFila, nuevaColumna;

    nuevaColumna = enemigo->pos.x;
    nuevaFila = enemigo->pos.y;

    if (enemigo->direccion == 1)
    {
        if (enemigo->lado == 1)
            nuevaColumna--;
        else
            nuevaColumna++;
    }
    else if (enemigo->direccion == 2)
    {
        if (enemigo->lado == 1)
            nuevaFila--;
        else
            nuevaFila++;
    }
    if(Mapa_MovimientoValido(mapa, nuevaFila, nuevaColumna, 0) == TODOOK &&
       Enemigo_ColisionEnemigos(v, enemigo, nuevaFila, nuevaColumna) == NO_ENCONTRADO)
    {
        enemigo->pos.x = nuevaColumna;
        enemigo->pos.y = nuevaFila;
    }else
    {
        enemigo->rebotes--;
        if(enemigo->lado == 1)
            enemigo->lado = 2;
        else
            enemigo->lado = 1;
    }
}
int Enemigo_ColisionEnemigos(tVector *v, tEnemigo *enemigo_actual, int fila, int columna)
{
    int i;
    tEnemigo *enemigos = (tEnemigo*)v->vec;

    for(i = 0 ; i < v->ce ; i++)
    {
        if((enemigos + i) != enemigo_actual &&
           (enemigos + i)->esta_vivo == E_VIVO)
        {
            if((enemigos + i)->pos.y == fila &&
               (enemigos + i)->pos.x == columna)
                return ENCONTRADO;
        }
    }
    return NO_ENCONTRADO;
}
void Enemigo_DanioaPJ(tEnemigo *enemigo, tPersonaje *personaje, DWORD ahora)
{
    int distancia_x, distancia_y;

    if(personaje->esta_vivo == E_INMORTAL)
        return;

    distancia_x = enemigo->pos.x - personaje->pos.x;
    distancia_y = enemigo->pos.y - personaje->pos.y;

    if(distancia_x == 0 && distancia_y == 0)
    {
        personaje->vidas--;
        personaje->esta_vivo = E_INMORTAL;
        personaje->invul = ahora;
    }
}
//void explotar_bomba(tMapa *m, int x, int y, int rango, tPuerta *puerta, tVector *v, tPersonaje *pj, DWORD ahora)
//{
//    int i, j,k, aux_x, aux_y;
//    int dir_x[] = {-1,1,0,0};
//    int dir_y[] = {0,0,-1,1};
//    tEnemigo *enemigo;
//
//    enemigo = (tEnemigo*)v->vec;
//
//    for (i = 0 ; i < 4 ; i++)
//    {
//        for(j = 1; j <= rango; j++)
//        {
//            aux_x = x + (j * dir_x[i]);
//            aux_y = y + (j * dir_y[i]);
//            if(aux_x < 0 || aux_y < 0 || aux_y >= m->filas || aux_x >= m->columnas) //chequeamos bordes
//                break;             // no me gusta usar break, le voy a preguntar. Si lo tengo q hacer con bandera
//            if(m->celdas[aux_y][aux_x] == DM_PARED || m->celdas[aux_y][aux_x] == DM_OBSTACULO)
//                break;
//            if(m->celdas[aux_y][aux_x] == DM_ROMPIBLE)
//            {
//                if(puerta->estado_puerta == E_ACTIVAR)
//                {
//                    m->celdas[aux_y][aux_x] = D_PUERTA;
//                    puerta->estado_puerta = E_ACTIVA;
//                }else
//                    {
//                        m->celdas[aux_y][aux_x] = DM_VACIO;
//                    }
//                break;
//            }
//            if(enemigo != NULL)
//            {
//                for(k = 0 ; k < v->ce ; k++)
//                {
//                     if((enemigo + k)->esta_vivo == E_VIVO &&
//                        (enemigo + k)->pos.x == aux_x
//                        && (enemigo + k)->pos.y == aux_y)
//                    {
//                        (enemigo + k)->esta_vivo = E_MUERTO;
//                        pj->puntaje += 270;
//                        (enemigo + k)->pos.x =0;
//                        (enemigo + k)->pos.y = 0;
//                    }
//                }
//            }
//            if(pj!=NULL && pj->pos.x == aux_x && pj->pos.y == aux_y)
//            {
//                pj->vidas--;
//                pj->esta_vivo = E_INMORTAL;
//                pj->invul = ahora;
//            }
//
//            if(m->celdas[aux_y][aux_x] == DM_VACIO)
////               if(m->celdas[aux_y][aux_x] != DM_TECHO && m->celdas[aux_y][aux_x] != DM_PISO)  //Detectar q la estela no haya muro
//                    m->celdas[aux_y][aux_x] = D_EXPLOSION; //esto es como muestra, el tema es q no borra la estela.
//        }
//    }
//}
