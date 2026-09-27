#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include "Comunes.h"
#include "Mapa.h"
#include "PJ_Principal.h"

#define MAX_BOMBAS 8
#define TIMER_BOMBA 3      // se desactiva tras 3 turnos del jugador
#define SIMBOLO_BOMBA 254  // simbolito bomba  ■

typedef struct {
    Posicion pos;
    int activa;
    int turnos_restantes;
} Bomba;

typedef struct {
    Bomba bombas[MAX_BOMBAS];
} vBombas;

vBombas* crear_vec_bombs();
void free_vec_bombs(vBombas *vbomb);
void inicializar_vec_bombs(vBombas *vbomb);

int  bomba_poner(vBombas *vbomb, Mapa *m, Personaje *p);
int  hay_bomba(const vBombas *vbomb, int x, int y);
void actualizar_bomba(vBombas *vbomb, int x_actual, int y_actual);

#endif // BOMBA_H_INCLUDED
