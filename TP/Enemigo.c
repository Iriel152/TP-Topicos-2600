#include "Enemigo.h"
tEnemigo* Enemigo_Crear()
{
    tEnemigo *e;

    e = (tEnemigo*)malloc(sizeof(tEnemigo));
    if(!e)
        return NULL;

    e->pos.x = 0;
    e->pos.y = 0;
    e->esta_vivo = 1;
    e->velocidad = 600;
    e->rebotes = 3;
    e->direccion = 0;
    e->lado = 0;
    e->valor = 200;

    return e;
}
void Enemigo_Destruir(tEnemigo *e)
{
    if(e)
        free(e);
}
int Enemigo_ArchivosGuardar(const char* binPath, tEnemigo *enemigo)
{
    FILE *fbin;
    fbin = fopen(binPath, "wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(enemigo->esta_vivo), sizeof(int), 1, fbin);
    fwrite(&(enemigo->pos), sizeof(enemigo->pos), 1, fbin);
    fwrite(&(enemigo->velocidad), sizeof(int), 1, fbin);
    fwrite(&(enemigo->rebotes), sizeof(int), 1, fbin);
    fwrite(&(enemigo->direccion), sizeof(int), 1, fbin);
    fwrite(&(enemigo->lado), sizeof(int), 1, fbin);
    fwrite(&(enemigo->valor), sizeof(int), 1, fbin);

    fclose(fbin);
    return TODOOK;
}
tEnemigo* Enemigo_ArchivosCargar(const char* binPath)
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
    fread(&(enemigo->pos), sizeof(enemigo->pos), 1, pf);
    fread(&(enemigo->velocidad), sizeof(int), 1, pf);
    fread(&(enemigo->rebotes), sizeof(int), 1, pf);
    fread(&(enemigo->direccion), sizeof(int), 1, pf);
    fread(&(enemigo->lado), sizeof(int), 1, pf);
    fread(&(enemigo->valor), sizeof(int), 1, pf);

    fclose(pf);
    return enemigo;
}
void Enemigo_AparicionRandom(tMapa *m, tEnemigo *e)
{
    int fila, columna;

    do
    {
        fila = ObtenerNumeroAleatorio(1, m->filas - 2);
        columna = ObtenerNumeroAleatorio(1, m->columnas - 2);

    } while(m->celdas[fila][columna] != DM_VACIO);

    e->pos.x = columna;
    e->pos.y = fila;
}
void EnemigoMovimientoxTiempo(DWORD ahora, tEnemigo *enemigo, tMapa *mapa, DWORD *tiempo_enemigo, tPersonaje *p)
{
    if(ahora - (*tiempo_enemigo) >= enemigo->velocidad && enemigo->esta_vivo == 1)
    {
        DireccionEnemigo(enemigo);
        EnemigoMoverRandom(mapa, enemigo, p);
        EnemigoDanioaPJ(enemigo, p, ahora);
        *tiempo_enemigo = ahora;
    }
}
void DireccionEnemigo(tEnemigo *enemigo)
{
    if(enemigo->direccion == 0)
    {
        enemigo->direccion = ObtenerNumeroAleatorio(1,2);
        enemigo->lado= ObtenerNumeroAleatorio(1,2);
    }

    if(enemigo->rebotes == 0)
    {
        if(enemigo->direccion == 1)
            {
                enemigo->direccion= 2;
            }else
                {
                    enemigo->direccion = 1;
                }

        enemigo->rebotes = 4;
    }
}
void EnemigoMoverRandom(tMapa *mapa, tEnemigo *enemigo, tPersonaje *personaje)
{
    int nuevaFila, nuevaColumna;

    nuevaColumna = enemigo->pos.x;
    nuevaFila = enemigo->pos.y;

    switch(enemigo->direccion)
    {
        case ARRIBA:
            switch(enemigo->lado)
            {
                case IZQUIERDA:
                nuevaColumna--;
                break;

                case DERECHA:
                nuevaColumna++;
                break;
            }break;

        case ABAJO:
            switch(enemigo->lado)
                {
                    case ARRIBA:
                    nuevaFila--;
                    break;

                    case ABAJO:
                    nuevaFila++;
                    break;
                }break;
            }
            if(MovimientoValido(mapa, nuevaFila, nuevaColumna, 0) == TODOOK)
            {
                enemigo->pos.x = nuevaColumna;
                enemigo->pos.y = nuevaFila;
            }else
                {
                    enemigo->rebotes--;
                    if(enemigo->lado == 1)
                    {
                        enemigo->lado= 2;
                    }else
                        {
                            enemigo->lado = 1;
                        }
                }
}
void EnemigoDanioaPJ(tEnemigo *enemigo, tPersonaje *personaje, DWORD ahora)
{
    int distancia_x, distancia_y;

    if(personaje->esta_vivo == 2)
        return;

    distancia_x = enemigo->pos.x - personaje->pos.x;
    distancia_y = enemigo->pos.y - personaje->pos.y;

    if(distancia_x == 0 && distancia_y == 0)
    {
        personaje->vidas--;
        personaje->esta_vivo = 2;
        personaje->invul = ahora;
    }
}
