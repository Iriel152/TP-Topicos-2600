#include "Bomba.h"
void Bomba_RellenarVec(tVector *v, int cant)
{
    int i;
    tBomba bomba;

    bomba.activa = E_DESACTIVADA;
    bomba.explosion = E_DESACTIVADA;
    bomba.pos.x = 0;
    bomba.pos.y = 0;
    bomba.rango = 1;
    bomba.tiempo_bomba = 0;

    for(i = 0 ; i < cant ; i++)
        Comunes_InsertarVector(v, &bomba);
}
int Bomba_Existencia(tVector *v, int x, int y)
{
    int i;
    tBomba *bomba;

    bomba = (tBomba*)v->vec;

    for(i = 0 ; i < v->ce ; i++)
    {
        if((bomba + i)->activa == 1 &&
           (bomba + i)->pos.x == x &&
           (bomba + i)->pos.y == y)
            return ENCONTRADO;
    }
    return NO_ENCONTRADO;
}
////FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE NO LIMPIA DEL MAPA LA BOMBA
////FALTA FUNCION BORRAR BOMBA LO TENGO AHI TODO METIDO. EN EL MOMENTO Q BORRA LA BOMBA EPLOTA
void actualizar_bomba(tVector *vec_e,tMapa *m, DWORD ahora, tPuerta *puerta, tVector *enemigos, tPersonaje *pj, tVector *vec_p)
{
    int i;
    tBomba *bomba;
    DWORD RELOJ_BOMBA = 3000;

    if (!vec_e)
        return;

    bomba = (tBomba*)vec_e->vec;

    for(i = 0 ; i < vec_e->ce ; i++)
    {
        if((bomba + i)->activa == E_ACTIVAR)
        {
            if(ahora - (bomba + i)->tiempo_bomba >= RELOJ_BOMBA)
            {
                explotar_bomba(m, (bomba + i),puerta, enemigos, pj, ahora, vec_p);

                (bomba + i)->activa = E_ACTIVA;
                (bomba + i)->tiempo_bomba = ahora;
            }

        }
        else
            if((bomba + i)->activa == E_ACTIVA)
            {
                if(ahora - (bomba + i)->tiempo_bomba >= 300) //300 ms de retardo
                {

                    limpiar_estela(m, (bomba + i), pj->alcance_bomba);

                    (bomba + i)->activa = E_DESACTIVADA;
                    (bomba + i)->pos.x = -1;
                    (bomba + i)->pos.y = -1;
                }
        }
    }
}



void explotar_bomba(tMapa *m, tBomba *b, tPuerta *puerta, tVector *v_en, tPersonaje *pj, DWORD ahora, tVector *vec_p)
{
    int i, j,/*k,*/ aux_x, aux_y;
    int dir_x[] = {-1,1,0,0};
    int dir_y[] = {0,0,-1,1};

//    tEnemigo *enemigo;
//    enemigo = (tEnemigo*)v_en->vec;

    m->celdas[b->pos.y][b->pos.x] = D_EXPLOSION;  //dibuja el centro
    if(pj != NULL && pj->pos.x == b->pos.x && pj->pos.y == b->pos.y) //chequea si esta en el centro
    {
        if(pj->esta_vivo == E_VIVO)
       {
            pj->vidas--;
            pj->esta_vivo = E_INMORTAL;
            pj->invul = ahora;
       }
    }

    for (i = 0 ; i < 4 ; i++)
    {
        for(j = 1; j <= pj->alcance_bomba; j++)
        {
            aux_x = (b->pos.x) + (j * dir_x[i]);
            aux_y = (b->pos.y) + (j * dir_y[i]);
            if(aux_x < 0 || aux_y < 0 || aux_y >= m->filas || aux_x >= m->columnas) //chequeamos bordes
                break;
            if(m->celdas[aux_y][aux_x] == DM_PARED || m->celdas[aux_y][aux_x] == DM_OBSTACULO)
                break;
            if(m->celdas[aux_y][aux_x] == DM_ROMPIBLE)
            {
                if(ProcesarRompible(m, aux_x, aux_y, puerta, vec_p) == ERROR_) //ERROR_ PORQ SIGNIFICA Q AHI HAY QUE CORTAR CICLO
                    break;
            }
            control_vec_enemigo(v_en, aux_x, aux_y, pj);

            if(pj!=NULL && pj->pos.x == aux_x && pj->pos.y == aux_y)
            {
                if(pj->esta_vivo == E_VIVO)
               {
                    pj->vidas--;
                    pj->esta_vivo = E_INMORTAL;
                    pj->invul = ahora;
                }
                break;
            }


            if(m->celdas[aux_y][aux_x] == DM_VACIO ||
               m->celdas[aux_y][aux_x] == D_MASRANGO ||
               m->celdas[aux_y][aux_x] == D_MASBOMBA)
               if(m->celdas[aux_y][aux_x] != DM_TECHO && m->celdas[aux_y][aux_x] != DM_PISO)  //Detectar q la estela no haya muro
                    m->celdas[aux_y][aux_x] = D_EXPLOSION; //esto es como muestra, el tema es q no borra la estela.
        }
    }
}



void limpiar_estela(tMapa *m, tBomba *b, int rango)
{
    int i, j, aux_x, aux_y;
    int dir_x[] = {-1,1,0,0};
    int dir_y[] = {0,0,-1,1};

    if(m->celdas[b->pos.y][b->pos.x] == D_EXPLOSION)
        m->celdas[b->pos.y][b->pos.x]= DM_VACIO;

    for (i=0 ; i<4 ; i++)
    {
        for(j=1; j<=rango; j++)
        {
            aux_x = b->pos.x + (j * dir_x[i]);
            aux_y = b->pos.y + (j * dir_y[i]);
            if((aux_x < 0) || (aux_y < 0) || (aux_y >= m->filas) || (aux_x >= m->columnas))
                break;
            if(m->celdas[aux_y][aux_x] == DM_PARED || m->celdas[aux_y][aux_x] == DM_OBSTACULO)
                break;

            if(m->celdas[aux_y][aux_x] == D_EXPLOSION)
               m->celdas[aux_y][aux_x] = DM_VACIO;
        }
    }


}

void control_vec_enemigo(tVector *v_en, int x, int y, tPersonaje *p)
{
    int i;

    tEnemigo *enemigo;

    if(!v_en)
        return;

    enemigo = (tEnemigo*)v_en->vec;

    for(i=0 ; i < v_en->ce ; i++)
    {
        if((enemigo + i)->esta_vivo == 1 && (enemigo + i)->pos.x == x && (enemigo + i)->pos.y == y)
        {
            (enemigo + i)->esta_vivo = 0;
            p->puntaje += (enemigo + i)->valor;
            (enemigo + i)->pos.x = -1;
            (enemigo + i)->pos.y = -1;
        }
    }
}
int ProcesarRompible(tMapa *m, int x, int y, tPuerta *puerta, tVector* vec_p)
{
    if(puerta != NULL && puerta->estado_puerta == E_ACTIVAR)
    {
        m->celdas[y][x] = D_PUERTA;
        puerta->estado_puerta = E_ACTIVA;
        return ERROR_;
    }

    Potenciador_GenerarAleatorio(vec_p, m, x, y, GetTickCount());

    return ERROR_;
}

