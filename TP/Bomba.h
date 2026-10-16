#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

///.h
#include "Comunes.h"

///DEFINE
#define CANT_BOMBA 7
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

void actualizar_bomba(tVector*, DWORD);
//void limpiar_estela(tMapa*, int, int, int);

#endif // BOMBA_H_INCLUDED
