#include "Comunes.h"
int EsLetraValida(int LetraEsperada, int LetraRecibida)
{
    if(LetraEsperada == LetraRecibida || LetraEsperada + 32 == LetraRecibida)
        return TODOOK;
    else
        return ERROR_;
}
int Tecla_ArribaAbajo(int tecla)
{
    if(EsLetraValida('S', tecla) == TODOOK || EsLetraValida('W', tecla) == TODOOK)
        return TODOOK;
    else
        return ERROR_;
}
int ObtenerNumeroAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}
