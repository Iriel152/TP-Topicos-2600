#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

///.h
#include "Comunes.h"

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
#define ACTIVA 2
#define ACTIVAR 1
#define DESACTIVADA 0

#define PROBABILIDADPUERTA 0.7
///RUTAS
#define MAPA_DAT "../Archivos/Mapa.dat"
#define PUERTA_DAT "../Archivos/Puerta.dat"

///ESTRUCTURAS
typedef struct{
    int filas;
    int columnas;
    int **celdas;
}tMapa;

typedef struct{
    float prob;
    int vacio;
    int cualquiera;
    int estado_puerta;
}tPuerta;

tMapa* Mapa_CrearMapa(int,  int);
void Mapa_DestruirMapa(tMapa *);
void Mapa_RellenoObstaculos(tMapa *p);
int Archivos_GuardarMapa(const char* binPath, tMapa *mapa);
tMapa* Archivos_CargarMapa(const char* binPath);
void Mapa_RellenoObstaculosRombiples(tMapa *p);
void AparicionPuerta(tMapa *mapa, tPuerta *puerta);
tPuerta *Mapa_CrearPuerta(void);
void Mapa_DestruirPuerta(tPuerta *puerta);
int Archivos_GuardarPuerta_Mapa(const char* binPath, tPuerta *puerta);
tPuerta* Archivos_CargarPuerta(const char* binPath);
int MovimientoValido(tMapa *mapa, int fila, int columna, int esPJP);

#endif // MAPA_H_INCLUDED
