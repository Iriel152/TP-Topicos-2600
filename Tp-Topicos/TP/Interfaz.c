#include "Interfaz.h"
void PantallaInicio()
{
    TituloSistema();
    OpcionesInicio();
    Separador(n_centrado);
}
void Separador(int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("=");
    printf("\n");
}
void TituloSistema()
{
    Separador(n_centrado);
    AlinearCentro(Titulo, n_centrado);
    Separador(n_centrado);
}
void AlinearCentro(const char* palabra, int total)
{
    int tam, i;
    tam=strlen(palabra);
    tam=tam/2;
    for(i=0;i<total/2-tam;i++)
        printf(" ");
    printf("%s\n",palabra);
}
void OpcionesInicio()
{
    AlinearCentro("Continuar", n_centrado);
    AlinearCentro("Nueva Partida", n_centrado);
    AlinearCentro("Ranking", n_centrado);
    AlinearCentro("Salir", n_centrado);
}
