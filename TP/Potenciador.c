#include "Potenciador.h"
void Potenciador_RellenarVec(tVector *v, int lim)
{
    int i;
    tPotenciador pot;

    pot.estado = E_DESACTIVADA;
    pot.pos.x = 0;
    pot.pos.y = 0;
    pot.tipo = 0;
    pot.t_creacion = 0;
    pot.cant = CANT_POT;

    for(i = 0 ; i < lim ; i++)
        Comunes_InsertarVector(v, &pot);
}
void Potenciador_GenerarAleatorio(tVector *v_pot, tMapa *m, int x, int y, DWORD ahora)
{
    int i, aux, tipo_generado = 0;
    tPotenciador *pot;

    if (!v_pot || !v_pot->vec)
    {
        m->celdas[y][x] = DM_VACIO;
        return;
    }

    aux = Comunes_ObtenerNumeroAleatorio(1, 20);

    if(aux % PROB_RANGO == 0)
        tipo_generado = T_MAS_RANGO;
    else if(aux % PROB_BOMBA == 0)
        tipo_generado = T_MAS_BOMBA;

    if(tipo_generado == 0)
    {
        m->celdas[y][x] = DM_VACIO;
        return;
    }

    pot = (tPotenciador*)v_pot->vec;

    for(i = 0 ; i < v_pot->ce ; i++)
    {
        if((pot + i)->estado == E_DESACTIVADA)
        {
            (pot + i)->estado = E_ACTIVA;
            (pot + i)->tipo = tipo_generado;
            (pot + i)->pos.x = x;
            (pot + i)->pos.y = y;
            (pot + i)->t_creacion = ahora;

            if(tipo_generado == T_MAS_RANGO)
                m->celdas[y][x] = D_MASRANGO;
            else
                m->celdas[y][x] = D_MASBOMBA;

            break;
        }
    }
}
