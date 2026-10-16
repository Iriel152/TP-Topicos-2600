#include "Juego.h"
int Juego_EnCurso(int opcion)
{
    int seguir, temporizador;
    DWORD ahora, tiempo_enemigo, tiempo_reloj, tiempo_pj;
    tMapa *mapa;
    tPersonaje *personaje;
    tPuerta *puerta;
    tVector *vec_enemigo, *vec_bomba;

    srand(time(NULL));

    while(opcion == EP_NUEVAP)
    {
        mapa = Mapa_ArchivosCargar(MAPA_DAT);
        Mapa_RellenoObstaculosRombiples(mapa);

        personaje = PJ_ArchivosCargar(PJ_Principal_DAT);
        PJ_AparicionRandom(mapa, personaje);
        PJ_LimpiarLados(mapa, personaje);

        puerta = Puerta_ArchivosCargar(PUERTA_DAT);

        vec_enemigo = Comunes_VectorArchivosCargar(ENEMIGO_DAT, sizeof(tEnemigo));
        Enemigo_AparicionRandom(mapa, vec_enemigo, personaje);

        vec_bomba = Comunes_VectorArchivosCargar(BOMBA_DAT, sizeof(tBomba));

        seguir = EP_CONTINUAR;
        tiempo_enemigo = GetTickCount();
        tiempo_pj = GetTickCount();
        tiempo_reloj = GetTickCount();

        while(seguir == EP_CONTINUAR)
        {
            ahora = GetTickCount();

            temporizador = TIEMPOFIN - Comunes_ASegundos(ahora - tiempo_reloj);
            Interfaz_renderizar(mapa, personaje, vec_enemigo, vec_bomba, temporizador);

            if(!puerta->estado_puerta)
                Mapa_AparicionPuerta(mapa,puerta);

//            actualizar_bomba(vec_bomba, mapa, ahora, puerta, vec_enemigo, personaje);
            EnemigoMovimientoxTiempo(ahora, vec_enemigo, mapa, &tiempo_enemigo, personaje);
            PJ_MovimientoxTiempo(ahora, personaje, mapa, &tiempo_pj, &seguir, vec_bomba);

            if(temporizador == 0 || personaje->vidas == 0)
            {
                seguir = EP_GAMEOVER;
                Interfaz_PantallaMensaje(C_GAMEOVER);
            }
            if(PJ_EnSalida(mapa, personaje) == TODOOK)
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
        PJ_Destruir(personaje);
        Puerta_Destruir(puerta);
        Comunes_DestruirVector(vec_enemigo);
        Comunes_DestruirVector(vec_bomba);

        seguir = EP_SALIR;
    }
    return seguir;
}
