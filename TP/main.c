#include "Interfaz.h"
#include "PJ_Principal.h"
#include "Comunes.h"
#include "Mapa.h"
int main() {
    int opcion = 0;
    int salir = 0;

    srand((unsigned int)time(NULL));

    while (!salir) {
        opcion = MostrarMenuPrincipal(); // Retorna 0: Nueva, 1: Cargar, 2: Salir

        if (opcion == 0) {
            // Nueva partida
            Mapa *mapa = Mapa_CrearMapa(FILAS, COLUMNAS);
            Mapa_RellenoObstaculos(mapa);

            Personaje *jugador = PJ_Princial_CrearPersonaje(1, 1, 3);
            PJ_Principal_AparicionRandom(jugador, mapa->filas, mapa->columnas);

            renderizar(mapa, jugador);

            // Al salir de la partida, liberamos la memoria limpia
            PJ_Principal_DestruirPersonaje(jugador);
            Mapa_DestruirMapa(mapa);
        }
        else if (opcion == 1) {
            // Cargar partida desde archivo binario
            Mapa *mapa = NULL;
            Personaje *jugador = NULL;

            if (partida_cargar_binario(RUTA_SAVE, &mapa, &jugador) == TODOOK) {
                renderizar(mapa, jugador);
                PJ_Principal_DestruirPersonaje(jugador);
                Mapa_DestruirMapa(mapa);
            } else {
                printf("\nNo se pudo cargar la partida guardada.\n");
                _getch();
            }
        }
        else if (opcion == 2) {
            salir = 1;
        }
    }

    return 0;
}
