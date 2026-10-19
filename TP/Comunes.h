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
#define TODOOK 0
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
#define EP_CONTINUAR 2
#define EP_SALIR 3
#define EP_VICTORIA 4
///DISENIOS
#define D_ENEMIGO 'E'
#define D_PJP 'P'
#define D_BOMBA 'O'
#define D_PUERTA 'S'
#define D_EXPLOSION '#'
/////
#define D_MASBOMBA 'B'
#define D_MASRANGO 'R'
#define PROB_RANGO 5
#define PROB_BOMBA 3
/////
///ESTADOS
#define E_DESACTIVADA 0
#define E_ACTIVAR 1
#define E_ACTIVA 2
#define E_VIVO 1
#define E_INMORTAL 2
#define E_MUERTO 3

///DEFINE
#define TIEMPOFIN 200
#define SEGUNDOS 1000

///MACROS
#define AMAYUSCULA(X) ((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X)

///ESTRUCTURAS
typedef struct{
    int x;
    int y;
}Posicion;
typedef struct{
    void *vec;
    size_t ce;
    size_t tam;
    size_t maxElem;
}tVector;

tVector* Comunes_CrearVector(size_t tam);
int Comunes_InsertarVector(tVector*, const void*);
void Comunes_DestruirVector(tVector*);
int Comunes_VectorArchivosGuardar(const char*, tVector*);
tVector* Comunes_VectorArchivosCargar(const char*, size_t);
int Comunes_EsLetraValida(int, int);
int Comunes_TeclaArribaAbajo(int);
int Comunes_ObtenerNumeroAleatorio(int, int);
int Comunes_ASegundos(DWORD);

#endif // COMUNES_H_INCLUDED
