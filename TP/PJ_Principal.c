#include "PJ_Principal.h"
tPersonaje* PJ_Princial_CrearPersonaje(int fila, int col, int vidas)
{
    tPersonaje *p = (tPersonaje*)malloc(sizeof(tPersonaje));
    if(!p)
        return NULL;
    p->pos.x = fila;
    p->pos.y = col;
    p->vidas = vidas;
    p->alcance_bomba = 2;
    p->esta_vivo = 1;
    p->velocidad = 1;

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
    if(!p)
        return;// NULL;
    switch(esquina)
    {
        case 1:
            p->pos.x = 1;
            p->pos.y = 1;
            break;
        case 2:
            p->pos.x = m->filas - 2;
            p->pos.y = 1;
            break;
        case 3:
            p->pos.x = 1;
            p->pos.y = m->columnas - 2;
            break;
        case 4:
            p->pos.x = m->filas - 2;
            p->pos.y = m->columnas - 2;
            break;
    }
}

void LimpiarLadosPJ(tMapa *m, tPersonaje *p)
{
    int* arriba = &m->celdas[p->pos.x-1][p->pos.y];
    int* abajo = &m->celdas[p->pos.x+1][p->pos.y];
    int* izquierda = &m->celdas[p->pos.x][p->pos.y-1];
    int* derecha = &m->celdas[p->pos.x][p->pos.y+1];

    m->celdas[p->pos.x][p->pos.y] = VACIO;

    if(*arriba != PARED && *arriba != TECHO && *arriba != PISO)
    {
        *arriba = VACIO;
    }
    if(*abajo != PARED && *abajo != TECHO && *abajo != PISO)
    {
        *abajo = VACIO;
    }
    if(*izquierda != PARED && *izquierda != TECHO && *izquierda != PISO)
    {
        *izquierda = VACIO;
    }
    if(*derecha != PARED && *derecha != TECHO && *derecha != PISO)
    {
        *derecha = VACIO;
    }
}

void NuevaPosicionPJ(tMapa *m, tPersonaje *p, int NuevaPosX, int NuevaPosY/*, vBombas *vbombs*/)
{
    if(m->celdas[NuevaPosX][NuevaPosY] == VACIO)
    {
        p->pos.x = NuevaPosX;
        p->pos.y = NuevaPosY;
    }
}

int MovimientoPJ(tMapa *m, tPersonaje *p/*, vBombas *vbomb*/)
{
    char tecla = _getch();
//    int hay_mov = 0;

    tecla = AMAYUSCULA(tecla);

    switch(tecla)
    {
        case 'W': NuevaPosicionPJ(m,p,p->pos.x-1,p->pos.y/*, vbomb*/); /*hay_mov = 1*/; break;
        case 'S': NuevaPosicionPJ(m,p,p->pos.x+1,p->pos.y/*, vbomb*/); /*hay_mov = 1*/; break;
        case 'A': NuevaPosicionPJ(m,p,p->pos.x,p->pos.y-1/*, vbomb*/); /*hay_mov = 1*/; break;
        case 'D': NuevaPosicionPJ(m,p,p->pos.x,p->pos.y+1/*, vbomb*/); /*hay_mov = 1*/; break;
//        case 'B': bomba_poner(vbomb,m,p); hay_mov = 1; break;
        case 27: return SALIR; break;
        default: return SEGUIR; break;
    }
//    if (hay_mov)
//        actualizar_bomba(vbomb,m);

    return SEGUIR;
}
int Archivos_GuardarPersonaje(const char* binPath, tPersonaje *personaje)
{
    FILE *fbin;
    fbin = fopen(binPath, "wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(personaje->alcance_bomba), sizeof(int), 1, fbin);
    fwrite(&(personaje->esta_vivo), sizeof(int), 1, fbin);
    fwrite(&(personaje->pos), sizeof(int), 1, fbin);
    fwrite(&(personaje->velocidad), sizeof(int), 1, fbin);
    fwrite(&(personaje->vidas), sizeof(int), 1, fbin);

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

    personaje = PJ_Princial_CrearPersonaje(1, 1, VIDAS_BASE);
    if(!personaje)
    {
        fclose(pf);
        return NULL;
    }

    fread(&(personaje->alcance_bomba), sizeof(int), 1, pf);
    fread(&(personaje->esta_vivo), sizeof(int), 1, pf);
    fread(&(personaje->pos), sizeof(int), 1, pf);
    fread(&(personaje->velocidad), sizeof(int), 1, pf);
    fread(&(personaje->vidas), sizeof(int), 1, pf);

    fclose(pf);
    return personaje;
}
