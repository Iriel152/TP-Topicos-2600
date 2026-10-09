#include "Interfaz.h"
#include "PJ_Principal.h"
#include "Comunes.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "Bomba.h"
#include "Archivos.h"
int main()
{
    int opcion, fin = 0, seguir;
    DWORD ahora, tiempo_enemigo;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;

    srand(time(NULL));

    if(ArchivosCargaDatos() == ERROR_ARCH)
        return ERROR_ARCH;

    while(!fin)
    {
        opcion = MostrarMenuPrincipal();
        while(opcion == NUEVAP)
        {
            mapa = Archivos_CargarMapa(MAPA_DAT);
            Mapa_RellenoObstaculosRombiples(mapa);

            personaje = Archivos_CargarPersonaje(PJ_DAT);
            PJ_Principal_AparicionRandom(mapa, personaje);
            LimpiarLadosPJ(mapa, personaje);

            enemigo = Archivos_CargarEnemigo(ENEMIGO_DAT);
            Enemigo_AparicionRandom(mapa, enemigo);

            seguir = CONTINUAR;
            tiempo_enemigo = GetTickCount();

            while(seguir == CONTINUAR)
            {
                ahora = GetTickCount();//COMENTAR PARA HACER ANDAR EL PJ
                if(ahora - tiempo_enemigo >= 1000)//COMENTAR PARA HACER ANDAR EL PJ
                {//COMENTAR PARA HACER ANDAR EL PJ
                    EnemigoMover(mapa, enemigo);//COMENTAR PARA HACER ANDAR EL PJ
                    tiempo_enemigo = ahora;//COMENTAR PARA HACER ANDAR EL PJ
                }//COMENTAR PARA HACER ANDAR EL PJ
                renderizar(mapa, personaje, enemigo);
//                seguir = MovimientoPJ(mapa, personaje/*, Bomba */);//COMENTAR PARA HACER ANDAR EL ENEMIGO
                if(seguir == SALIR)
                    seguir = MenuEjecucion();
                Sleep(16);
            }

            if(seguir != NUEVAP)
                opcion = -1;
            Mapa_DestruirMapa(mapa);
            PJ_Principal_DestruirPersonaje(personaje);
            Enemigo_Destruir(enemigo);

            seguir = SALIR;
        }
        if(opcion == CARGARP)
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
        else if(opcion == SALIR)
            fin = 1;
    }
    return 0;
}
