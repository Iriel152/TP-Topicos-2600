#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#define PARED 219
#define TECHO 223
#define PISO  220
#define VACIO 0
#define FILAS 15
#define COLUMNAS 49
#define OBSTACULO 178
#define ESC 27

void Mapa();
int** crearMatriz(int filas, int columnas);
void rellenarBordes(int** matriz, int filas, int columnas);
void rellenarObstaculosPerm(int** matriz, int filas, int columnas);
void imprimirMatriz(int** matriz, int filas, int columnas);
void liberarMatriz(int** matriz, int filas);

#endif // MAPA_H_INCLUDED
