#ifndef POTENCIADOR_H_INCLUDED
#define POTENCIADOR_H_INCLUDED

//tipo
#define T_MAS_BOMBA 1
#define T_MAS_RANGO 2
#define CANT_POT 5
#define TIMER_POT 10000
#include "Comunes.h"
#include "Mapa.h"
#define POTENCIADOR_DAT "../Archivos/Potenciador.dat"

typedef struct{
    int tipo;
    int estado;
    Posicion pos;
    DWORD t_creacion;
    int cant;
}tPotenciador;

void Potenciador_RellenarVec(tVector*, int);
void Potenciador_GenerarAleatorio(tVector*, tMapa*, int, int, DWORD);
void actualizar_potenciador(tMapa*, tVector*, DWORD);
#endif // POTENCIADOR_H_INCLUDED
