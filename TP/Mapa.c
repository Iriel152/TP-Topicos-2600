#include "Mapa.h"
tMapa* Mapa_CrearMapa(int filas, int columnas)
{
    int i, j;
    tMapa *m;

    m = (tMapa*)malloc(sizeof(tMapa));
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
    for(i = 0; i < filas ; i++)
    {
        *(m->celdas + i) = (int*)malloc(columnas * sizeof(int));
        if(!*(m->celdas + i))
        {
            while(i > 0)
            {
                i--;
                free(*(m->celdas + i));
            }
            free(m->celdas);
            free(m);
            return NULL;
        }
        for(j = 0 ; j < columnas ; j++)
            *(*(m->celdas + i) + j) = DM_VACIO;
    }
    return m;
}
void Mapa_DestruirMapa(tMapa *m)
{
    int i;

    if(!m)
        return;

    for(i = 0 ; i < m->filas ; i++)
        free(*(m->celdas + i));

    free(m->celdas);
    free(m);
}
void Mapa_RellenoObstaculos(tMapa *p)
{
    int i, j;
    for(j = 0 ; j < p->columnas ; j++)
    {
        if(j == 0 || j == p->columnas - 1)
        {
            p->celdas[0][j] = DM_PARED;
            p->celdas[p->filas - 1][j] = DM_PARED;
        }
        else
        {
            p->celdas[0][j] = DM_TECHO;
            p->celdas[p->filas - 1][j] = DM_PISO;
        }
    }
    for (i = 1; i < p->filas - 1; i++)
    {
        p->celdas[i][0] = DM_PARED;
        p->celdas[i][p->columnas - 1] = DM_PARED;
    }
    for (i = 1 ; i < p->filas - 1 ; i++)
        for (j = 1 ; j < p->columnas - 1 ; j++)
        {
            if((i % 2 == 0) && (j % 2 == 0))
                p->celdas[i][j] = DM_OBSTACULO;
        }
}
void Mapa_RellenoObstaculosRombiples(tMapa *p)
{
    int i, j;
    for (i = 1 ; i < p->filas - 1 ; i++)
        for (j = 1 ; j < p->columnas - 1 ; j++)
        {
            if(p->celdas[i][j] == DM_VACIO && (rand() % 10 < 4))
                p->celdas[i][j] = DM_ROMPIBLE;
        }
}
int Mapa_ArchivosGuardar(const char* binPath, tMapa *mapa)
{
    int i;
    FILE *fbin;

    fbin = fopen(binPath, "wb");
    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(mapa->filas), sizeof(int), 1, fbin);
    fwrite(&(mapa->columnas), sizeof(int), 1, fbin);

    for(i=0 ; i< mapa->filas ; i++)
        fwrite(*(mapa->celdas + i), sizeof(int), mapa->columnas, fbin);

    fclose(fbin);
    return TODOOK;
}
tMapa* Mapa_ArchivosCargar(const char* binPath)
{
    int i, filas, columnas;
    tMapa* mapa;
    FILE *pf;

    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    fread(&filas, sizeof(int), 1, pf);
    fread(&columnas, sizeof(int), 1, pf);

    mapa = Mapa_CrearMapa(filas, columnas);
    if(!mapa)
    {
        fclose(pf);
        return NULL;
    }

    for(i = 0 ; i<mapa->filas ; i++)
        fread(*(mapa->celdas + i), sizeof(int), mapa->columnas, pf);

    fclose(pf);
    return mapa;
}
void Mapa_AparicionPuerta(tMapa *mapa, tPuerta *puerta)
{
    int i, j;

    for(i = 1 ; i < mapa->filas - 1 ; i++)
    {
        for(j = 1 ; j < mapa->columnas - 1 ; j++)
        {
            if(mapa->celdas[i][j] == DM_VACIO)
            {
                puerta->vacio++;
                puerta->celdas_transitables++;
            }
            if(mapa->celdas[i][j] == DM_ROMPIBLE)
                puerta->celdas_transitables++;
        }
    }

    puerta->prob = (float)puerta->vacio / (float)puerta->celdas_transitables;

    if(puerta->prob > PROB)
        puerta->estado_puerta = E_ACTIVAR;
}
int Mapa_MovimientoValido(tMapa *mapa, int fila, int columna, int esPJP)
{
    int band;

    band = ERROR_;

    if(fila >= 0 && fila < mapa->filas &&
       columna >= 0 && columna < mapa->columnas)
    {
        if(mapa->celdas[fila][columna] == DM_VACIO ||
           mapa->celdas[fila][columna] == D_MASRANGO ||
           mapa->celdas[fila][columna] == D_MASBOMBA)
            band = TODOOK;
        else if(esPJP && mapa->celdas[fila][columna] == D_PUERTA)
            band = TODOOK;
    }
    return band;
}
