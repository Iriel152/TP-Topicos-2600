#ifndef COMUNES_H_INCLUDED
#define COMUNES_H_INCLUDED

///BIBLIOTECAS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

///DEFINE
#define ERROR_MEMORIA -1
#define TODOOK    0
#define ERROR_ -2
#define ERROR_ARCH -3
#define ENCONTRADO 1
#define NO_ENCONTRADO 0

///
#define IZQUIERDA 1
#define DERECHA 2
///
#define ARRIBA 1
#define ABAJO 2
#define IZQ 3
#define DER 4
#define TIEMPOFIN 200
#define SEGUNDOS 1000
#define GAMEOVER -1
#define NUEVAP 0
#define CARGARP 1
#define CONTINUAR 2
#define SALIR 3
#define AMAYUSCULA(X) ((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X)

///ESTRUCTURAS
typedef struct{
    int x;
    int y;
}Posicion;

int EsLetraValida(int LetraEsperada, int LetraRecibida);
int Tecla_ArribaAbajo(int tecla);
int ObtenerNumeroAleatorio(int, int);
int ASegundos(DWORD tiempo);


#endif // COMUNES_H_INCLUDED
