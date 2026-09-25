#include "PJ_Principal.h"
#include "Mapa.h"
#define SEGUIR 1
#define SALIR 0
#define AMAYUSCULA(X) ((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X)

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
            break;
        case 2:
            p->pos.x = m->filas - 2;
            p->pos.y = 1;
            break;
        case 3:
            p->pos.x = 1;
            p->pos.y = m->columnas - 2;
            break;
        case 4:
            p->pos.x = m->filas - 2;
            p->pos.y = m->columnas - 2;
            break;
    }
}

void LimpiarLadosPJ(Mapa *m, Personaje *p)
{
    int* arriba = &m->celdas[p->pos.x-1][p->pos.y];
    int* abajo = &m->celdas[p->pos.x+1][p->pos.y];
    int* izquierda = &m->celdas[p->pos.x][p->pos.y-1];
    int* derecha = &m->celdas[p->pos.x][p->pos.y+1];

    m->celdas[p->pos.x][p->pos.y] = VACIO;

    if(*arriba != PARED && *arriba != TECHO && *arriba != PISO)
    {
        *arriba = VACIO;
    }
    if(*abajo != PARED && *abajo != TECHO && *abajo != PISO)
    {
        *abajo = VACIO;
    }
    if(*izquierda != PARED && *izquierda != TECHO && *izquierda != PISO)
    {
        *izquierda = VACIO;
    }
    if(*derecha != PARED && *derecha != TECHO && *derecha != PISO)
    {
        *derecha = VACIO;
    }
}

void NuevaPosicionPJ(Mapa *m, Personaje *p, int NuevaPosX, int NuevaPosY)
{
    if(m->celdas[NuevaPosX][NuevaPosY] == VACIO)
    {
        p->pos.x = NuevaPosX;
        p->pos.y = NuevaPosY;
    }
}

int MovimientoPJ(Mapa *m, Personaje *p)
{
    char tecla = _getch();

    tecla = AMAYUSCULA(tecla);

    switch(tecla)
    {
        case 'W': NuevaPosicionPJ(m,p,p->pos.x-1,p->pos.y); return SEGUIR; break;
        case 'S': NuevaPosicionPJ(m,p,p->pos.x+1,p->pos.y); return SEGUIR; break;
        case 'A': NuevaPosicionPJ(m,p,p->pos.x,p->pos.y-1); return SEGUIR; break;
        case 'D': NuevaPosicionPJ(m,p,p->pos.x,p->pos.y+1); return SEGUIR; break;
        case 27: return SALIR; break;
        default: return SEGUIR; break;
    }
}
