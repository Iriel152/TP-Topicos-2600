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
#define ACTIVA 2
#define ACTIVAR 1
#define DESACTIVADA 0
#define SALIDA 'S'
#define PROBABILIDADPUERTA 0.7
#define MAPA_DAT "../Archivos/Mapa.dat"

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
int MovimientoValido(tMapa *mapa, int fila, int columna, int esPJP);
void AparicionPuerta(tMapa *mapa, tPuerta *puerta);

#endif // MAPA_H_INCLUDED
