#include "Bomba.h"
void Bomba_RellenarVec(tVector *v, int cant)
{
    int i;
    tBomba bomba;

    bomba.activa = E_DESACTIVADA;
    bomba.explosion = E_DESACTIVADA;
    bomba.pos.x = 0;
    bomba.pos.y = 0;
    bomba.rango = 1;
    bomba.tiempo_bomba = 0;

    for(i = 0 ; i < cant ; i++)
        Comunes_InsertarVector(v, &bomba);
}
int Bomba_Existencia(tVector *v, int x, int y)
{
    int i;
    tBomba *bomba;

    bomba = (tBomba*)v->vec;

    for(i = 0 ; i < v->ce ; i++)
    {
        if((bomba + i)->activa == 1 &&
           (bomba + i)->pos.x == x &&
           (bomba + i)->pos.y == y)
            return ENCONTRADO;
    }
    return NO_ENCONTRADO;
}
////FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE NO LIMPIA DEL MAPA LA BOMBA
////FALTA FUNCION BORRAR BOMBA LO TENGO AHI TODO METIDO. EN EL MOMENTO Q BORRA LA BOMBA EPLOTA
//void actualizar_bomba(tVector *v, DWORD ahora)
//{
//    int i;
//    tBomba *bomba;
//    DWORD RELOJ_BOMBA = 3000;
//
//    if (!v)
//        return;
//
//    bomba = (tBomba*)v->vec;
//
//    for(i = 0 ; i < v->ce ; i++)
//    {
//        if((bomba + i)->activa == E_ACTIVAR)
//        {
//            if(ahora - (bomba + i)->tiempo_bomba >= RELOJ_BOMBA)
//            {
//                (bomba + i)->explosion = E_ACTIVAR;
//                (bomba + i)->activa = E_ACTIVA;
//                (bomba + i)->tiempo_bomba = ahora;
//            }
//
//        }
//        else
//            if((bomba + i)->activa == E_ACTIVA)
//            {
//                if(ahora - (bomba + i)->tiempo_bomba >= 300) //300 ms de retardo
//                {
//                    (bomba + i)->explosion = E_ACTIVA;
////                limpiar_estela(m, pivot->pos.x, pivot->pos.y,vbomb->rango);
//
//                    (bomba + i)->activa = E_DESACTIVADA;
//                    (bomba + i)->pos.x = -1;
//                    (bomba + i)->pos.y = -1;
//                }
//        }
//    }
//}
//
//

//
//void limpiar_estela(tMapa *m, int x, int y, int rango)
//{
//    int i, j, aux_x, aux_y;
//    int dir_x[] = {-1,1,0,0};
//    int dir_y[] = {0,0,-1,1};
//
//    if(m->celdas[y][x] == D_EXPLOSION)
//        m->celdas[y][x]= DM_VACIO;
//
//    for (i=0 ; i<4 ; i++)
//    {
//        for(j=1; j<=rango; j++)
//        {
//            aux_x = x + (j * dir_x[i]);
//            aux_y = y + (j * dir_y[i]);
//            if((aux_x < 0) || (aux_y < 0) || (aux_y >= m->filas) || (aux_x >= m->columnas))
//                break;
//            if(m->celdas[aux_y][aux_x] == DM_PARED || m->celdas[aux_y][aux_x] == DM_OBSTACULO)
//                break;
//
//            if(m->celdas[aux_y][aux_x] == D_EXPLOSION)
//               m->celdas[aux_y][aux_x] = DM_VACIO;
//        }
//    }
//
//
//}
