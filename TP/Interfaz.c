#include "Interfaz.h"
#include "Comunes.h"
void PantallaInicio(int *seleccion, const char *opciones[])
{
    TituloSistema();
    for (int i = 0; i < TOTAL_OPCIONES; i++)
    {
        if (i == *seleccion)
            AlinearCentro(opciones[i], n_centrado, COLOR_ACTIVO, T_seleccionado);
        else
            AlinearCentro(opciones[i], n_centrado,COLOR_NORMAL, T_No_seleccionado);
    }
    Separador(n_centrado);
}
void MenuInicio()
{
    int seleccion = 0, ejecutando = 1;
    const char *opciones[TOTAL_OPCIONES] = {"Nueva Partida",
                                            "Cargar Partida",
                                            "Salir"};
    while(ejecutando)
    {
        system("cls");
        PantallaInicio(&seleccion, opciones);
        ejecutando=SeleccionMenu(&seleccion, opciones);
    }
}
int SeleccionMenu(int *seleccion, const char *opciones[])
{
    int tecla = _getch(), ejecutando = 1;
    if (tecla == 0 || tecla == 224 || tecla == 13)
    {
        if(tecla == 13 || EsLetraValida('E', tecla) == TODOOK)
        {
            system("cls");
//            if (*seleccion == TOTAL_OPCIONES - 1) Es para que salga hasta que estes las condiciones
//            {
                AlinearCentro("Gracias por jugar!", n_centrado, COLOR_NORMAL, T_No_seleccionado);
                ejecutando = 0;
//            }
        }
        tecla = _getch();
        if(tecla == 72 || EsLetraValida('W', tecla) == TODOOK)
            *seleccion = (*seleccion - 1 + TOTAL_OPCIONES) % TOTAL_OPCIONES;
        else if(tecla == 80 || EsLetraValida('S', tecla) == TODOOK)
            *seleccion = (*seleccion + 1) % TOTAL_OPCIONES;
    }
    return ejecutando;
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
    AlinearCentro(Titulo, n_centrado, COLOR_NORMAL, T_No_seleccionado);
    Separador(n_centrado);
}
void AlinearCentro(const char* palabra, int total, const char* color, int selec)
{
    int tam, i;
    char* caracter = " >";
    tam = strlen(palabra);
    tam = tam/2;
    for(i=0;i<total/2 - tam - selec;i++)
        printf(" ");
    if(selec == 0)
        caracter = "";
    printf("%s%s%s %s\n", color, caracter, palabra, COLOR_RESET);
}
