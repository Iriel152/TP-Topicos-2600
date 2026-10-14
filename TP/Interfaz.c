#include "Interfaz.h"
int Interfaz_MostrarMenuPrincipal()
{
    int seleccion = 0, tecla, cant_op;
    const char *opciones[] = {
        "Nueva Partida",
        "Cargar Partida",
        "Salir"
    };

    cant_op = (int)sizeof(opciones)/sizeof(*opciones);

    while (1)
    {

        system("cls");
        Interfaz_PantallaInicio(&seleccion, opciones, cant_op);
        tecla = _getch();

        if (EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + cant_op) % cant_op;
        else if (EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % cant_op;
        else if (EsLetraValida('E', tecla) == TODOOK)
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
            return seleccion;
        }
    }
}
void Interfaz_PantallaInicio(int *seleccion, const char **opciones, int cant)
{
    int i;

    Interfaz_TituloSistema();

    for (i = 0; i < cant; i++)
    {
        if (i == *seleccion)
            Interfaz_AlinearCentro(*(opciones + i), N_CENTRADO, COLOR_ACTIVO, T_SELECCIONADO);
        else
            Interfaz_AlinearCentro(*(opciones + i), N_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    }
    Interfaz_Separador(N_CENTRADO);
}
void Interfaz_TituloSistema()
{
    Interfaz_Separador(N_CENTRADO);
    Interfaz_AlinearCentro(TITULO_C, N_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    Interfaz_Separador(N_CENTRADO);
}
void Interfaz_Separador(int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("=");
    printf("\n");
}
void Interfaz_AlinearCentro(const char* palabra, int total, const char* color, int selec)
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
int Interfaz_MenuEjecucion()
{
    int seleccion=0, tecla, cant_op;
    const char *opciones[] = {  "Continuar",
                                "Nueva Partida",
                                "Volver"};

    cant_op = (int)sizeof(opciones)/sizeof(*opciones);

    while(1)
    {
        system("cls");
        Interfaz_PantallaInicio(&seleccion, opciones, cant_op);
        tecla = _getch();

        if (EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + cant_op) % cant_op;
        else if (EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % cant_op;
        else if (EsLetraValida('E', tecla) == TODOOK)
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
            return seleccion;
        }
    }
}
void Interfaz_renderizar(const tMapa *m, const tPersonaje *p, const tEnemigo *e, int temporizador)
{
    int i, j;
    UINT consolaOriginal;

    printf("\033[H");
    printf("TIEMPO %3d\t PUNTAJE %7d\tVIDAS ", temporizador, p->puntaje);

    consolaOriginal = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    for(i = 0 ; i < p->vidas ; i++)
        printf("\u2665");

    printf("\033[K");
    SetConsoleOutputCP(consolaOriginal);
    printf("\n");
    for (i = 0; i < m->filas; i++)
    {
        for (j = 0; j < m->columnas ; j++)
        {
            if (p != NULL && p->pos.x == i && p->pos.y == j)
            {
                if(p->esta_vivo == 2 && (GetTickCount() % 300) < 150)
                    printf(" ");
                else
                    printf("%c", PJP);
            }

            else if(e != NULL && e->esta_vivo == 1 && e->pos.x == i && e->pos.y == j)
                printf("%c", ENEMIGO_VISUAL);
            else if (m->celdas[i][j] != VACIO)
                printf("%c", m->celdas[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }

    fflush(stdout);
}
void Interfaz_PantallaMensaje(const char *frase)
{
    system("cls");
    Interfaz_TituloSistema();
    printf("\n\n");
    Interfaz_AlinearCentro(frase, N_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    Sleep(6000);
}
