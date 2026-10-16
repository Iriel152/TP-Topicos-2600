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

//typedef struct vBombas vBombas;

tPersonaje* PJ_Crear(void);
void PJ_Destruir(tPersonaje*);
int PJ_ArchivosGuardar(const char*, tPersonaje*);
tPersonaje* PJ_ArchivosCargar(const char*);
void PJ_AparicionRandom(tMapa*, tPersonaje*);
void PJ_LimpiarLados(tMapa*, tPersonaje*);
void PJ_MovimientoxTiempo(DWORD, tPersonaje*, tMapa*, DWORD*, int*, tVector*);
int PJ_Movimiento(tMapa*, tPersonaje*, tVector*);
void ValidarEspacio(tMapa*, tPersonaje*, int*, int*);
int  PJ_PoneBomba(tVector *, tMapa*, tPersonaje*);
int PJ_EnSalida(tMapa*, tPersonaje*);

#endif // PJ_PRINCIPAL_H_INCLUDED
