#include "Juego.h"
int main()
{
    int opcion, fin = 0;

    if(ArchivosCargaDatos() == ERROR_ARCH)
        return ERROR_ARCH;

    while(!fin)
    {
        opcion = MostrarMenuPrincipal();
        switch(opcion)
        {
            case NUEVAP:
                opcion = JuegoEnCurso(opcion);
                break;
            case CARGARP: //temporal
                fin = 1;
                break;
            case SALIR:
                fin = 1;
                break;
        }
    }
    return 0;
}
