#include "Juego.h"
int JuegoEnCurso(int opcion)
{
    int seguir, temporizador;
    DWORD ahora, tiempo_enemigo, tiempo_reloj, tiempo_pj;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;
    vBombas *bombs;
    tPuerta *puerta;

    srand(time(NULL));

    while(opcion == NUEVAP)
    {
        mapa = Archivos_CargarMapa(MAPA_DAT);
        Mapa_RellenoObstaculosRombiples(mapa);

        personaje = Archivos_CargarPersonaje(PJ_Principal_DAT);
        PJ_Principal_AparicionRandom(mapa, personaje);
        LimpiarLadosPJ(mapa, personaje);

        enemigo = Archivos_CargarEnemigo(ENEMIGO_DAT);
        Enemigo_AparicionRandom(mapa, enemigo);

        puerta = Archivos_CargarPuerta(PUERTA_DAT);

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

            if(!puerta->estado_puerta)
                AparicionPuerta(mapa,puerta);

            actualizar_bomba(bombs,mapa,ahora,puerta,enemigo,personaje);
            EnemigoMovimientoxTiempo(ahora, enemigo, mapa, &tiempo_enemigo, personaje);
            PJMovimientoxTiempo(ahora, personaje, mapa, &tiempo_pj, &seguir,bombs);

            if(temporizador == 0 || personaje->vidas == 0)
            {
                seguir = GAMEOVER;
                PantallaGameOver();
            }
            if(PJEnSalida(mapa,personaje))
            {
                seguir = VICTORIA;
                PantallaVictoria();
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
        Mapa_DestruirPuerta(puerta);
        free_vec_bombs(bombs);

        seguir = SALIR;
    }
    return seguir;
}
