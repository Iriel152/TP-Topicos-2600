#include "Mapa.h"
tMapa* Mapa_CrearMapa(int filas, int columnas)
{
    int i, j;
    tMapa* m = (tMapa*)malloc(sizeof(tMapa));
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
            return NULL;
        }
        for(j=0 ; j<columnas ; j++)
            m->celdas[i][j] = VACIO;
    }
    return m;
}
void Mapa_DestruirMapa(tMapa *p)
{
    int i;
    if(!p)
        return;
    for(i=0 ; i<p->filas; i++)
        free(p->celdas[i]);
    free(p->celdas);
    free(p);
}
void Mapa_RellenoObstaculos(tMapa *p)
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
//            else
//                if(rand() % 10 < 4)
//                    p->celdas[i][j] = ROMPIBLE;
        }
}
void Mapa_RellenoObstaculosRombiples(tMapa *p)
{
    int i, j;
    for (i = 1; i < p->filas - 1; i++)
        for (j = 1; j < p->columnas - 1; j++)
        {
            if(p->celdas[i][j] == VACIO && rand() % 10 < 4)
                p->celdas[i][j] = ROMPIBLE;
        }
}
int Archivos_GuardarMapa(const char* binPath, tMapa *mapa)
{
    int i;
    FILE *fbin;
    fbin=fopen(binPath,"wb");
    if(!fbin)
        return ERROR_ARCH;
    fwrite(&(mapa->filas), sizeof(int), 1, fbin);
    fwrite(&(mapa->columnas), sizeof(int), 1, fbin);
    for(i=0 ; i< mapa->filas ; i++)
    {
        fwrite(mapa->celdas[i], sizeof(int), mapa->columnas, fbin);
    }
    fclose(fbin);
    return TODOOK;
}
tMapa* Archivos_CargarMapa(const char* binPath)
{
    int i, filas, columnas;
    tMapa* mapa;
    FILE *pf;

    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    fread(&filas, sizeof(int), 1, pf);
    fread(&columnas, sizeof(int), 1, pf);

    mapa = Mapa_CrearMapa(FILAS, COLUMNAS);
    if(!mapa)
    {
        fclose(pf);
        return NULL;
    }

    for(i=0; i<mapa->filas; i++)
    {
        fread(mapa->celdas[i], sizeof(int), mapa->columnas, pf);
    }
    fclose(pf);
    return mapa;
}
int MovimientoValido(tMapa *mapa, int fila, int columna, int esPJP)
{
    if(fila < 0 || fila >= FILAS ||
       columna < 0 || columna >= COLUMNAS)
    {
        return 0;
    }

    if(esPJP)
    {
        if(mapa->celdas[fila][columna] == SALIDA)
        {
            return 1;
        }
    }

    if(mapa->celdas[fila][columna] != VACIO)
    {
        return 0;
    }

    return 1;
}
void AparicionPuerta(tMapa *mapa, tPuerta *puerta)
{
    int i,j;

    for(i = 1; i < mapa->filas - 1; i++)
    {
        for(j = 1; j < mapa->columnas - 1; j++)
        {
            if(mapa->celdas[i][j] == VACIO)
            {
                puerta->vacio++;
                puerta->cualquiera++;
            }
            if(mapa->celdas[i][j] == ROMPIBLE)
            {
                puerta->cualquiera++;
            }
        }
    }

    puerta->prob = (float)puerta->vacio/(float)puerta->cualquiera;

    if(puerta->prob > PROBABILIDADPUERTA)
    {
        puerta->estado_puerta = ACTIVAR;
    }
}
tPuerta *Mapa_CrearPuerta()
{
    tPuerta *puerta = (tPuerta*)malloc(sizeof(tPuerta));
    if(!puerta)
        return NULL;
    puerta->estado_puerta = DESACTIVADA;
    puerta->cualquiera = 0;
    puerta->prob = 0;
    puerta->vacio = 0;

    return puerta;
}
void Mapa_DestruirPuerta(tPuerta *puerta)
{
    if(puerta)
        free(puerta);
}
tPuerta* Archivos_CargarPuerta(const char* binPath)
{
    FILE *pf;
    tPuerta *puerta;
    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    puerta = (tPuerta*)malloc(sizeof(tPuerta));
    if(!puerta)
    {
        fclose(pf);
        return NULL;
    }

    fread(&(puerta->cualquiera), sizeof(int), 1, pf);
    fread(&(puerta->estado_puerta), sizeof(int), 1, pf);
    fread(&(puerta->prob), sizeof(float), 1, pf);
    fread(&(puerta->vacio), sizeof(int), 1, pf);

    fclose(pf);
    return puerta;
}
int Archivos_GuardarPuerta_Mapa(const char* binPath, tPuerta *puerta)
{
    FILE *fbin;
    fbin = fopen(binPath,"wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(puerta->cualquiera), sizeof(int), 1, fbin);
    fwrite(&(puerta->estado_puerta), sizeof(int), 1, fbin);
    fwrite(&(puerta->prob), sizeof(float), 1, fbin);
    fwrite(&(puerta->vacio), sizeof(int), 1, fbin);

    fclose(fbin);
    return TODOOK;
}
