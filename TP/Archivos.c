#include "Archivos.h"
int ArchivosCargaDatos(void)
{
    FILE *pfMapa, *pfPrincipal, *pfEnemigo;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;

    pfMapa = fopen(MAPA_DAT,"rb");
    if(!pfMapa)
    {
        mapa = Mapa_CrearMapa(FILAS, COLUMNAS);
        if(!mapa)
            return ERROR_ARCH;
        Mapa_RellenoObstaculos(mapa);
        Archivos_GuardarMapa(MAPA_DAT, mapa);
        Mapa_DestruirMapa(mapa);
    }else
        fclose(pfMapa);

    pfPrincipal = fopen(PJ_DAT,"rb");
    if(!pfPrincipal)
    {
        personaje = PJ_Princial_CrearPersonaje(1, 1, VIDAS_BASE);
        if(!personaje)
            return ERROR_ARCH;
        Archivos_GuardarPersonaje(PJ_DAT, personaje);
        PJ_Principal_DestruirPersonaje(personaje);
    }else
        fclose(pfPrincipal);

    pfEnemigo = fopen(ENEMIGO_DAT, "rb");
    if(!pfEnemigo)
    {
        enemigo = Enemigo_Crear(1, 1);
        if(!enemigo)
            return ERROR_ARCH;
        Archivos_GuardarEnemigo(ENEMIGO_DAT, enemigo);
        Enemigo_Destruir(enemigo);
    }else
        fclose(pfEnemigo);
    return TODOOK;
}
int partida_guardar_binario(const char *ruta, const tMapa *mapa, const tPersonaje *jugador) {
    FILE *arch = fopen(ruta, "wb");
    if (!arch) return ERROR_ARCH;

    // 1. Guardar dimensiones
    fwrite(&mapa->filas, sizeof(int), 1, arch);
    fwrite(&mapa->columnas, sizeof(int), 1, arch);

    // 2. Guardar grilla celda por celda
    for (int i = 0; i < mapa->filas; i++) {
        fwrite(mapa->celdas[i], sizeof(int), mapa->columnas, arch);
    }

    // 3. Guardar estado del jugador
    fwrite(jugador, sizeof(tPersonaje), 1, arch);

    fclose(arch);
    return TODOOK;
}

int partida_cargar_binario(const char *ruta, tMapa **mapa_out, tPersonaje **jugador_out) {
    FILE *arch = fopen(ruta, "rb");
    if (!arch) return ERROR_ARCH;

    int filas, cols;
    fread(&filas, sizeof(int), 1, arch);
    fread(&cols, sizeof(int), 1, arch);

    tMapa *m = Mapa_CrearMapa(filas, cols);
    if (!m) {
        fclose(arch);
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < filas; i++) {
        fread(m->celdas[i], sizeof(int), cols, arch);
    }

    tPersonaje *p = (tPersonaje*) malloc(sizeof(tPersonaje));
    if (!p) {
        Mapa_DestruirMapa(m);
        fclose(arch);
        return ERROR_MEMORIA;
    }
    fread(p, sizeof(tPersonaje), 1, arch);

    fclose(arch);
    *mapa_out = m;
    *jugador_out = p;
    return TODOOK;
}
