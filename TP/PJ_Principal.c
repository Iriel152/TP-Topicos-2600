#include "PJ_Principal.h"
tPersonaje* PJ_Crear(void)
{
    tPersonaje *p;

    p = (tPersonaje*)malloc(sizeof(tPersonaje));
    if(!p)
        return NULL;

    p->pos.x = 0;
    p->pos.y = 0;
    p->vidas = VIDAS_BASE;
    p->alcance_bomba = 2;
    p->esta_vivo = E_VIVO;
    p->velocidad = 550;
    p->puntaje = 0;
    p->invul = 0;

    return p;
}
void PJ_Destruir(tPersonaje *p)
{
    if(p)
        free(p);
}
int PJ_ArchivosGuardar(const char* binPath, tPersonaje *personaje)
{
    FILE *fbin;
    fbin = fopen(binPath, "wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(personaje->alcance_bomba), sizeof(int), 1, fbin);
    fwrite(&(personaje->esta_vivo), sizeof(int), 1, fbin);
    fwrite(&(personaje->pos), sizeof(personaje->pos), 1, fbin);
    fwrite(&(personaje->velocidad), sizeof(int), 1, fbin);
    fwrite(&(personaje->vidas), sizeof(int), 1, fbin);
    fwrite(&(personaje->puntaje), sizeof(int), 1, fbin);

    fclose(fbin);
    return TODOOK;
}
tPersonaje* PJ_ArchivosCargar(const char* binPath)
{
    tPersonaje *personaje;
    FILE *pf;

    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    personaje = (tPersonaje*)malloc(sizeof(tPersonaje));
    if(!personaje)
    {
        fclose(pf);
        return NULL;
    }

    fread(&(personaje->alcance_bomba), sizeof(int), 1, pf);
    fread(&(personaje->esta_vivo), sizeof(int), 1, pf);
    fread(&(personaje->pos), sizeof(personaje->pos), 1, pf);
    fread(&(personaje->velocidad), sizeof(int), 1, pf);
    fread(&(personaje->vidas), sizeof(int), 1, pf);
    fread(&(personaje->puntaje), sizeof(int), 1, pf);

    personaje->invul = 0;

    fclose(pf);
    return personaje;
}
void PJ_AparicionRandom(tMapa *m, tPersonaje *p)
{
    int esquina;

    esquina = Comunes_ObtenerNumeroAleatorio(1,4);

    if(!p || !m)
        return;

    switch(esquina)
    {
        case 1:
            p->pos.x = 1;
            p->pos.y = 1;
            break;
        case 2:
            p->pos.x = 1;
            p->pos.y = m->filas - 2;
            break;
        case 3:
            p->pos.x = m->columnas - 2;
            p->pos.y = 1;
            break;
        case 4:
            p->pos.x = m->columnas - 2;
            p->pos.y = m->filas - 2;
            break;
    }
}
void PJ_LimpiarLados(tMapa *m, tPersonaje *p)
{
    int f, c, *pt;

    f = p->pos.y;
    c = p->pos.x;

    m->celdas[f][c] = DM_VACIO;

    if (f - 1 >= 0)
    {
        pt = &m->celdas[f - 1][c];
        if (*pt != DM_PARED && *pt != DM_TECHO && *pt != DM_OBSTACULO)
            *pt = DM_VACIO;
    }

    if (f + 1 < m->filas)
    {
        pt = &m->celdas[f + 1][c];
        if (*pt != DM_PARED && *pt != DM_PISO && *pt != DM_OBSTACULO)
            *pt = DM_VACIO;
    }

    if (c - 1 >= 0)
    {
        pt = &m->celdas[f][c - 1];
        if (*pt != DM_PARED && *pt != DM_OBSTACULO)
            *pt = DM_VACIO;
    }

    if (c + 1 < m->columnas)
    {
        pt = &m->celdas[f][c + 1];
        if (*pt != DM_PARED && *pt != DM_OBSTACULO)
            *pt = DM_VACIO;
    }
}
void PJ_MovimientoxTiempo(DWORD ahora, tPersonaje *personaje, tMapa *mapa,
                          DWORD *tiempo_personaje, int *seguir, tVector *vbomb,
                          tVector *v_pot)
{
    if(personaje->esta_vivo == E_INMORTAL && (ahora - personaje->invul) >= TIMER_INVUL)
            personaje->esta_vivo = E_VIVO;
    if(_kbhit())
    {
        if(ahora - (*tiempo_personaje) >= personaje->velocidad)
        {
            *seguir = PJ_Movimiento(mapa, personaje, vbomb, v_pot);
            *tiempo_personaje = ahora;
            while(_kbhit())
                _getch();
        }
    }
}
int PJ_Movimiento(tMapa *m, tPersonaje *p, tVector *vbomb, tVector *v_pot)
{
    char tecla;
    int NuevaFila, NuevaColumna, escenario;

    escenario = EP_CONTINUAR;
    tecla = _getch();
    NuevaFila = p->pos.y;
    NuevaColumna = p->pos.x;

    tecla = AMAYUSCULA(tecla);

    switch(tecla)
    {
        case TEC_ARRIBA:
            NuevaFila--;
            break;
        case TEC_ABAJO:
            NuevaFila++;
            break;
        case TEC_IZQUIERDA:
            NuevaColumna--;
            break;
        case TEC_DERECHA:
            NuevaColumna++;
            break;
        case TEC_PONERSELEC:
            PJ_PoneBomba(vbomb, m, p);
            break;
        case TEC_ESC:
            escenario = EP_SALIR;
            break;
    }

    if(Mapa_MovimientoValido(m, NuevaFila, NuevaColumna, 1) == TODOOK)
    {
        p->pos.y = NuevaFila;
        p->pos.x = NuevaColumna;

        PJ_EnPotenciador(m, p, vbomb, v_pot);
    }

    return escenario;
}
int PJ_PoneBomba(tVector *v, tMapa *m, tPersonaje *p)
{
    int i;
    tBomba *bomba;

    if(!v || !m || !p)
        return ERROR_MEMORIA;

    if(Bomba_Existencia(v, p->pos.x , p->pos.y) == ENCONTRADO)
        return ENCONTRADO;

    bomba = (tBomba*)v->vec;

    for (i = 0 ; i < v->ce ; i++)
    {
        if((bomba + i)->activa == E_DESACTIVADA)
        {
            (bomba + i)->activa = E_ACTIVAR;
            (bomba + i)->pos.x = p->pos.x;
            (bomba + i)->pos.y = p->pos.y;
            (bomba + i)->tiempo_bomba = GetTickCount();
            return TODOOK;
        }
    }
    return ENCONTRADO;
}
int PJ_EnSalida(tMapa *m, tPersonaje *p)
{
    int band;

    band = ERROR_;
    if(m->celdas[p->pos.y][p->pos.x] == D_PUERTA)
        band = TODOOK;

    return band;
}
//////
void PJ_EnPotenciador(tMapa *m, tPersonaje *p, tVector *v_b, tVector *v_pot)
{
    int i;

    if(!v_pot || !v_pot->vec)
        return;

     tPotenciador *pot = (tPotenciador*)v_pot->vec;

    for(i = 0; i < v_pot->ce ; i++)
    {
        if((pot + i)->estado == E_ACTIVA &&
           (pot + i)->pos.x == p->pos.x &&
           (pot + i)->pos.y == p->pos.y)
           {
                if((pot + i)->tipo == T_MAS_RANGO)
                {
                    if(p->alcance_bomba <= 10)
                        p->alcance_bomba++;
                }
                else if((pot + i)->tipo == T_MAS_BOMBA)
                    Bomba_RellenarVec(v_b,1);

                (pot + i)->estado = E_DESACTIVADA;
                (pot + i)->pos.x = 0;
                (pot + i)->pos.y = 0;

                m->celdas[p->pos.y][p->pos.x] = DM_VACIO;
                break;
           }

    }

}
//////
