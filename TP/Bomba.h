#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

///.h
#include "Comunes.h"
///DEFINE
#define MAX_BOMBAS 7
#define TIMER_BOMBA 5
///RUTAS
#define BOMBA_DAT "../Archivos/Bomba.dat"

///ESTRUCTURAS
typedef struct Bomba{
    Posicion pos;
    int activa;
    DWORD tiempo_bomba;
    int rango;
} tBomba;

void Bomba_RellenarVec(tVector *v, int cant);

//int insertar_bomba(vBombas*);
/////int  bomba_poner(vBombas *vbomb, tMapa *m, tPersonaje *p);
//int  hay_bomba(const vBombas*, int, int);
//void actualizar_bomba(vBombas*, tMapa*, DWORD, tPuerta *, tEnemigo *, tPersonaje*);
//void explotar_bomba(tMapa*, int, int, int, tPuerta*, tEnemigo*, tPersonaje*, DWORD );
//void limpiar_estela(tMapa*, int, int, int);
//int Archivos_GuardarBombas(const char*, vBombas*);
//vBombas* Archivos_CargarB(const char*);

#endif // BOMBA_H_INCLUDED
