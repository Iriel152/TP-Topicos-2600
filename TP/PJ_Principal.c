#include "PJ_Principal.h"
#include "Mapa.h"
void AparicionRandomPJP(int** matriz)
{
    int posicion;
    srand(time(NULL));
    posicion = ObtenerNumeroAleatorio(1,4);
    switch(posicion)
    {
        case 1:
            matriz[1][1]= PJP;
            break;
        case 2:
            matriz[FILAS - 2][1]= PJP;
            break;
        case 3:
            matriz[1][COLUMNAS - 2]= PJP;
            break;
        case 4:
            matriz[FILAS - 2][COLUMNAS - 2]= PJP;
            break;
    }
}
