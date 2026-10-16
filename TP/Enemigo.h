#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

///.h
#include "PJ_Principal.h"

///DEFINE
#define CANT_ENEMIGO 5
///RUTAS
#define ENEMIGO_DAT "../Archivos/Enemigo.dat"

///ESTRUCTURAS
typedef struct tEnemigo
{
    Posicion pos;
    int esta_vivo;
    DWORD velocidad;
    int rebotes;
    int direccion;
    int lado;
    int valor;
}tEnemigo;

tEnemigo* Enemigo_Crear(void);
void Enemigo_Destruir(tEnemigo*);
int Enemigo_ArchivosGuardar(const char*, tEnemigo*);
void Enemigo_RellenarVec(tVector*, int);
tEnemigo* Enemigo_ArchivosCargar(const char* );
void Enemigo_AparicionRandom(tMapa*, tVector*, tPersonaje*);
void EnemigoMovimientoxTiempo(DWORD, tVector*, tMapa*, DWORD *, tPersonaje *p);
void DireccionEnemigo(tEnemigo*);
void EnemigoMoverRandom(tMapa*, tEnemigo*, tPersonaje*);
void EnemigoDanioaPJ(tEnemigo*, tPersonaje*, DWORD);

#endif // ENEMIGO_H_INCLUDED
