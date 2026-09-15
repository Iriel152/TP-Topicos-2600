#ifndef PJ_PRINCIPAL_H_INCLUDED
#define PJ_PRINCIPAL_H_INCLUDED

#define PJ_Principal_DAT "../Archivos/PJ_Principal.dat"
#include "Comunes.h"
#include "Mapa.h"

#define PJP 80

typedef struct{
    int x;
    int y;
}Posicion;
typedef struct{
    Posicion pos;
    int vidas;
    int alcance_bomba;
    int esta_vivo;
}Personaje;
Personaje* PJ_Princial_CrearPersonaje(int, int, int);
void PJ_Principal_DestruirPersonaje(Personaje*);
void PJ_Principal_AparicionRandom(Mapa*,Personaje*);

#endif // PJ_PRINCIPAL_H_INCLUDED
