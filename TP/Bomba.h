#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

///.h
#include "Comunes.h"
///////
#include "Puerta.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "PJ_Principal.h"
///////

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
