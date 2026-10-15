#include "Puerta.h"
tPuerta *Puerta_Crear()
{
    tPuerta *puerta;
    puerta = (tPuerta*)malloc(sizeof(tPuerta));
    if(!puerta)
        return NULL;
    puerta->estado_puerta = DESACTIVADA;
    puerta->celdas_transitables = 0;
    puerta->prob = 0;
    puerta->vacio = 0;

    return puerta;
}
void Puerta_Destruir(tPuerta *puerta)
{
    if(puerta)
        free(puerta);
}
int Puerta_ArchivosGuardar(const char* binPath, tPuerta *puerta)
{
    FILE *fbin;
    fbin = fopen(binPath,"wb");

    if(!fbin)
        return ERROR_ARCH;

    fwrite(&(puerta->celdas_transitables), sizeof(int), 1, fbin);
    fwrite(&(puerta->estado_puerta), sizeof(int), 1, fbin);
    fwrite(&(puerta->prob), sizeof(float), 1, fbin);
    fwrite(&(puerta->vacio), sizeof(int), 1, fbin);

    fclose(fbin);
    return TODOOK;
}
tPuerta* Puerta_ArchivosCargar(const char* binPath)
{
    FILE *pf;
    tPuerta *puerta;
    pf = fopen(binPath, "rb");
    if(!pf)
        return NULL;

    puerta = (tPuerta*)malloc(sizeof(tPuerta));
    if(!puerta)
    {
        fclose(pf);
        return NULL;
    }

    fread(&(puerta->celdas_transitables), sizeof(int), 1, pf);
    fread(&(puerta->estado_puerta), sizeof(int), 1, pf);
    fread(&(puerta->prob), sizeof(float), 1, pf);
    fread(&(puerta->vacio), sizeof(int), 1, pf);

    fclose(pf);
    return puerta;
}
