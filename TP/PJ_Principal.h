#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

///.h
#include "Comunes.h"


///DEFINE
#define VIDAS_BASE 3
#define TIMER_INVUL 2000
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

typedef struct Mapa tMapa;

tPersonaje* PJ_Crear(void);
void PJ_Destruir(tPersonaje*);
int PJ_ArchivosGuardar(const char*, tPersonaje*);
tPersonaje* PJ_ArchivosCargar(const char*);
void PJ_AparicionRandom(tMapa*, tPersonaje*);//MUDAR A MAPA.H
void PJ_LimpiarLados(tMapa*, tPersonaje*);//MUDAR A MAPA.H
void PJ_MovimientoxTiempo(DWORD, tPersonaje*, tMapa*, DWORD*, int*, tVector*, tVector*);//MUDAR A MAPA.H
int PJ_Movimiento(tMapa*, tPersonaje*, tVector*, tVector*);//MUDAR A MAPA.H
int  PJ_PoneBomba(tVector *, tMapa*, tPersonaje*);//MUDAR A MAPA.H
int PJ_EnSalida(tMapa*, tPersonaje*);//MUDAR A MAPA.H
/////
void PJ_EnPotenciador(tMapa*, tPersonaje*,tVector *v_b, tVector*);
/////
#endif // PJ_PRINCIPAL_H_INCLUDED
