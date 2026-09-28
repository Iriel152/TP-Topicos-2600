#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

#define PJ_Principal_DAT "../Archivos/PJ_Principal.dat"
#include "Comunes.h"
#include "Mapa.h"
#include <conio.h>

#define PJP 80

typedef struct{
    Posicion pos;
    int vidas;
    int alcance_bomba;
    int esta_vivo;
    float velocidad;
}Personaje;

typedef struct vBombas vBombas;

Personaje* PJ_Princial_CrearPersonaje(int, int, int);
void PJ_Principal_DestruirPersonaje(Personaje*);
void PJ_Principal_AparicionRandom(Mapa*,Personaje*);
void LimpiarLadosPJ(Mapa*,Personaje*);
void NuevaPosicionPJ(Mapa*,Personaje*,int,int, vBombas*);
int MovimientoPJ(Mapa*,Personaje*,vBombas*);

#endif // PJ_PRINCIPAL_H_INCLUDED
