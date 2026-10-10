#include "Interfaz.h"
void PantallaInicio(int *seleccion, const char *opciones[])
{
    int i;
    TituloSistema();
    for (i = 0; i < TOTAL_OPCIONES; i++)
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
    int tecla;
    const char *opciones[TOTAL_OPCIONES] = {
        "Nueva Partida",
        "Cargar Partida",
        "Salir"
    };

    while (1)
    {

        system("cls");
        PantallaInicio(&seleccion, opciones);
        tecla = _getch();
        if (EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + TOTAL_OPCIONES) % TOTAL_OPCIONES;
        else if (EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % TOTAL_OPCIONES;
        // Confirmación con tecla 'E' o Enter (ASCII 13)
        /// Acá le quiero poner el "Enter" pero no sé si jode otra función, lo probé y anda pero igual,
        /// habría que ver bien en la función EsLetraValida. Pero creo que no jode.
        else if (EsLetraValida('E', tecla) == TODOOK || tecla == 13)
        {
            system("cls");
            switch(seleccion)
            {
                case 0:
                    seleccion = NUEVAP;
                    break;
                case 1:
                    seleccion = CARGARP;
                    break;
                case 2:
                    seleccion = SALIR;
                    break;
            }
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
int MenuEjecucion()
{
    int seleccion=0, tecla;
    const char *opciones[TOTAL_OPCIONES] = {"Continuar",
                                            "Nueva Partida",
                                            "Volver"};
    while(1)
    {
        system("cls");
        PantallaInicio(&seleccion, opciones);
        tecla = _getch();
        if (EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + TOTAL_OPCIONES) % TOTAL_OPCIONES;
        else if (EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % TOTAL_OPCIONES;
        else if (EsLetraValida('E', tecla) == TODOOK || tecla == 13)
        {
            system("cls");
            switch(seleccion)
            {
                case 0:
                    seleccion = CONTINUAR;
                    break;
                case 1:
                    seleccion = NUEVAP;
                    break;
                case 2:
                    seleccion = SALIR;
                    break;
            }
            return seleccion; // Retorna 0, 1 o 2
        }
    }
}
void renderizar(const tMapa *m, const tPersonaje *p, const tEnemigo *e, int temporizador)
{
    int i, j;
    UINT consolaOriginal;

    printf("\033[H");
    printf("TIEMPO %3d\t PUNTAJE %7d\tVIDAS ", temporizador, p->puntaje);

    consolaOriginal = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    for(i=0; i<p->vidas ; i++)
        printf("\u2665");

    SetConsoleOutputCP(consolaOriginal);
    printf("\n");
    for (i = 0; i < m->filas; i++)
    {
        for (j = 0; j < m->columnas; j++)
        {
            if (p != NULL && p->pos.x == i && p->pos.y == j)
                printf("%c",PJP);
            else if(e != NULL && e->pos.x == i && e->pos.y == j)
                printf("%c",ENEMIGO_VISUAL);
            else if (m->celdas[i][j] != VACIO)
                printf("%c",m->celdas[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }

    fflush(stdout);
}
void PantallaGameOver()
{
    system("cls");
    TituloSistema();
    printf("\n\n");
    AlinearCentro("GAME OVER", n_centrado, COLOR_NORMAL, T_No_seleccionado);
    Sleep(6000);
}
