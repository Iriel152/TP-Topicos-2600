#include "Archivos.h"
int ArchivosCargaDatos(void)
{
    FILE *pfMapa, *pfPrincipal, *pfEnemigo, *pfBombs, *pfPuerta;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;
    vBombas *vbomb;
    tPuerta *puerta;

    pfMapa = fopen(MAPA_DAT,"rb");
    if(!pfMapa)
    {
        mapa = Mapa_CrearMapa(FILAS, COLUMNAS);
        if(!mapa)
            return ERROR_ARCH;
        Mapa_RellenoObstaculos(mapa);
        if(Archivos_GuardarMapa(MAPA_DAT, mapa) == ERROR_ARCH)
           {
              Mapa_DestruirMapa(mapa);
              return ERROR_ARCH;
           }
    }else
        fclose(pfMapa);

    pfPrincipal = fopen(PJ_Principal_DAT,"rb");
    if(!pfPrincipal)
    {
        personaje = PJ_Princial_CrearPersonaje();
        if(!personaje)
            return ERROR_ARCH;
        Archivos_GuardarPersonaje(PJ_Principal_DAT, personaje);
        PJ_Principal_DestruirPersonaje(personaje);
    }else
        fclose(pfPrincipal);

    pfEnemigo = fopen(ENEMIGO_DAT, "rb");
    if(!pfEnemigo)
    {
        enemigo = Enemigo_Crear();
        if(!enemigo)
            return ERROR_ARCH;
        Enemigo_ArchivosGuardar(ENEMIGO_DAT, enemigo);
        Enemigo_Destruir(enemigo);
    }else
        fclose(pfEnemigo);

    pfBombs = fopen(BOMB_DAT, "rb");
    if(!pfBombs)
    {
        vbomb=crear_vec_bombs();
        if(!vbomb)
            return ERROR_ARCH;
        Archivos_GuardarBombas(BOMB_DAT, vbomb);
        free_vec_bombs(vbomb);
    }
    else
        fclose(pfBombs);

    pfPuerta = fopen(PUERTA_DAT, "rb");
    if(!pfPuerta)
    {
        puerta = Mapa_CrearPuerta();
        if(!puerta)
            return ERROR_ARCH;
        Archivos_GuardarPuerta_Mapa(PUERTA_DAT, puerta);
        Mapa_DestruirPuerta(puerta);
    }
    else
        fclose(pfPuerta);

    return TODOOK;
}

