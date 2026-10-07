#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

///.h
#include "Mapa.h"
#include "PJ_Principal.h"
#include "Enemigo.h"

///DEFINE


int ArchivosCargaDatos(void);
int partida_guardar_binario(const char *ruta, const tMapa *mapa, const tPersonaje *jugador);
int partida_cargar_binario(const char *ruta, tMapa **mapa_out, tPersonaje **jugador_out);

#endif // ARCHIVOS_H_INCLUDED
