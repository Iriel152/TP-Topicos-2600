#include "Archivos.h"

int partida_guardar_binario(const char *ruta, const Mapa *mapa, const Personaje *jugador) {
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
    fwrite(jugador, sizeof(Personaje), 1, arch);

    fclose(arch);
    return TODOOK;
}

int partida_cargar_binario(const char *ruta, Mapa **mapa_out, Personaje **jugador_out) {
    FILE *arch = fopen(ruta, "rb");
    if (!arch) return ERROR_ARCH;

    int filas, cols;
    fread(&filas, sizeof(int), 1, arch);
    fread(&cols, sizeof(int), 1, arch);

    Mapa *m = Mapa_CrearMapa(filas, cols);
    if (!m) {
        fclose(arch);
        return ERROR_MEMORIA;
    }

    for (int i = 0; i < filas; i++) {
        fread(m->celdas[i], sizeof(int), cols, arch);
    }

    Personaje *p = (Personaje*) malloc(sizeof(Personaje));
    if (!p) {
        Mapa_DestruirMapa(m);
        fclose(arch);
        return ERROR_MEMORIA;
    }
    fread(p, sizeof(Personaje), 1, arch);

    fclose(arch);
    *mapa_out = m;
    *jugador_out = p;
    return TODOOK;
}
