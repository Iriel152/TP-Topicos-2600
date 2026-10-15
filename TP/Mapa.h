#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

///.h
#include "Comunes.h"
#include "Puerta.h"

///DISENIO MAPA
#define DM_PARED 219
#define DM_TECHO 223
#define DM_PISO  220
#define DM_VACIO 0
#define DM_OBSTACULO 219
#define DM_ROMPIBLE 176
///DEFINE
#define FILAS 15
#define COLUMNAS 49

///RUTAS
#define MAPA_DAT "../Archivos/Mapa.dat"
#define PUERTA_DAT "../Archivos/Puerta.dat"

///ESTRUCTURAS
typedef struct{
    int filas;
    int columnas;
    int **celdas;
}tMapa;

tMapa* Mapa_CrearMapa(int,  int);
void Mapa_DestruirMapa(tMapa *);
void Mapa_RellenoObstaculos(tMapa*);
int Archivos_GuardarMapa(const char*, tMapa*);
tMapa* Archivos_CargarMapa(const char*);
void Mapa_RellenoObstaculosRombiples(tMapa*);
void AparicionPuerta(tMapa*, tPuerta*);
int MovimientoValido(tMapa*, int, int, int);

#endif // MAPA_H_INCLUDED
