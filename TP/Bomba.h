#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include "Mapa.h"
//#include "PJ_Principal.h"
//#include "Enemigo.h"


#define MAX_BOMBAS 7
#define TIMER_BOMBA 5      // se desactiva tras 3 turnos del jugador

///RUTAS
#define BOMB_DAT "../Archivos/Bomba.dat"

typedef struct Bomba{
    Posicion pos;
    int activa;
    DWORD tiempo_bomba;
} Bomba;

typedef struct vBombas{
    Bomba *bombas;
    int ce;
    int tam;
    int rango;
} vBombas;

typedef struct tEnemigo tEnemigo;
typedef struct tPersonaje tPersonaje;

vBombas* crear_vec_bombs(void);
void free_vec_bombs(vBombas*);
int inicializar_vec_bombs(vBombas*);
int insertar_bomba(vBombas*);
///int  bomba_poner(vBombas *vbomb, tMapa *m, tPersonaje *p);
int  hay_bomba(const vBombas*, int, int);
void actualizar_bomba(vBombas*, tMapa*, DWORD, tPuerta *, tEnemigo *, tPersonaje*);
void explotar_bomba(tMapa*, int, int, int, tPuerta*, tEnemigo*, tPersonaje*, DWORD );
void limpiar_estela(tMapa*, int, int, int);
int Archivos_GuardarBombas(const char*, vBombas*);
vBombas* Archivos_CargarB(const char*);

#endif // BOMBA_H_INCLUDED
