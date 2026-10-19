#ifndef PUERTA_H_INCLUDED
#define PUERTA_H_INCLUDED

///.h
#include "Comunes.h"

///RUTAS
#define PUERTA_DAT "../Archivos/Puerta.dat"
///DEFINE
#define PROB 0.7

///ESTRUCTURAS
typedef struct Puerta{
    float prob;
    int vacio;
    int celdas_transitables;
    int estado_puerta;
}tPuerta;

tPuerta *Puerta_Crear(void);
void Puerta_Destruir(tPuerta*);
int Puerta_ArchivosGuardar(const char*, tPuerta*);
tPuerta* Puerta_ArchivosCargar(const char*);

#endif // PUERTA_H_INCLUDED
