#include "PJ_Principal.h"
#include "Mapa.h"
Personaje* PJ_Princial_CrearPersonaje(int fila, int col, int vidas)
{
    Personaje *p = (Personaje*)malloc(sizeof(Personaje));
    if(!p)
        return NULL;
    p->pos.x = fila;
    p->pos.y = col;
    p->vidas = vidas;
    p->alcance_bomba = 2;
    p->esta_vivo = 1;

    return p;
}
void PJ_Principal_DestruirPersonaje(Personaje *p)
{
    if(p)
        free(p);
}
void PJ_Principal_AparicionRandom(Mapa *m, Personaje *p)
{
    int esquina = ObtenerNumeroAleatorio(1,4);
    if(!p)
        return;// NULL;
    switch(esquina)
    {
        case 1:
            p->pos.x = 1;
            p->pos.y = 1;
            m->celdas[1][1] = VACIO;
            m->celdas[1][2] = VACIO;
            m->celdas[2][1] = VACIO;
            break;
        case 2:
            p->pos.x = m->filas - 2;
            p->pos.y = 1;
            m->celdas[m->filas-2][1] = VACIO;
            m->celdas[m->filas-3][1] = VACIO;
            m->celdas[m->filas-2][2] = VACIO;
            break;
        case 3:
            p->pos.x = 1;
            p->pos.y = m->columnas - 2;
            m->celdas[1][m->columnas-2] = VACIO;
            m->celdas[1][m->columnas-3] = VACIO;
            m->celdas[2][m->columnas-2] = VACIO;
            break;
        case 4:
            p->pos.x = m->filas - 2;
            p->pos.y = m->columnas - 2;
            m->celdas[m->filas-2][m->columnas-2] = VACIO;
            m->celdas[m->filas-2][m->columnas-3] = VACIO;
            m->celdas[m->filas-3][m->columnas-2] = VACIO;
            break;
    }
}
