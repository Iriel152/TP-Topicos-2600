#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

///.h
#include "Enemigo.h"

///BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

///TEXTO
#define C_TITULO "BOMBERMAN"
#define C_GAMEOVER "GAMEOVER"
#define C_VICTORIA "VICTORIA"
///FORMATO TEXTO
#define T_CENTRADO 52
#define T_SELECCIONADO 2
#define T_NO_SELECCIONADO 0
///COLORES
#define COLOR_RESET   "\033[0m"
#define COLOR_ACTIVO  "\033[1;30;47m"
#define COLOR_NORMAL  "\033[0;37m"

int Interfaz_MostrarMenuPrincipal(void);
void Interfaz_PantallaInicio(int *, const char**, int);
void Interfaz_TituloSistema(void);
void Interfaz_Separador(int);
void Interfaz_AlinearCentro(const char*, int, const char*, int);
int Interfaz_MenuEjecucion(void);
void Interfaz_renderizar(const tMapa *m, const tPersonaje *p, tVector *e, tVector *b, int temporizador);
void Interfaz_PantallaMensaje(const char*);

#endif // INTERFAZ_H_INCLUDED
