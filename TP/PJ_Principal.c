#include "PJ_Principal.h"
tPersonaje* PJ_Princial_CrearPersonaje()
{
    tPersonaje *p = (tPersonaje*)malloc(sizeof(tPersonaje));
    if(!p)
        return NULL;
    p->pos.x = 0;
    p->pos.y = 0;
    p->vidas = VIDAS_BASE;
    p->alcance_bomba = 2;
    p->esta_vivo = 1;
    p->velocidad = 550;
    p->puntaje = 0;

    return p;
}
void PJ_Principal_DestruirPersonaje(tPersonaje *p)
{
    if(p)
        free(p);
}
void PJ_Principal_AparicionRandom(tMapa *m, tPersonaje *p)
{
    int esquina = ObtenerNumeroAleatorio(1,4);
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
void LimpiarLadosPJ(tMapa *m, tPersonaje *p)
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
int MovimientoPJ(tMapa *m, tPersonaje *p, vBombas *vbomb)
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
            bomba_poner(vbomb,m,p);
            break;
        case TEC_ESC:
            escenario = EP_SALIR;
            break;
    }

    if(MovimientoValido(m, NuevaFila, NuevaColumna, 1) == TODOOK)
    {
        p->pos.y = NuevaFila;
        p->pos.x = NuevaColumna;
    }

    return escenario;
}
int Archivos_GuardarPersonaje(const char* binPath, tPersonaje *personaje)
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
tPersonaje* Archivos_CargarPersonaje(const char* binPath)
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

    fclose(pf);
    return personaje;
}
void PJMovimientoxTiempo(DWORD ahora, tPersonaje *personaje, tMapa *mapa, DWORD *tiempo_personaje, int *seguir, vBombas *vbomb)
{
    if(_kbhit())
    {
        if(personaje->esta_vivo == 2 && (ahora - personaje->invul) >= TIMER_INVUL)
        {
            personaje->esta_vivo = 1;
        }
        if(ahora - (*tiempo_personaje) >= personaje->velocidad)
        {
            *seguir = MovimientoPJ(mapa, personaje, vbomb);
            *tiempo_personaje = ahora;
        }
        else
            while(_kbhit()) _getch();
    }
}
int bomba_poner(vBombas*vbomb, tMapa *m, tPersonaje *p)
{
    int i;
    Bomba *pivot;

    if(!vbomb || !m || !p)
        return ERROR_;

    if(hay_bomba(vbomb, p->pos.x , p->pos.y) == ENCONTRADO)
        return ERROR_;

    pivot = vbomb->bombas;

    for (i = 0; i < vbomb->ce; i++)
    {
        if(!pivot->activa)
        {
            pivot->activa = 1;
            pivot->pos.x = p->pos.x;
            pivot->pos.y = p->pos.y;
            pivot->tiempo_bomba = GetTickCount();
            m->celdas[p->pos.y][p->pos.x] = D_BOMBA;
            return TODOOK;
        }
        pivot++;
    }
    return ERROR_;

}
int PJEnSalida(tMapa *m, tPersonaje *p)
{
    if(m->celdas[p->pos.y][p->pos.x] == D_PUERTA)
    {
        return 1;
    }

    return 0;
}
