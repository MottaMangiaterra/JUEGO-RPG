#include "mapa.h"

nodoArbol* inicArbol()
{
    return NULL;
}
nodoArbol* crearNodoArbol(int dato)
{
    nodoArbol*aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->id=dato;
    aux->derecha=NULL;
    aux->izquierda=NULL;
    aux->encuentro=rand()%2;
    aux->estado=0;
    return aux;
}
nodoArbol* insertar(nodoArbol*arbol,int dato)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(dato);
    }
    else
    {
        if(dato>arbol->id) //si dato es mayor al dato en arbol insertamos en la derecha
        {
            arbol->derecha=insertar(arbol->derecha,dato);
        }
        else //si no iria a la izquierda
        {
            arbol->izquierda=insertar(arbol->izquierda,dato);
        }
    }
    return arbol;
}
void preorder(nodoArbol* arbol)
{
    if(arbol!=NULL)
    {
        printf("%d\n",arbol->id);
        preorder(arbol->izquierda);
        preorder(arbol->derecha);
    }
}
void inorder(nodoArbol* arbol)
{
    if(arbol!=NULL)
    {
        inorder(arbol->izquierda);
        printf("%d",arbol->id);
        inorder(arbol->derecha);
    }
}
void postorder(nodoArbol* arbol)
{
    if(arbol!=NULL)
    {
        postorder(arbol->izquierda);
        postorder(arbol->derecha);
        printf("%d", arbol->id);
    }
}
nodoArbol* buscarArbol(nodoArbol*arbol, int dato)
{
    nodoArbol*rta=NULL;
    if(arbol!=NULL)
    {
        if(dato==arbol->id)
        {
            rta=arbol;
        }
        else
        {
            if(dato>arbol->id)
            {
                rta=buscarArbol(arbol->derecha,dato);
            }
            else
            {
                rta=buscarArbol(arbol->izquierda,dato);
            }
        }
    }
    return rta;
}
int esHoja (nodoArbol* nodo)
{
    int rta=0;
    if((nodo->derecha==NULL) && (nodo->derecha==NULL))
    {
        rta=1;
    }
    return rta;
}

// funciones de manejo de mapa

nodoArbol*cargaMapa(nodoArbol*arbol)
{
    arbol=insertar(arbol,4);
    arbol->estado=1; //para que la primera
    arbol=insertar(arbol,2);
    arbol=insertar(arbol,6);
    arbol=insertar(arbol,1);
    arbol=insertar(arbol,3);
    arbol=insertar(arbol,5);
    arbol=insertar(arbol,7);
    return arbol;
}
void avanzarIzquierda(nodoArbol* mapa, int habitacionActual, Heroe* jugador, int nivelMazmorra, int *finNivel)
{
    if(habitacionActual==mapa->id)
    {
        if(mapa->derecha==NULL)
        {
            combateBoss(jugador, nivelMazmorra, finNivel);
        }
        else
        {
            nodoArbol*aux=mapa;
            aux=aux->izquierda;
            jugador->habitacionActual=aux->id;
            if(aux->estado==1)
            {
                if(aux->encuentro==1)
                {
                    printf("el cadaver de tu enemigo yace en el suelo\n");
                    Sleep(2300);
                }
                else
                {
                    printf("el cofre abierto yace en la habitacion\n");
                    Sleep(2300);
                }
            }
            else
            {
                if(aux->encuentro==1)
                {
                    int seEscapo=combate(jugador);
                    if(seEscapo==0)
                    {
                        aux->estado=1;
                    }
                    else
                    {
                        retroceso(jugador,mapa);
                    }
                }
                else
                {
                    (*jugador)=recogerLootCofre((*jugador));
                    aux->estado=1;
                    jugador->cantidadCombates++;
                }

            }

        }
    }
    else
    {
        if(habitacionActual>mapa->id)
        {
            avanzarIzquierda(mapa->derecha,habitacionActual,jugador, nivelMazmorra, finNivel);
        }
        else
        {
            avanzarIzquierda(mapa->izquierda,habitacionActual,jugador, nivelMazmorra, finNivel);
        }
    }
}
void avanzarDerecha(nodoArbol*mapa, int habitacionActual, Heroe*jugador, int nivelMazmorra, int *finNivel)
{
    if(habitacionActual==mapa->id)
    {
        if(mapa->derecha==NULL)
        {
            combateBoss(jugador, nivelMazmorra, finNivel);
        }
        else
        {

            nodoArbol*aux=mapa;
            aux=aux->derecha;
            jugador->habitacionActual=aux->id;
            if(aux->estado==1)
            {
                if(aux->encuentro==1)
                {
                    printf("el cadaver de tu enemigo yace en el suelo\n");
                    Sleep(2300);
                }
                else
                {
                    printf("el cofre abierto yace en la habitacion\n");
                    Sleep(2300);
                }
            }
            else
            {
                if(aux->encuentro==1)
                {
                    int seEscapo=combate(jugador);
                    if(seEscapo==0)
                    {
                        aux->estado=1;
                    }
                }
                else
                {
                    (*jugador)=recogerLootCofre((*jugador));
                    aux->estado=1;
                    jugador->cantidadCombates++;
                }

            }

        }
    }
    else
    {
        if(habitacionActual>mapa->id)
        {
            avanzarDerecha(mapa->derecha,habitacionActual,jugador, nivelMazmorra, finNivel);
        }
        else
        {
            avanzarDerecha(mapa->izquierda,habitacionActual,jugador, nivelMazmorra, finNivel);
        }
    }
}

void retroceso(Heroe*jug,nodoArbol*mapa)
{
    nodoArbol*aux=mapa;
    if(jug->habitacionActual==1 || jug->habitacionActual==3)
    {
        jug->habitacionActual=2;
        aux=buscarYmostrarRestrocediendo(mapa,jug->habitacionActual);
    }
    else if(jug->habitacionActual==5 || jug->habitacionActual==7)
    {
        jug->habitacionActual=6;
        aux=buscarYmostrarRestrocediendo(mapa,jug->habitacionActual);
    }
    else
    {
        jug->habitacionActual=4;
    }

    if(jug->habitacionActual!=4)
    {
        /*if(aux->encuentro==1)
        {
            printf("el cadaver de tu enemigo yace en el suelo\n");
            Sleep(2300);
        }
        else
        {
            printf("el cofre abierto yace en la habitacion\n");
            Sleep(2300);
        }*/
    }
    else
    {
        printf("regresaste a la entrada de la dungeon");
        Sleep(2300);
    }
system("cls");
}

nodoArbol*buscarYmostrarRestrocediendo(nodoArbol*arbol, int dato)
{
    if(arbol!=NULL)
    {
        if(dato==arbol->id)
        {
            printf("Nuestro heroe retrocede a la habitacion anterior");
            Sleep(2300);
            system("cls");
            if(arbol->encuentro==1) //es combate
            {
                printf("el cadaver de tu enemigo yace en el suelo");
                Sleep(2300);
                system("cls");
            }
            else
            {
                printf("el cofre abierto yace en la habitacion");
                Sleep(2300);
                system("cls");
            }
        }
        else if(dato>arbol->id)
        {
            arbol->derecha=buscarYmostrarRestrocediendo(arbol->derecha,dato);
        }
        else
        {
            arbol->izquierda=buscarYmostrarRestrocediendo(arbol->izquierda,dato);
        }
    }
    return arbol;
}

void cargaNivelesMapa(celda ada[])
{
    int i=0;
    while(i<3)
    {
        ada[i].mapa=inicArbol();
        ada[i].mapa=cargaMapa(ada[i].mapa);
        ada[i].nivel=i;
        i++;
    }
}
