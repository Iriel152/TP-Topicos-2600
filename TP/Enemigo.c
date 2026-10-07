#include "Enemigo.h"
tEnemigo* Enemigo_Crear(int fila, int columna)
{
    tEnemigo *e = (tEnemigo*)malloc(sizeof(tEnemigo));

    if(!e)
        return NULL;

    e->pos.x = fila;
    e->pos.y = columna;
    e->esta_vivo = 1;

    return e;
}

void Enemigo_Destruir(tEnemigo *e)
{
    if(e)
        free(e);
}

void Enemigo_AparicionRandom(tMapa *m, tEnemigo *e) //hay que mejorarla para que no se posicione encima de otro enemigo/del jugador
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
int Archivos_GuardarEnemigo(const char* binPath, tEnemigo *enemigo)
{
    FILE *fbin;
    fbin = fopen(binPath, "wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(enemigo->esta_vivo), sizeof(int), 1, fbin);
    fwrite(&(enemigo->pos), sizeof(int), 1, fbin);

    fclose(fbin);
    return TODOOK;
}
tEnemigo* Archivos_CargarEnemigo(const char* binPath)
{
    tEnemigo *enemigo;
    FILE *pf;

    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    enemigo = (tEnemigo*)malloc(sizeof(tEnemigo));
    if(!enemigo)
    {
        fclose(pf);
        return NULL;
    }

    fread(&(enemigo->esta_vivo), sizeof(int), 1, pf);
    fread(&(enemigo->pos), sizeof(int), 1, pf);

    fclose(pf);
    return enemigo;
}
