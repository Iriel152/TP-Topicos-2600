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

        if (Comunes_EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + cant_op) % cant_op;
        else if (Comunes_EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % cant_op;
        else if (Comunes_EsLetraValida('E', tecla) == TODOOK)
        {
            system("cls");
            switch(seleccion)
            {
                case 0:
                    seleccion = EP_NUEVAP;
                    break;
                case 1:
                    seleccion = EP_CARGARP;
                    break;
                case 2:
                    seleccion = EP_SALIR;
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
            Interfaz_AlinearCentro(*(opciones + i), T_CENTRADO, COLOR_ACTIVO, T_SELECCIONADO);
        else
            Interfaz_AlinearCentro(*(opciones + i), T_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    }
    Interfaz_Separador(T_CENTRADO);
}
void Interfaz_TituloSistema()
{
    Interfaz_Separador(T_CENTRADO);
    Interfaz_AlinearCentro(C_TITULO, T_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    Interfaz_Separador(T_CENTRADO);
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

        if (Comunes_EsLetraValida('W', tecla) == TODOOK)
            seleccion = (seleccion - 1 + cant_op) % cant_op;
        else if (Comunes_EsLetraValida('S', tecla) == TODOOK)
            seleccion = (seleccion + 1) % cant_op;
        else if (Comunes_EsLetraValida('E', tecla) == TODOOK)
        {
            system("cls");
            switch(seleccion)
            {
                case 0:
                    seleccion = EP_CONTINUAR;
                    break;
                case 1:
                    seleccion = EP_NUEVAP;
                    break;
                case 2:
                    seleccion = EP_SALIR;
                    break;
            }
            return seleccion;
        }
    }
}
void Interfaz_renderizar(const tMapa *m, const tPersonaje *p, tVector *vec_e, tVector *vec_b, int temporizador)
{
    int i, j, k, ocupado;
    tEnemigo *enemigo;
    tBomba *bomba;
    UINT consolaOriginal;

    enemigo = (tEnemigo*)vec_e->vec;
    bomba = (tBomba*)vec_b->vec;

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
            ocupado = 0;
            if (p != NULL && p->pos.y == i && p->pos.x == j)
            {
                if(p->esta_vivo == 2 && (GetTickCount() % 300) < 150)
                    printf(" ");
                else
                    printf("%c", D_PJP);
                ocupado = 1;
            }
            if(!ocupado && enemigo != NULL)
            {
                for(k = 0 ; k < vec_e->ce ; k++)
                {
                    if((enemigo + k)->esta_vivo == 1 && (enemigo + k)->pos.y == i && (enemigo + k)->pos.x == j)
                    {
                        printf("%c", D_ENEMIGO);
                        ocupado = 1;
                    }
                }
            }
            if(!ocupado && bomba != NULL)
            {
                for(k = 0 ; k < vec_b->ce ; k++)
                {
                    if(bomba->activa == 1 && (bomba + k)->pos.y == i && (bomba + k)->pos.x == j)
                    {
                        printf("%c", D_BOMBA);
                        ocupado = 1;
                    }
                }
            }
            if(!ocupado)
            {
                if (m->celdas[i][j] != DM_VACIO)
                    printf("%c", m->celdas[i][j]);
                else
                    printf(" ");
            }
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
    Interfaz_AlinearCentro(frase, T_CENTRADO, COLOR_NORMAL, T_NO_SELECCIONADO);
    Sleep(6000);
}
