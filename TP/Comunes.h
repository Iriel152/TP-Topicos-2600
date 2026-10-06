#ifndef COMUNES_H_INCLUDED
#define COMUNES_H_INCLUDED

///BIBLIOTECAS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

///DEFINE
#define ERROR_MEMORIA -1
#define TODOOK    0
#define ERROR_ -2
#define ERROR_ARCH -3
#define ENCONTRADO 1
#define NO_ENCONTRADO 0

///ESTRUCTURAS
typedef struct{
    int x;
    int y;
}Posicion;

int EsLetraValida(int LetraEsperada, int LetraRecibida);
int Tecla_ArribaAbajo(int tecla);
int ObtenerNumeroAleatorio(int, int);

#endif // COMUNES_H_INCLUDED
