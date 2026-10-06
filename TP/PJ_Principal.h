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
#define SEGUIR 1
#define SALIR 0
#define AMAYUSCULA(X) ((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X)

///ESTRUCTURAS
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
