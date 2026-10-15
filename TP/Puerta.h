#ifndef PUERTA_H_INCLUDED
#define PUERTA_H_INCLUDED

#include "Comunes.h"

#define ACTIVA 2
#define ACTIVAR 1
#define DESACTIVADA 0
#define PROBABILIDADPUERTA 0.7

typedef struct{
    float prob;
    int vacio;
    int celdas_transitables;
    int estado_puerta;
}tPuerta;

tPuerta *Puerta_Crear(void);
void Puerta_Destruir(tPuerta*);
tPuerta* Puerta_ArchivosCargar(const char*);
int Puerta_ArchivosGuardar(const char*, tPuerta*);

#endif // PUERTA_H_INCLUDED
