#include "Mapa.h"
#include "Comunes.h"
#include "PJ_Principal.h"
void Mapa()
{
    int** mapa = crearMatriz(FILAS, COLUMNAS);
    int tecla;
    rellenarBordes(mapa, FILAS, COLUMNAS);

    rellenarObstaculosPerm(mapa, FILAS, COLUMNAS);
    AparicionRandomPJP(mapa);
    do{
        imprimirMatriz(mapa, FILAS, COLUMNAS);
        tecla = _getch();
        system("cls");
    }while(tecla!= ESC);
    MenuEjecucion();
    liberarMatriz(mapa, FILAS);
}
int** crearMatriz(int filas, int columnas) {
    int** matriz = (int**)malloc(filas * sizeof(int*));
    if (matriz == NULL) {
        perror("Error al asignar memoria para las filas");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));
        if (matriz[i] == NULL) {
            perror("Error al asignar memoria para las columnas");
            exit(EXIT_FAILURE);
        }
        // Inicializa el interior en 0
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = VACIO;
        }
    }
    return matriz;
}

// Rellena el techo (fila 0), el piso (última fila) y las paredes laterales
void rellenarBordes(int** matriz, int filas, int columnas) {
    // Techo (fila 0) y Piso (fila filas - 1)
    for (int j = 0; j < columnas; j++) {
        if(j==0 || j == columnas -1)
        {
            matriz[0][j] = PARED;
            matriz[filas - 1][j] = PARED;
        }
        else
        {
            matriz[0][j] = TECHO;
            matriz[filas - 1][j] = PISO;
        }
    }

    // Paredes laterales (columnas 0 y columnas - 1) para las filas intermedias
    for (int i = 1; i < filas - 1; i++) {
        matriz[i][0] = PARED;
        matriz[i][columnas - 1] = PARED;
    }
}
void rellenarObstaculosPerm(int** matriz, int filas, int columnas)
{
    for(int i = 2; i < filas -1; i = i +2)
    {
        for(int j= 2; j < columnas -2 ; j= j +2)
        matriz[i][j] = OBSTACULO;
    }
}
// Imprime la matriz como caracteres extendidos/ASCII o números
void imprimirMatriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] != VACIO) {
                // Se castea a unsigned char para renderizar los bloques si la consola lo soporta
                printf("%c", (unsigned char)matriz[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Libera la memoria reservada
void liberarMatriz(int** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
