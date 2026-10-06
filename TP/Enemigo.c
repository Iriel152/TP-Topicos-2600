#include "Enemigo.h"
Enemigo* Enemigo_Crear(int fila, int columna)
{
    Enemigo *e = (Enemigo*)malloc(sizeof(Enemigo));

    if(!e)
        return NULL;

    e->pos.x = fila;
    e->pos.y = columna;
    e->esta_vivo = 1;

    return e;
}

void Enemigo_Destruir(Enemigo *e)
{
    if(e)
        free(e);
}

void Enemigo_AparicionRandom(tMapa *m, Enemigo *e) //hay que mejorarla para que no se posicione encima de otro enemigo/del jugador
{
    int fila;
    int columna;

    do
    {
        fila = ObtenerNumeroAleatorio(1, m->filas - 2);
        columna = ObtenerNumeroAleatorio(1, m->columnas - 2);

    } while(m->celdas[fila][columna] != VACIO);

    e->pos.x = fila;
    e->pos.y = columna;
}
