#include "Bomba.h"
void Bomba_RellenarVec(tVector *v, int cant)
{
    int i;
    tBomba bomba;

    bomba.activa = 0;
    bomba.pos.x = 0;
    bomba.pos.y = 0;
    bomba.rango = 1;
    bomba.tiempo_bomba = 0;

    for(i = 0 ; i < cant ; i++)
        Insertar_Vector(v, &bomba);
}
//int inicializar_vec_bombs(vBombas *vbomb)
//{
//    if(!vbomb)
//        return ERROR_MEMORIA;
//
//    vbomb->rango=1;
//    if(insertar_bomba(vbomb) != TODOOK)
//       return ERROR_;
//    return TODOOK;
//}
//
////chequea si hay bomba xd
//
//int hay_bomba(const vBombas *vbomb, int x, int y)
//{
//    int i;
//    Bomba *pivot;
//
//    if(!vbomb)
//        return ERROR_;
//
//    pivot = vbomb->bombas;
//
//    for(i=0 ; i < vbomb->ce ; i++)
//    {
//        if(pivot->activa == 1 && pivot->pos.x == x && pivot->pos.y == y) // es lo mismo pivot->activa y pivot->activa == 1
//            return ENCONTRADO;
//        pivot++;
//    }
//    return NO_ENCONTRADO;
//}
//
///////*
////int bomba_poner(vBombas*vbomb, tMapa *m, tPersonaje *p)
////{
////    int i;
////    Bomba *pivot;
////
////    if(!vbomb || !m || !p)
////        return ERROR_;
////
////    if(hay_bomba(vbomb, p->pos.x , p->pos.y) == ENCONTRADO)
////        return ERROR_;
////
////    pivot = vbomb->bombas;
////
////    for (i = 0; i < vbomb->ce; i++)
////    {
////        if(!pivot->activa)
////        {
////            pivot->activa = 1;
////            pivot->pos.x = p->pos.x;
////            pivot->pos.y = p->pos.y;
////            pivot->tiempo_bomba = GetTickCount();
////            m->celdas[p->pos.x][p->pos.y] = SIMBOLO_BOMBA;
////            return TODOOK;
////        }
////        pivot++;
////    }
////    return ERROR_;
////
////}
////*///
////FUNCION PARA QUE EL TIMER DE LA BOMBA DECREMENTE A LAP AR QUE EL JUGADOR INTENTE MOVERSE NO LIMPIA DEL MAPA LA BOMBA
////FALTA FUNCION BORRAR BOMBA LO TENGO AHI TODO METIDO. EN EL MOMENTO Q BORRA LA BOMBA EPLOTA
//void actualizar_bomba(vBombas *vbomb, tMapa *m, DWORD ahora, tPuerta *puerta, tEnemigo *e, tPersonaje *pj)
//{
//    int i;
//    Bomba *pivot;
//    DWORD RELOJ_BOMBA = 3000;
//
//    if (!vbomb || !m)
//        return;
//
//    pivot = vbomb->bombas;
//
//    for(i=0 ; i<vbomb->ce; i++)
//    {
//        if(pivot->activa == 1)
//        {
//            if(ahora - pivot->tiempo_bomba >= RELOJ_BOMBA)
//            {
//                m->celdas[pivot->pos.y][pivot->pos.x] = D_EXPLOSION;
//
//                explotar_bomba(m,pivot->pos.x,pivot->pos.y,vbomb->rango,puerta,e,pj,ahora);
//
//                pivot->activa = 2;
//                pivot->tiempo_bomba = ahora;
//            }
//
//        }
//
//        else
//            if(pivot->activa == 2)
//        {
//            if(ahora - pivot->tiempo_bomba >= 300) //300 ms de retardo
//            {
//                m->celdas[pivot->pos.y][pivot->pos.x] = DM_VACIO;
//                limpiar_estela(m, pivot->pos.x, pivot->pos.y,vbomb->rango);
//
//                pivot->activa = 0;
//                pivot->pos.x = -1;
//                pivot->pos.y = -1;
//            }
//        }
//        pivot++;
//    }
//}
//
//
//void explotar_bomba(tMapa *m, int x, int y, int rango, tPuerta *puerta,tEnemigo *e,tPersonaje *pj,DWORD ahora)
//{
//    int i, j, aux_x, aux_y;
//    int dir_x[] = {-1,1,0,0};
//    int dir_y[] = {0,0,-1,1};
//
//    for (i=0 ; i<4 ; i++)
//    {
//        for(j=1; j<=rango; j++)
//        {
//            aux_x = x + (j * dir_x[i]);
//            aux_y = y + (j * dir_y[i]);
//            if(aux_x < 0 || aux_y < 0 || aux_y >= m->filas || aux_x >= m->columnas) //chequeamos bordes
//                break;             // no me gusta usar break, le voy a preguntar. Si lo tengo q hacer con bandera
//            if(m->celdas[aux_y][aux_x] == DM_PARED || m->celdas[aux_y][aux_x] == DM_OBSTACULO)
//                break;
//            if(m->celdas[aux_y][aux_x] == DM_ROMPIBLE)
//            {
//                if(puerta->estado_puerta == E_ACTIVAR)
//                {
//                    m->celdas[aux_y][aux_x] = D_PUERTA;
//                    puerta->estado_puerta = E_ACTIVA;
//                }else
//                    {
//                        m->celdas[aux_y][aux_x] = DM_VACIO;
//                    }
//                break;
//            }
//
//           if(e != NULL && e->esta_vivo == 1 && e->pos.x == aux_x && e->pos.y == aux_y)
//            {
//                e->esta_vivo = 0;
//                pj->puntaje += 270;
//                e->pos.x =0;
//                e->pos.y = 0;
//            }
//
//            if(pj!=NULL && pj->pos.x == aux_x && pj->pos.y == aux_y)
//            {
//                pj->vidas--;
//                pj->esta_vivo = 2;
//                pj->invul = ahora;
//            }
//
//            if(m->celdas[aux_y][aux_x] == DM_VACIO)
////               if(m->celdas[aux_y][aux_x] != DM_TECHO && m->celdas[aux_y][aux_x] != DM_PISO)  //Detectar q la estela no haya muro
//                    m->celdas[aux_y][aux_x] = D_EXPLOSION; //esto es como muestra, el tema es q no borra la estela.
//
//
//
//        }
//    }
//}
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
//
//int Archivos_GuardarBombas(const char* binPath, vBombas *vbomb)
//{
//    FILE *fbin;
//    fbin = fopen(binPath,"wb");
//
//    if(!fbin)
//        return ERROR_ARCH;
//    fwrite(&(vbomb->ce),sizeof(int),1,fbin);
//    fwrite(&(vbomb->rango),sizeof(int),1,fbin);
//    fwrite(&(vbomb->tam),sizeof(int),1,fbin);
//
//    if(vbomb->tam > 0 && vbomb->bombas != NULL)
//    {
//        fwrite(vbomb->bombas,sizeof(Bomba),vbomb->tam,fbin);
//    }
//    fclose(fbin);
//    return TODOOK;
//}
//
//vBombas* Archivos_CargarBombas(const char* binPath)
//{
//    FILE *pf;
//    vBombas *vbomb;
//
//    pf = fopen(binPath,"rb");
//    if(!pf)
//        return NULL;
//
//    vbomb = (vBombas*)malloc(sizeof(vBombas));
//    if(!vbomb)
//    {
//        fclose(pf);
//        return NULL;
//    }
//
//    fread(&(vbomb->ce),sizeof(int),1,pf);
//    fread(&(vbomb->rango),sizeof(int),1,pf);
//    fread(&(vbomb->tam),sizeof(int),1,pf);
//
//    vbomb->bombas = (Bomba*)malloc(sizeof(Bomba) * vbomb->tam);
//    if(!vbomb->bombas)
//    {
//        free(vbomb);
//        fclose(pf);
//        return NULL;
//    }
//
//    if (vbomb->tam > 0)
//        fread(vbomb->bombas,sizeof(Bomba),vbomb->tam,pf);
//
//    fclose(pf);
//    return vbomb;
//}
