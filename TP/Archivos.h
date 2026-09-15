#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "Mapa.h"
#include "PJ_Principal.h"

int partida_guardar_binario(const char *ruta, const Mapa *mapa, const Personaje *jugador);
int partida_cargar_binario(const char *ruta, Mapa **mapa_out, Personaje **jugador_out);

#endif // ARCHIVOS_H_INCLUDED
