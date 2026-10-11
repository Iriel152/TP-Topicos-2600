#include "Interfaz.h"
#include "PJ_Principal.h"
#include "Comunes.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "Bomba.h"
#include "Archivos.h"
int main()
{
    int opcion, fin = 0, seguir, temporizador;
    DWORD ahora, tiempo_enemigo, tiempo_reloj, tiempo_pj;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;
    vBombas *bombs;

    srand(time(NULL));

    if(ArchivosCargaDatos() == ERROR_ARCH)
        return ERROR_ARCH;

    while(!fin)
    {
        opcion = MostrarMenuPrincipal();
        while(opcion == NUEVAP)
        {

            mapa = Archivos_CargarMapa(MAPA_DAT);
            Mapa_RellenoObstaculosRombiples(mapa); //DESCOMENTAR PARA PONER OBSTACULOS

            personaje = Archivos_CargarPersonaje(PJ_Principal_DAT);
            PJ_Principal_AparicionRandom(mapa, personaje);
            LimpiarLadosPJ(mapa, personaje);

            enemigo = Archivos_CargarEnemigo(ENEMIGO_DAT);
            Enemigo_AparicionRandom(mapa, enemigo);

            bombs = crear_vec_bombs();

            seguir = CONTINUAR;
            tiempo_enemigo = GetTickCount();
            tiempo_pj = GetTickCount();
            tiempo_reloj = GetTickCount();

            while(seguir == CONTINUAR)
            {
                ahora = GetTickCount();


                temporizador = TIEMPOFIN - ASegundos(ahora - tiempo_reloj);
                renderizar(mapa, personaje, enemigo, temporizador);

                actualizar_bomba(bombs,mapa,ahora);
                EnemigoMovimientoxTiempo(ahora, enemigo, mapa, &tiempo_enemigo, personaje);
                PJMovimientoxTiempo(ahora, personaje, mapa, &tiempo_pj, &seguir,bombs);

                if(temporizador == 0)
                {
                    seguir = GAMEOVER;
                    PantallaGameOver();
                }
                if(seguir == SALIR)
                    seguir = MenuEjecucion();

                Sleep(16);
            }

            if(seguir != NUEVAP)
                opcion = -1;
            Mapa_DestruirMapa(mapa);
            PJ_Principal_DestruirPersonaje(personaje);
            Enemigo_Destruir(enemigo);
            free_vec_bombs(bombs);

            seguir = SALIR;
        }
       /* if(opcion == CARGARP)
        {

            if (partida_cargar_binario(RUTA_SAVE, &mapa, &personaje) == TODOOK)
            {
                bombs = Archivos_CargarBombas(BOMB_DAT);
                if(!bombs)
                    bombs = crear_vec_bombs();

                renderizar(mapa, personaje, enemigo, ahora - tiempo_reloj);
                PJ_Principal_DestruirPersonaje(personaje);
                Mapa_DestruirMapa(mapa);
            }
            else
            {
                printf("\nNo se pudo cargar la partida guardada.\n");
                _getch();
            }
        }*/
        /*else*/ if(opcion == SALIR)
            fin = 1;
    }
    return 0;
}
