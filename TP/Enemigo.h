#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

///.h
#include "Comunes.h"

///DEFINE
#define CANT_ENEMIGO 5
///RUTAS
#define ENEMIGO_DAT "../Archivos/Enemigo.dat"

///ESTRUCTURAS
typedef struct tEnemigo
{
    Posicion pos;
    int esta_vivo;
    DWORD velocidad;
    int rebotes;
    int direccion;
    int lado;
    int valor;
}tEnemigo;

typedef struct Mapa tMapa;
typedef struct tPersonaje tPersonaje;

void Enemigo_RellenarVec(tVector*, int);
void Enemigo_AparicionRandom(tMapa*, tVector*, tPersonaje*); //MUDAR A MAPA.H
void ValidarEspacio(tMapa*, tPersonaje*, tVector*, int, int*, int*);
void EnemigoMovimientoxTiempo(DWORD, tVector*, tMapa*, DWORD*, tPersonaje*);//MUDAR A MAPA.H
void Enemigo_Direccion(tEnemigo*);
void Enemigo_MoverRandom(tMapa*, tEnemigo*, tPersonaje*, tVector*);//MUDAR A MAPA.H
int Enemigo_ColisionEnemigos(tVector*, tEnemigo*, int, int);
void Enemigo_DanioaPJ(tEnemigo*, tPersonaje*, DWORD);

#endif // ENEMIGO_H_INCLUDED
