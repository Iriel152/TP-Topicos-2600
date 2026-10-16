#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

///.h
#include "Comunes.h"
#include "Puerta.h"
//#include "Enemigo.h" //DESCOMENTAR DESPUES DE MUDAR LOS .H
//#include "PJ_Principal.h"//DESCOMENTAR DESPUES DE MUDAR LOS .H

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

///ESTRUCTURAS
typedef struct{
    int filas;
    int columnas;
    int **celdas;
}tMapa;

tMapa* Mapa_CrearMapa(int,  int);
void Mapa_DestruirMapa(tMapa *);
void Mapa_RellenoObstaculos(tMapa*);
int Mapa_ArchivosGuardar(const char*, tMapa*);
tMapa* Mapa_ArchivosCargar(const char*);
void Mapa_RellenoObstaculosRombiples(tMapa*);
void Mapa_AparicionPuerta(tMapa*, tPuerta*);
int Mapa_MovimientoValido(tMapa*, int, int, int);

#endif // MAPA_H_INCLUDED
