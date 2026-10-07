#include "Interfaz.h"
#include "PJ_Principal.h"
#include "Comunes.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "Bomba.h"
#include "Archivos.h"
int main()
{
    int opcion = 0, salir = 0, seguir = 1;

    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;

    if(ArchivosCargaDatos() == ERROR_ARCH)
        return ERROR_ARCH;

    while(!salir)
    {
        opcion = MostrarMenuPrincipal();
        if(opcion == 0)
        {
            mapa = Archivos_CargarMapa(MAPA_DAT);

            personaje = Archivos_CargarPersonaje(PJ_DAT);
            PJ_Principal_AparicionRandom(mapa, personaje);
            LimpiarLadosPJ(mapa, personaje);

            enemigo = Archivos_CargarEnemigo(ENEMIGO_DAT);
            Enemigo_AparicionRandom(mapa, enemigo);

            while(seguir)
            {
                system("cls");
                renderizar(mapa, personaje, enemigo);
                seguir = MovimientoPJ(mapa, personaje/*, Bomba */);
            }

            Mapa_DestruirMapa(mapa);
            PJ_Principal_DestruirPersonaje(personaje);
            Enemigo_Destruir(enemigo);

            seguir = 1;
        }else if(opcion == 1)
        {

            if (partida_cargar_binario(RUTA_SAVE, &mapa, &personaje) == TODOOK)
            {
                renderizar(mapa, personaje, enemigo);
                PJ_Principal_DestruirPersonaje(personaje);
                Mapa_DestruirMapa(mapa);
            }
            else
            {
                printf("\nNo se pudo cargar la partida guardada.\n");
                _getch();
            }
        }
        else if(opcion == 2)
            salir = 1;
    }
    return 0;
}
