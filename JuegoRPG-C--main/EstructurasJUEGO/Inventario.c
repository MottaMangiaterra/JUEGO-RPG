#include "Inventario.h"

nododoble* inicinventario()
{
    nododoble* inventario=iniclista();

    return inventario;
}

nododoble* usarobjeto(nododoble* inventario,Objeto elobjeto)
{
    if(inventario!=NULL)
    {
        inventario=borrarnodo(inventario,elobjeto.nombre);

    }
    //Hacer la verificacion desde donde llamo la funcion y de ahi en caso de que el inventairo sea NULL hago el printf

    return inventario;
}

nododoble* agregarobjeto(nododoble* inventario,Objeto elobjeto)
{
    nododoble* nuevo=crearnodo(elobjeto);

    if(inventario==NULL)
    {
        inventario=nuevo;
    }
    else
    {
        nododoble* aux=inventario;
        aux=buscarultimo(aux);

        aux->sig=nuevo;
        nuevo->ante=aux;
    }

    return inventario;
}

void verinventario(nododoble* inventario)
{
    if(inventario==NULL)
    {
        printf("No hay Objetos\n");
    }
    else
    {
        int limite=contarItemsInventario(inventario);
        mostrarlista(inventario);
        while(limite<LIMITE)
        {
            limite++;
            printf("%i.---------\n",limite);
        }
        printf("Que desea utilizar:  ");
    }

}

Objeto buscarobjeto(nododoble* inventario,int posicion)
{
    Objeto abuscar;
    abuscar.tipo=0;///Inicializo este campo en 0 para poder hacer comprobaciones fuera de la funcion

    if(inventario!=NULL)
    {
        nododoble* aux=inventario;
        int i=0;
        while(i!=posicion && aux!=NULL)
        {
            aux=aux->sig;
            i++;
        }

        if(aux!=NULL)
        {
            abuscar=aux->dato;
        }
    }

    return abuscar;
}

