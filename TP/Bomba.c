#include "Bomba.h"

vBombas* crear_vec_bombs()
{
    vBombas *vbomb = (vBombas*)malloc(sizeof(vBombas));
    if (!vbomb)
        return NULL;
    vbomb->bombas = (Bomba*)malloc(sizeof(Bomba)*MAX_BOMBAS);
    if (!vbomb->bombas)
    {
        free(vbomb);
        return NULL;
    }

    vbomb->ce=0;
    vbomb->tam=MAX_BOMBAS;

    if(inicializar_vec_bombs(vbomb)!= TODOOK)
    {
        free_vec_bombs(vbomb);
        return NULL;
    }

    return vbomb;
}

void free_vec_bombs(vBombas *vbomb)
{
    if(vbomb != NULL)
        {
            if(vbomb->bombas != NULL)
                free(vbomb->bombas);
            free(vbomb);
        }
}

int insertar_bomba(vBombas*vbomb)
{
    Bomba b;

    if(!vbomb || vbomb->ce >= vbomb->tam)
        return ERROR_;

    b.activa = 0;
    b.pos.x = -1;
    b.pos.y = -1;
    b.turnos_restantes = 0;

    *(vbomb->bombas + vbomb->ce) = b;
    vbomb->ce++;

    return TODOOK;
}

int inicializar_vec_bombs(vBombas *vbomb)
{
    if(!vbomb)
        return NULL;

    vbomb->rango=1;
    if(insertar_bomba(vbomb) != TODOOK)
       return ERROR_;
    return TODOOK;
}

//chequea si hay bomba xd

int hay_bomba(const vBombas *vbomb, int x, int y)
{
    int i;
    Bomba *pivot;

    if(!vbomb)
        return ERROR_;

    pivot = vbomb->bombas;

    for(i=0 ; i < vbomb->ce ; i++)
    {
        if(pivot->activa == 1 && pivot->pos.x == x && pivot->pos.y == y) // es lo mismo pivot->activa y pivot->activa == 1
            return ENCONTRADO;
        pivot++;
    }
    return NO_ENCONTRADO;
}


int bomba_poner(vBombas*vbomb, Mapa *m, Personaje *p)
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
            pivot->turnos_restantes = TIMER_BOMBA;
            m->celdas[p->pos.x][p->pos.y] = SIMBOLO_BOMBA;
            return TODOOK;
        }
        pivot++;
    }
    return ERROR_;

}

//FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE NO LIMPIA DEL MAPA LA BOMBA
//FALTA FUNCION BORRAR BOMBA LO TENGO AHI TODO METIDO. EN EL MOMENTO Q BORRA LA BOMBA EPLOTA
void actualizar_bomba(vBombas *vbomb, Mapa *m)
{
    int i;
    Bomba *pivot;

    if (!vbomb || !m)
        return;

    pivot = vbomb->bombas;

    for(i=0 ; i<vbomb->ce; i++)
    {
        if(pivot->activa)
        {
            vbomb->bombas[i].turnos_restantes--;

            if(vbomb->bombas[i].turnos_restantes <= 0)
            {
                m->celdas[pivot->pos.x][pivot->pos.y] = VACIO;

                explotar_bomba(m,pivot->pos.x,pivot->pos.y,vbomb->rango);

                pivot->activa = 0;
                pivot->pos.x = -1;
                pivot->pos.y = -1;
            }
            pivot++;
        }
    }
}


void explotar_bomba(Mapa *m, int x, int y, int rango)
{
    int i, j, aux_x, aux_y;
    int dir_x[] = {-1,1,0,0};
    int dir_y[] = {0,0,-1,1};

    for (i=0 ; i<4 ; i++)
    {
        for(j=1; j<=rango; j++)
        {
            aux_x = x + (j * dir_x[i]);
            aux_y = y + (j * dir_y[i]);
            if(aux_x < 0 || aux_y < 0 || aux_x >= m->filas || aux_y >= m->columnas) //chequeamos bordes
                break;             // no me gusta usar break, le voy a preguntar. Si lo tengo q hacer con bandera
            if(m->celdas[aux_x][aux_y] == PARED || m->celdas[aux_x][aux_y] == OBSTACULO)
                break;
            if(m->celdas[aux_x][aux_y] == ROMPIBLE)
            {
                m->celdas[aux_x][aux_y] = VACIO;
                break;
            }
            /*if(m->celdas[aux_x][aux_y] == VACIO)
                m->celdas[aux_x][aux_y] = '#';*/ //esto es como muestra, el tema es q no borra la estela.
        }

    }
}

