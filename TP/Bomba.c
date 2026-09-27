#include "Bomba.h"

vBombas* crear_vec_bombs()
{
    vBombas *vbomb = (vBombas*)malloc(sizeof(vBombas));
    if (!vbomb)
        return ERROR_MEMORIA;
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
        return ERROR_MEMORIA;
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
        return ERROR_;
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
        return ERROR_;
    if(hay_bomba(vbomb, p->pos.x , p->pos.y))
        return ERROR_;

    for (i = 0; i < MAX_BOMBAS; i++)
    {
        if(!vbomb->bombas[i].activa) //TODAVÍA NO ESTOY PONDERANDO LA CANT DE BOMBAS DEL PJ
        {
            vbomb->bombas[i].activa = 1;
            vbomb->bombas[i].pos.x = p->pos.x;
            vbomb->bombas[i].pos.y = p->pos.y;
            vbomb->bombas[i].turnos_restantes = TIMER_BOMBA;
        }

        m->celdas[p->pos.x][p->pos.y] = SIMBOLO_BOMBA;
        return TODOOK;
    }
    return ERROR_;

}

//FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE

void actualizar_bomba(vBombas *vbomb, int x_actual, int y_actual)
{
    int i;
    if (!vbomb)
        return ERROR_;
    for(i=0 ; i<MAX_BOMBAS ; i++)
    {
        if(vbomb->bombas[i].activa != 1)
            return NO_ENCONTRADO;
        vbomb->bombas[i].turnos_restantes--;

        if(vbomb->bombas[i].turnos_restantes == 0)
        {
            vbomb->bombas[i].activa = 0;
            vbomb->bombas[i].turnos_restantes = 0;
            vbomb->bombas[i].pos.x = -1;
            vbomb->bombas[i].pos.y = -1;
        }

    }
}


