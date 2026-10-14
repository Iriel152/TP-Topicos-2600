#include "Comunes.h"
int EsLetraValida(int LetraEsperada, int LetraRecibida)
{
    if(LetraEsperada == LetraRecibida || LetraEsperada + ('a' - 'A') == LetraRecibida)
        return TODOOK;
    else
        return ERROR_;
}
int Tecla_ArribaAbajo(int tecla)
{
    if(EsLetraValida(TEC_ABAJO, tecla) == TODOOK || EsLetraValida(TEC_ARRIBA, tecla) == TODOOK)
        return TODOOK;
    else
        return ERROR_;
}
int ObtenerNumeroAleatorio(int min, int max)
{
    return (rand()%(max - min + 1)) + min;
}
int ASegundos(DWORD tiempo)
{
    return ((int)tiempo / SEGUNDOS);
}
