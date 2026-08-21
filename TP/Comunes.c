#include "Comunes.h"
int EsLetraValida(int LetraEsperada, int LetraRecibida)
{
    if(LetraEsperada == LetraRecibida
       || LetraEsperada + 32 == LetraRecibida)
        return TODOOK;
    else
        return ERROR_;
}
