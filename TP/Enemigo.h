#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "Comunes.h"
#include "Mapa.h"

#define MAX_ENEMIGOS 5
#define ENEMIGO_VISUAL 69

typedef struct
{
    Posicion pos; //teniendo en cuenta que ponemos Posicion dentro de
    int esta_vivo; //comunes para que tanto el personaje como  los enemigos puedan usarla
}Enemigo;

Enemigo* Enemigo_Crear(int fila, int columna); //crea enemigo
void Enemigo_Destruir(Enemigo*); //libera memoria
void Enemigo_Mover(Mapa*, Enemigo*); //intenta moverse
void Enemigo_AparicionRandom(Mapa*, Enemigo*);//aparicion random

#endif // ENEMIGO_H_INCLUDED
