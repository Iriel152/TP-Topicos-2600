#include "Mapa.h"
#include "Comunes.h"
#include "PJ_Principal.h"
Mapa* Mapa_CrearMapa(int filas, int columnas)
{
    int i, j;
    Mapa* m = (Mapa*)malloc(sizeof(Mapa));
    if(!m)
        return NULL;
    m->filas = filas;
    m->columnas = columnas;
    m->celdas = (int**)malloc(filas * sizeof(int*));
    if(!m->celdas)
    {
        free(m);
        return NULL;
    }
    for(i=0; i<filas ; i++)
    {
        m->celdas[i] = (int*)malloc(columnas * sizeof(int));
        if(!m->celdas[i])
        {
            for(j=0 ; j<i; j--)
                free(m->celdas[j]);
            free(m->celdas);
            free(m);
        }
        for(j=0 ; j<columnas ; j++)
            m->celdas[i][j] = VACIO;
    }
    return m;
}
void Mapa_DestruirMapa(Mapa *p)
{
    int i;
    if(!p)
        return;
    for(i=0 ; i<p->filas; i++)
        free(p->celdas[i]);
    free(p->celdas);
    free(p);
}
void Mapa_RellenoObstaculos(Mapa *p)
{
    int i, j;
    for(j=0; j < p->columnas; j++)
    {
        if(j == 0 || j == p->columnas - 1)
        {
            p->celdas[0][j] = PARED;
            p->celdas[p->filas - 1][j] = PARED;
        }
        else
        {
            p->celdas[0][j] = TECHO;
            p->celdas[p->filas - 1][j] = PISO;
        }
    }
    for (i = 1; i < p->filas - 1; i++)
    {
        p->celdas[i][0] = PARED;
        p->celdas[i][p->columnas - 1] = PARED;
    }
    for (i = 1; i < p->filas - 1; i++)
        for (j = 1; j < p->columnas - 1; j++)
        {
            if((i % 2 == 0) && (j % 2 == 0))
                p->celdas[i][j] = OBSTACULO;
            else
                if(rand() % 10 < 4)
                    p->celdas[i][j] = ROMPIBLE;
        }
}
