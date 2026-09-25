#include "Interfaz.h"
#include "Comunes.h"
#include "Mapa.h"
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
int MostrarMenuPrincipal()
{
    int seleccion = 0;
    const char *opciones[TOTAL_OPCIONES] = {
        "Nueva Partida",
        "Cargar Partida",
        "Salir"
    };

    while (1)
    {
        system("cls");
        PantallaInicio(&seleccion, opciones);

        int tecla = _getch();

        // Navegación vertical (W/S o flechas extendidas)
        if (EsLetraValida('W', tecla) == TODOOK) {
            seleccion = (seleccion - 1 + TOTAL_OPCIONES) % TOTAL_OPCIONES;
        }
        else if (EsLetraValida('S', tecla) == TODOOK) {
            seleccion = (seleccion + 1) % TOTAL_OPCIONES;
        }
        // Confirmación con tecla 'E' o Enter (ASCII 13)
        /// Acá le quiero poner el "Enter" pero no sé si jode otra función, lo probé y anda pero igual,
        /// habría que ver bien en la función EsLetraValida. Pero creo que no jode.
        else if (EsLetraValida('E', tecla) == TODOOK || tecla == 13) {
            system("cls");
            return seleccion; // Retorna 0, 1 o 2
        }
    }
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
//void MenuEjecucion()
//{
//    int seleccion = 0, ejecutando = 1;
//    const char *opciones[TOTAL_OPCIONES] = {"Continuar",
//                                            "Nueva Partida",
//                                            "Volver"};
//    while(ejecutando)
//    {
//        system("cls");
//        PantallaInicio(&seleccion, opciones);
//        ejecutando=SeleccionMenuPartida(&seleccion, opciones);
//    }
//}
void renderizar(const Mapa *m, const Personaje *p)
{
    int i, j;
    for (i = 0; i < m->filas; i++)
    {
        for (j = 0; j < m->columnas; j++)
        {
            if (p != NULL && p->pos.x == i && p->pos.y == j)
                printf("%c",PJP);
            else if (m->celdas[i][j] != VACIO)
                printf("%c",m->celdas[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }
    system("pause");
}
