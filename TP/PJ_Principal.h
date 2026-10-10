#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

///.h
#include "Mapa.h"
#include "Comunes.h"

//#include "Bomba.h"

///BIBLIOTECAS
#include <conio.h>

///DEFINE
#define PJP 80
#define PJ_Principal_DAT "../Archivos/PJ_Principal.dat"
#define VIDAS_BASE 3

///ESTRUCTURAS
typedef struct{
    Posicion pos;
    int vidas;
    int alcance_bomba;
    int esta_vivo;
    float velocidad;
    int puntaje;
}tPersonaje;

typedef struct vBombas vBombas;

tPersonaje* PJ_Princial_CrearPersonaje(int, int);
void PJ_Principal_DestruirPersonaje(tPersonaje*);
void PJ_Principal_AparicionRandom(tMapa*,tPersonaje*);
void LimpiarLadosPJ(tMapa*,tPersonaje*);
void NuevaPosicionPJ(tMapa*,tPersonaje*,int,int/*, vBombas**/);
int MovimientoPJ(tMapa*,tPersonaje*/*,vBombas**/);
int Archivos_GuardarPersonaje(const char* binPath, tPersonaje *personaje);
tPersonaje* Archivos_CargarPersonaje(const char* binPath);

#endif // PJ_PRINCIPAL_H_INCLUDED
