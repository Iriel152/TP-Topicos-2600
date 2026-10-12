#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

///.h
#include "Mapa.h"
#include "Comunes.h"
#include "Bomba.h"


///BIBLIOTECAS
#include <conio.h>

///DEFINE
#define PJP 80
#define PJ_Principal_DAT "../Archivos/PJ_Principal.dat"
#define VIDAS_BASE 3

///ESTRUCTURAS
typedef struct tPersonaje{
    Posicion pos;
    int vidas;
    int alcance_bomba;
    int esta_vivo;
    int velocidad;
    int puntaje;
}tPersonaje;

typedef struct vBombas vBombas;

tPersonaje* PJ_Princial_CrearPersonaje(int, int);
void PJ_Principal_DestruirPersonaje(tPersonaje*);
void PJ_Principal_AparicionRandom(tMapa*,tPersonaje*);
void LimpiarLadosPJ(tMapa*,tPersonaje*);
//void NuevaPosicionPJ(tMapa*,tPersonaje*,int,int, vBombas*vbomb);
int MovimientoPJ(tMapa*,tPersonaje*,vBombas* vbomb);
int Archivos_GuardarPersonaje(const char* binPath, tPersonaje *personaje);
tPersonaje* Archivos_CargarPersonaje(const char* binPath);
void PJMovimientoxTiempo(DWORD ahora, tPersonaje *personaje, tMapa *mapa, DWORD *tiempo_personaje, int* seguir, vBombas *vbomb);
int  bomba_poner(vBombas *vbomb, tMapa *m, tPersonaje *p);
int PJEnSalida(tMapa*,tPersonaje*);

#endif // PJ_PRINCIPAL_H_INCLUDED
