#include "Comunes.h"
tVector* Comunes_CrearVector(size_t tam)
{
    tVector *v;

    v = (tVector*)malloc(sizeof(tVector));

    if(!v)
        return NULL;

    v->vec = NULL;
    v->ce = 0;
    v->tam = tam;
    v->maxElem = 0;
    v->ce = 0;

    return v;
}
void Comunes_DestruirVector(tVector* v)
{
    free(v->vec);
}
int Comunes_VectorArchivosGuardar(const char *binPath, tVector *v)
{
    FILE *fbin;
    fbin = fopen(binPath,"wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(v->ce), sizeof(size_t), 1, fbin);

    if(v->ce > 0)
        fwrite(v->vec, v->tam, v->ce, fbin);

    fclose(fbin);
    return TODOOK;
}
int Comunes_InsertarVector(tVector *v, const void *elemento)
{
    int NuevoMax;
    void *Bloque, *pos;

    if(!v || !elemento)
        return ERROR_MEMORIA;
    if(v->ce == v->maxElem)
    {
        if(v->maxElem == 0)
            NuevoMax = 2;
        else
            NuevoMax = v->maxElem * 2;

        Bloque = realloc(v->vec, NuevoMax * v->tam);
        if(!Bloque)
            return ERROR_MEMORIA;

        v->vec = Bloque;
        v->maxElem = NuevoMax;
    }

    pos = (char*)v->vec + (v->ce * v->tam);
    memcpy(pos, elemento, v->tam);
    v->ce++;

    return TODOOK;
}
tVector* Comunes_VectorArchivosCargar(const char* binPath, size_t tam)
{
    size_t cant;
    FILE *pf;
    tVector *v;
    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    fread(&cant, sizeof(size_t), 1, pf);

    v = Comunes_CrearVector(tam);
    if(!v)
    {
        fclose(pf);
        return NULL;
    }

    if(cant > 0)
    {
        v->vec = malloc(cant * tam);
        if(!v->vec)
        {
            fclose(pf);
            free(v);
            return NULL;
        }
        v->maxElem = cant;
        v->ce = cant;
        fread(v->vec, tam, cant, pf);
    }

    fclose(pf);
    return v;
}
int Comunes_EsLetraValida(int LetraEsperada, int LetraRecibida)
{
    if(LetraEsperada == LetraRecibida || LetraEsperada + ('a' - 'A') == LetraRecibida)
        return TODOOK;
    else
        return ERROR_;
}
int Comunes_TeclaArribaAbajo(int tecla)
{
    if(Comunes_EsLetraValida(TEC_ABAJO, tecla) == TODOOK ||
       Comunes_EsLetraValida(TEC_ARRIBA, tecla) == TODOOK)
        return TODOOK;
    else
        return ERROR_;
}
int Comunes_ObtenerNumeroAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}
int Comunes_ASegundos(DWORD tiempo)
{
    return ((int)tiempo / SEGUNDOS);
}
