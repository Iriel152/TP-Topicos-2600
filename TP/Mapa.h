#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#define PARED 219
#define TECHO 223
#define PISO  220
#define VACIO 0
#define FILAS 15
#define COLUMNAS 49
#define OBSTACULO 219
#define ROMPIBLE 176
#define ESC 27

typedef struct{
    int filas;
    int columnas;
    int **celdas;
}Mapa;
Mapa* Mapa_CrearMapa(int,  int);
void Mapa_DestruirMapa(Mapa *);

#endif // MAPA_H_INCLUDED
