#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include "Comunes.h"
#include "Mapa.h"
#include "PJ_Principal.h"


#define MAX_BOMBAS 2
#define TIMER_BOMBA 5      // se desactiva tras 3 turnos del jugador
#define SIMBOLO_BOMBA 254  // simbolito bomba  ■


typedef struct Bomba{
    Posicion pos;
    int activa;
    int turnos_restantes;
} Bomba;

typedef struct vBombas{
    Bomba *bombas;
    int ce;
    int tam;
    int rango;
} vBombas;

vBombas* crear_vec_bombs();
void free_vec_bombs(vBombas *vbomb);
int inicializar_vec_bombs(vBombas *vbomb);
int insertar_bomba(vBombas*vbomb);
int  bomba_poner(vBombas *vbomb, Mapa *m, Personaje *p);
int  hay_bomba(const vBombas *vbomb, int x, int y);
void actualizar_bomba(vBombas *vbomb, Mapa *m);
void explotar_bomba(Mapa *m, int x, int y, int rango);

#endif // BOMBA_H_INCLUDED
