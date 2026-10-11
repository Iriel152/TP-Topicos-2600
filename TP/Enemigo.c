#include "Enemigo.h"
tEnemigo* Enemigo_Crear(int fila, int columna)
{
    tEnemigo *e = (tEnemigo*)malloc(sizeof(tEnemigo));

    if(!e)
        return NULL;

    e->pos.x = fila;
    e->pos.y = columna;
    e->esta_vivo = 1;
    e->velocidad = 800;
    e->rebotes = 4;
    e->direccion = 0;
    e->lado = 0;

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
    fwrite(&(enemigo->velocidad), sizeof(int), 1, fbin);
    fwrite(&(enemigo->rebotes), sizeof(int), 1, fbin);
    fwrite(&(enemigo->direccion), sizeof(int), 1, fbin);
    fwrite(&(enemigo->lado), sizeof(int), 1, fbin);

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
    fread(&(enemigo->velocidad), sizeof(int), 1, pf);
    fread(&(enemigo->rebotes), sizeof(int), 1, pf);
    fread(&(enemigo->direccion), sizeof(int), 1, pf);
    fread(&(enemigo->lado), sizeof(int), 1, pf);

    fclose(pf);
    return enemigo;
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
void EnemigoMoverRandom(tMapa *mapa, tEnemigo *enemigo)
{
    //int direccion;
    int nuevaFila;
    int nuevaColumna;

    nuevaFila = enemigo->pos.x;
    nuevaColumna = enemigo->pos.y;

    switch(enemigo->direccion )
    {
        case ARRIBA:
            switch(enemigo->lado)
            {
                case IZQUIERDA:
                nuevaColumna--;    // izquierda
                break;

                case DERECHA:
                nuevaColumna++;    // derecha
                break;
            }break;

        case ABAJO:
            switch(enemigo->lado)
                {
                    case ARRIBA:
                    nuevaFila--;       // arriba
                    break;

                    case ABAJO:
                    nuevaFila++;       // abajo
                    break;
                }break;
            }

            if(MovimientoValido(mapa, nuevaFila, nuevaColumna))
            {
                enemigo->pos.x = nuevaFila;
                enemigo->pos.y = nuevaColumna;
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
void EnemigoMovimientoxTiempo(DWORD ahora, tEnemigo *enemigo, tMapa *mapa, DWORD *tiempo_enemigo)
{
    if(ahora - (*tiempo_enemigo) >= enemigo->velocidad)
    {
        DireccionEnemigo(enemigo);
        EnemigoMoverRandom(mapa, enemigo);
        *tiempo_enemigo = ahora;
    }
}
void EnemigoMover(tMapa *mapa, tEnemigo *enemigo)
{
    int direccion;
    int nuevaFila;
    int nuevaColumna;

    direccion = ObtenerNumeroAleatorio(1,4);

    nuevaFila = enemigo->pos.x;
    nuevaColumna = enemigo->pos.y;

    switch(direccion)
    {
        case ARRIBA:
            nuevaFila--;       // arriba
            break;

        case ABAJO:
            nuevaFila++;       // abajo
            break;

        case IZQ:
            nuevaColumna--;    // izquierda
            break;

        case DER:
            nuevaColumna++;    // derecha
            break;
    }

    if(MovimientoValido(mapa, nuevaFila, nuevaColumna))
    {
        enemigo->pos.x = nuevaFila;
        enemigo->pos.y = nuevaColumna;
    }
}
