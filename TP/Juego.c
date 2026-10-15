#include "Juego.h"
int Juego_EnCurso(int opcion)
{
    int seguir, temporizador;
    DWORD ahora, tiempo_enemigo, tiempo_reloj, tiempo_pj;
    tMapa *mapa;
    tPersonaje *personaje;
    tEnemigo *enemigo;
    vBombas *bombs;
    tPuerta *puerta;

    srand(time(NULL));

    while(opcion == EP_NUEVAP)
    {
        mapa = Mapa_ArchivosCargar(MAPA_DAT);
        Mapa_RellenoObstaculosRombiples(mapa);

        personaje = Archivos_CargarPersonaje(PJ_Principal_DAT);
        PJ_Principal_AparicionRandom(mapa, personaje);
        LimpiarLadosPJ(mapa, personaje);

        enemigo = Enemigo_ArchivosCargar(ENEMIGO_DAT);
        Enemigo_AparicionRandom(mapa, enemigo);

        puerta = Puerta_ArchivosCargar(PUERTA_DAT);

        bombs = crear_vec_bombs();

        seguir = EP_CONTINUAR;
        tiempo_enemigo = GetTickCount();
        tiempo_pj = GetTickCount();
        tiempo_reloj = GetTickCount();

        while(seguir == EP_CONTINUAR)
        {
            ahora = GetTickCount();

            temporizador = TIEMPOFIN - ASegundos(ahora - tiempo_reloj);
            Interfaz_renderizar(mapa, personaje, enemigo, temporizador);

            if(!puerta->estado_puerta)
                Mapa_AparicionPuerta(mapa,puerta);

            actualizar_bomba(bombs,mapa,ahora,puerta,enemigo,personaje);
            EnemigoMovimientoxTiempo(ahora, enemigo, mapa, &tiempo_enemigo, personaje);
            PJMovimientoxTiempo(ahora, personaje, mapa, &tiempo_pj, &seguir,bombs);

            if(temporizador == 0 || personaje->vidas == 0)
            {
                seguir = EP_GAMEOVER;
                Interfaz_PantallaMensaje(C_GAMEOVER);
            }
            if(PJEnSalida(mapa,personaje) == TODOOK)
            {
                seguir = EP_VICTORIA;
                Interfaz_PantallaMensaje(C_VICTORIA);
            }

            if(seguir == EP_SALIR)
                seguir = Interfaz_MenuEjecucion();

            Sleep(16);
        }

        if(seguir != EP_NUEVAP)
            opcion = -1;

        Mapa_DestruirMapa(mapa);
        PJ_Principal_DestruirPersonaje(personaje);
        Enemigo_Destruir(enemigo);
        Puerta_Destruir(puerta);
        free_vec_bombs(bombs);

        seguir = EP_SALIR;
    }
    return seguir;
}
