#include "Archivos.h"
int ArchivosCargaDatos(void)
{
    FILE *pfMapa, *pfPrincipal, *pfEnemigo, *pfBombs, *pfPot, *pfPuerta;
    tMapa *mapa;
    tPersonaje *personaje;
    tPuerta *puerta;
    tVector *vec_bomba, *vec_enemigo, *vec_pot;

    pfMapa = fopen(MAPA_DAT,"rb");
    if(!pfMapa)
    {
        mapa = Mapa_CrearMapa(FILAS, COLUMNAS);
        if(!mapa)
            return ERROR_MEMORIA;
        Mapa_RellenoObstaculos(mapa);
        if(Mapa_ArchivosGuardar(MAPA_DAT, mapa) == ERROR_ARCH)
           {
              Mapa_DestruirMapa(mapa);
              return ERROR_ARCH;
           }
    }else
        fclose(pfMapa);

    pfPrincipal = fopen(PJ_Principal_DAT,"rb");
    if(!pfPrincipal)
    {
        personaje = PJ_Crear();

        if(!personaje)
            return ERROR_MEMORIA;
        if(PJ_ArchivosGuardar(PJ_Principal_DAT, personaje) == ERROR_ARCH)
        {
            PJ_Destruir(personaje);
            return ERROR_ARCH;
        }
    }else
        fclose(pfPrincipal);

    pfPuerta = fopen(PUERTA_DAT, "rb");
    if(!pfPuerta)
    {
        puerta = Puerta_Crear();
        if(!puerta)
            return ERROR_MEMORIA;
        if(Puerta_ArchivosGuardar(PUERTA_DAT, puerta) == ERROR_ARCH)
        {
            Puerta_Destruir(puerta);
            return ERROR_ARCH;
        }
    }
    else
        fclose(pfPuerta);

    pfEnemigo = fopen(ENEMIGO_DAT, "rb");
    if(!pfEnemigo)
    {
        vec_enemigo = Comunes_CrearVector(sizeof(tEnemigo));
        if(!vec_enemigo)
            return ERROR_MEMORIA;
        Enemigo_RellenarVec(vec_enemigo, CANT_ENEMIGO);

        if(Comunes_VectorArchivosGuardar(ENEMIGO_DAT, vec_enemigo) == ERROR_ARCH)
        {
            Comunes_DestruirVector(vec_enemigo);
            return ERROR_ARCH;
        }
    }else
        fclose(pfEnemigo);

    pfBombs = fopen(BOMBA_DAT, "rb");
    if(!pfBombs)
    {
        vec_bomba = Comunes_CrearVector(sizeof(tBomba));
        if(!vec_bomba)
            return ERROR_MEMORIA;

        Bomba_RellenarVec(vec_bomba, CANT_BOMBA);

        if(Comunes_VectorArchivosGuardar(BOMBA_DAT, vec_bomba) == ERROR_ARCH)
        {
            Comunes_DestruirVector(vec_bomba);
            return ERROR_ARCH;
        }
    }
    else
        fclose(pfBombs);

    pfPot = fopen(POTENCIADOR_DAT, "rb");
    if(!pfPot)
    {
        vec_pot = Comunes_CrearVector(sizeof(tPotenciador));
        if(!vec_pot)
            return ERROR_MEMORIA;

        Potenciador_RellenarVec(vec_pot, CANT_POT);

        if(Comunes_VectorArchivosGuardar(POTENCIADOR_DAT, vec_pot) == ERROR_ARCH)
        {
            Comunes_DestruirVector(vec_pot);
            return ERROR_ARCH;
        }
    }
    else
        fclose(pfPot);

    return TODOOK;
}
