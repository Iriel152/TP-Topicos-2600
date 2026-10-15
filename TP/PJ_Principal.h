#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

///.h
#include "Mapa.h"
#include "Bomba.h"


///BIBLIOTECAS
#include <conio.h>

///DEFINE

#define VIDAS_BASE 3
#define TIMER_INVUL 1500
///RUTAS
#define PJ_Principal_DAT "../Archivos/PJ_Principal.dat"

///ESTRUCTURAS
typedef struct tPersonaje{
    Posicion pos;
    int vidas;
    int alcance_bomba;
    int esta_vivo;
    int velocidad;
    int puntaje;
    DWORD invul;
}tPersonaje;

typedef struct vBombas vBombas;

tPersonaje* PJ_Princial_CrearPersonaje(void);
void PJ_Principal_DestruirPersonaje(tPersonaje*);
void PJ_Principal_AparicionRandom(tMapa*, tPersonaje*);
void LimpiarLadosPJ(tMapa*, tPersonaje*);
int MovimientoPJ(tMapa*, tPersonaje*, vBombas*);
int Archivos_GuardarPersonaje(const char*, tPersonaje*);
tPersonaje* Archivos_CargarPersonaje(const char*);
void PJMovimientoxTiempo(DWORD, tPersonaje*, tMapa*, DWORD*, int*, vBombas*);
int  bomba_poner(vBombas *, tMapa*, tPersonaje*);
int PJEnSalida(tMapa*, tPersonaje*);

#endif // PJ_PRINCIPAL_H_INCLUDED
