#include "Bomba.h"
vBombas* crear_vec_bombs()
{
    vBombas *vbomb = (vBombas*)malloc(sizeof(vBombas));
    if (!vbomb)
        return NULL;
    inicializar_vec_bombs(vbomb);
    return vbomb;
}

void free_vec_bombs(vBombas *vbomb)
{
    if(vbomb != NULL)
        free(vbomb);
}

void inicializar_vec_bombs(vBombas *vbomb)
{
    int i=0;
    if(!vbomb)
        return NULL;
    for(i=0;i<MAX_BOMBAS; i++)
    {
        vbomb->bombas[i].activa=0;
        vbomb->bombas[i].turnos_restantes=0;
        vbomb->bombas[i].pos.x = -1;
        vbomb->bombas[i].pos.y = -1;
    }
}

//chequea si hay bomba xd

int hay_bomba(const vBombas *vbomb, int x, int y)
{
    int i=0;
    if(!vbomb)
        return NULL;
    for(i=0 ; i < MAX_BOMBAS ; i++)
    {
        if(vbomb->bombas[i].activa && vbomb->bombas[i].pos.x == x && vbomb->bombas[i].pos.y == y)
            return ENCONTRADO;
    }
    return NO_ENCONTRADO;
}

int bomba_poner(vBombas*vbomb, Mapa *m, Personaje *p)
{
    int i;
    if(!vbomb || !m || !p)
        return NULL;
    if(hay_bomba(vbomb, p->pos.x , p->pos.y))
        return NULL;

    for (i = 0; i < MAX_BOMBAS; i++)
    {
        if(!vbomb->bombas[i].activa) //TODAVÍA NO ESTOY PONDERANDO LA CANT DE BOMBAS DEL PJ
        {
            vbomb->bombas[i].activa = 1;
            vbomb->bombas[i].pos.x = p->pos.x;
            vbomb->bombas[i].pos.y = p->pos.y;
            vbomb->bombas[i].turnos_restantes = TIMER_BOMBA;
            m->celdas[p->pos.x][p->pos.y] = SIMBOLO_BOMBA;
            return TODOOK;
        }
    }
    return NULL;

}

//FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE NO LIMPIA DEL MAPA LA BOMBA

void actualizar_bomba(vBombas *vbomb, Mapa *m, int x_actual, int y_actual)
{
    int i, bomb_x, bomb_y;
    if (!vbomb || !m)
        return;
    for(i=0 ; i<MAX_BOMBAS ; i++)
    {
        if(vbomb->bombas[i].activa != 1)
            continue;
        vbomb->bombas[i].turnos_restantes--;

        if(vbomb->bombas[i].turnos_restantes <= 0)
        {
            bomb_x = vbomb->bombas[i].pos.x;
            bomb_y = vbomb->bombas[i].pos.y;

            if(bomb_x >= 0 && bomb_y >= 0 && m->celdas[bomb_x][bomb_y] == SIMBOLO_BOMBA)
            {
                m->celdas[bomb_x][bomb_y] = VACIO;
            }

            vbomb->bombas[i].activa = 0;
            vbomb->bombas[i].turnos_restantes = 0;
            vbomb->bombas[i].pos.x = -1;
            vbomb->bombas[i].pos.y = -1;
        }

    }
}


