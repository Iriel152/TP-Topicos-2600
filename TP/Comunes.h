#ifndef COMUNES_H_INCLUDED
#define COMUNES_H_INCLUDED

///BIBLIOTECAS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

///RETURNS
#define ERROR_MEMORIA -1
#define TODOOK    0
#define ERROR_ -2
#define ERROR_ARCH -3
#define ENCONTRADO 1
#define NO_ENCONTRADO 0
///TECLAS
#define TEC_ESC 27
#define TEC_ARRIBA 'W'
#define TEC_ABAJO 'S'
#define TEC_DERECHA 'D'
#define TEC_IZQUIERDA 'A'
#define TEC_PONERSELEC 'E'
///ESTADOS PARTIDA
#define EP_GAMEOVER -1
#define EP_NUEVAP 0
#define EP_CARGARP 1
#define EP_CONTINUAR 2
#define EP_SALIR 3
#define EP_VICTORIA 4
///DISENIOS
#define D_ENEMIGO 'E'
#define D_PJP 'P'
#define D_BOMBA 'O'
#define D_PUERTA 'S'
#define D_EXPLOSION '#'
///
#define HORIZONTAL 1
#define VERTICAL 2
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 1
#define ABAJO 2
#define IZQ 3
#define DER 4
#define TIEMPOFIN 200
#define SEGUNDOS 1000
///MACROS
#define AMAYUSCULA(X) ((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X)

///ESTRUCTURAS
typedef struct{
    int x;
    int y;
}Posicion;

int EsLetraValida(int, int);
int Tecla_ArribaAbajo(int);
int ObtenerNumeroAleatorio(int, int);
int ASegundos(DWORD);


#endif // COMUNES_H_INCLUDED
