#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

///.h
#include "Comunes.h"

///DEFINE
#define PARED 219
#define TECHO 223
#define PISO  220
#define VACIO 0
#define FILAS 15
#define COLUMNAS 49
#define OBSTACULO 219
#define ROMPIBLE 176
#define ESC 27

///ESTRUCTURAS
typedef struct{
    int filas;
    int columnas;
    int **celdas;
}tMapa;

tMapa* Mapa_CrearMapa(int,  int);
void Mapa_DestruirMapa(tMapa *);
void Mapa_RellenoObstaculos(tMapa *p);

#endif // MAPA_H_INCLUDED
