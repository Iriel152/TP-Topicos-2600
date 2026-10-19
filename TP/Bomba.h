#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

///.h
#include "Comunes.h"


///DEFINE
#define CANT_BOMBA 1
#define TIMER_BOMBA 5
///RUTAS
#define BOMBA_DAT "../Archivos/Bomba.dat"

///ESTRUCTURAS
typedef struct Bomba{
    Posicion pos;
    int activa;
    int explosion;
    DWORD tiempo_bomba;
    int rango;
} tBomba;

/// esto se hace porque se usa una estructura como puntero es lo que se llama una forward declaration
typedef struct Mapa tMapa;
typedef struct tPersonaje tPersonaje;
typedef struct Puerta tPuerta;
////

void Bomba_RellenarVec(tVector *, int);
int Bomba_Existencia(tVector*, int, int);
/////
int ProcesarRompible(tMapa*,int,int,tPuerta*, tVector*);
void actualizar_bomba(tVector*, tMapa*, DWORD, tPuerta*,tVector*, tPersonaje*, tVector*);
void explotar_bomba(tMapa*, tBomba*, tPuerta*, tVector*, tPersonaje*, DWORD, tVector*);
void limpiar_estela(tMapa*, tBomba*, int);
void control_vec_enemigo(tVector*, int, int, tPersonaje *);
/////
#endif // BOMBA_H_INCLUDED
