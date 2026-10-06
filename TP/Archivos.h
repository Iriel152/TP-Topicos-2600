#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

///.h
#include "Mapa.h"
#include "PJ_Principal.h"

///DEFINE
#define MAPA_DAT "../Archivos/mapa.dat"

int partida_guardar_binario(const char *ruta, const tMapa *mapa, const Personaje *jugador);
int partida_cargar_binario(const char *ruta, tMapa **mapa_out, Personaje **jugador_out);
int Archivos_GuardarMapa(const char* binPath, tMapa *mapa);
tMapa* Archivos_CargarMapa(const char* binPath);

#endif // ARCHIVOS_H_INCLUDED
