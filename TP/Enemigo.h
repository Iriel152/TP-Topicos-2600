#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "Comunes.h"
#include "Mapa.h"
#include "PJ_Principal.h"

#define MAX_ENEMIGOS 5
#define ENEMIGO_VISUAL 69
#define ENEMIGO_DAT "../Archivos/Enemigo.dat"

typedef struct
{
    Posicion pos; //teniendo en cuenta que ponemos Posicion dentro de
    int esta_vivo; //comunes para que tanto el personaje como  los enemigos puedan usarla
    int velocidad;
    int rebotes;
    int direccion;
    int lado;
    int valor;
}tEnemigo;

tEnemigo* Enemigo_Crear(int fila, int columna); //crea enemigo
void Enemigo_Destruir(tEnemigo*); //libera memoria
void Enemigo_Mover(tMapa*, tEnemigo*); //intenta moverse
void Enemigo_AparicionRandom(tMapa*, tEnemigo*);//aparicion random
int Archivos_GuardarEnemigo(const char* binPath, tEnemigo *enemigo);
tEnemigo* Archivos_CargarEnemigo(const char* binPath);
void EnemigoMover(tMapa *m, tEnemigo *e/*, int *eRebotes, int *eDireccion, int *eLados*/);
void DireccionEnemigo(tEnemigo *enemigo);
void EnemigoMoverRandom(tMapa *m, tEnemigo *e, tPersonaje *p);
void EnemigoMovimientoxTiempo(DWORD tiempo, tEnemigo *enemigo, tMapa *mapa, DWORD *tiempo_enemigo, tPersonaje *p);
void EnemigoDanioaPJ(tEnemigo *enemigo, tPersonaje *personaje);

#endif // ENEMIGO_H_INCLUDED
