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
void PJ_Principal_AparicionRandom(Personaje *p, int fil, int col)
{
    int esquina = ObtenerNumeroAleatorio(1,4);
    if(!p)
        return NULL;
    switch(esquina)
    {
        case 1:
            p->pos.x = 1;
            p->pos.y = 1;
            break;
        case 2:
            p->pos.x = fil - 2;
            p->pos.y = 1;
            break;
        case 3:
            p->pos.x = 1;
            p->pos.y = col - 2;
            break;
        case 4:
            p->pos.x = fil - 2;
            p->pos.y = col - 2;
            break;
    }
}
