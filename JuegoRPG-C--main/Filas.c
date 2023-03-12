#include "filas.h"

void inicfila(Fila* tufila)
{
    tufila->cabecera=iniclista();
    tufila->cola=iniclista();
}

void agregar(Fila* tufila, Objeto conjuro)
{
    nododoble* nuevo=crearnodo(conjuro);
    if(tufila->cabecera==NULL)
    {
        tufila->cabecera=nuevo;
        tufila->cola=nuevo;
    }
    else
    {
        tufila->cabecera=agregarfinal2(tufila->cabecera,nuevo);
        tufila->cola=nuevo;
    }
}

Objeto extraer (Fila* tufila)
{
    Objeto rsp;
    if(tufila->cabecera!=NULL)
    {
        rsp=verPrimero(tufila->cabecera);
        tufila->cabecera=borrarPrimero(tufila->cabecera);
        if(tufila->cabecera==NULL)
        {
            tufila->cola=iniclista();
        }
    }
    return rsp;
}

nododoble* borrarPrimero(nododoble*lista)
{
    nododoble* aborrar=lista;
    if(lista!=NULL)
    {
        lista=lista->sig;
        if(lista!=NULL)
        {
            lista->ante=NULL;
        }
        free(aborrar);
    }
    return lista;
}

Objeto verPrimero(nododoble* lista)
{
    Objeto rta;

    if(lista!=NULL)
    {
        rta=lista->dato;
    }
    return rta;
}
