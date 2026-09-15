#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Mapa.h"
#include "PJ_Principal.h"

///FORMATO TEXTO
#define Titulo "BOMBERMAN"
#define n_centrado 52
#define T_seleccionado 2
#define T_No_seleccionado 0
#define TOTAL_OPCIONES 3

///COLORES
#define COLOR_RESET   "\033[0m"
#define COLOR_ACTIVO  "\033[1;30;47m" // Texto negro, fondo blanco
#define COLOR_NORMAL  "\033[0;37m"
#define RUTA_SAVE "partida.dat"

void MenuInicio();
void PantallaInicio(int *, const char *opciones[]);
void Separador(int);
void TituloSistema();
void AlinearCentro(const char*, int, const char *, int);
int SeleccionMenuInicio(int *seleccion, const char *opciones[]);
void MenuEjecucion();
int SeleccionMenuPartida(int *seleccion, const char *opciones[]);
void renderizar(const Mapa *m, const Personaje *p);
int MostrarMenuPrincipal();

#endif // INTERFAZ_H_INCLUDED
