#include "Juego.h"
int main()
{
    int opcion, fin = 0;

    if(ArchivosCargaDatos() == ERROR_ARCH)
        return ERROR_ARCH;

    while(!fin)
    {
        opcion = Interfaz_MostrarMenuPrincipal();
        switch(opcion)
        {
            case EP_NUEVAP:
                opcion = Juego_EnCurso(opcion);
                break;
            case EP_SALIR:
                fin = 1;
                break;
        }
    }
    return 0;
}
