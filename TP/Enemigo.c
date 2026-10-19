#include "Enemigo.h"
#include "Mapa.h"
#include "PJ_Principal.h"

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
void ValidarEspacio(tMapa *m, tPersonaje *p, tVector *v_enemigo, int limite,
                    int *fila, int *columna)
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
    }while(m->celdas[*fila][*columna] != DM_VACIO ||
           (*columna == x && *fila == y) ||superpuesto == 1);
}
void EnemigoMovimientoxTiempo(DWORD ahora, tVector *v, tMapa *mapa,
                              DWORD *tiempo_enemigo, tPersonaje *p)
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
