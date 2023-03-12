#ifndef CODITO2_H_INCLUDED
#define CODITO2_H_INCLUDED
#include "Objeto.h"

typedef struct nododoble
{
    Objeto dato;
    struct nododoble* ante;
    struct nododoble* sig;
}nododoble;

nododoble* iniclista();
nododoble* crearnodo(Objeto elobjetito);
nododoble* agregarfinal2(nododoble* lista, nododoble* nuevo);
nododoble* buscarultimo(nododoble* lista);
int contarItemsInventario(nododoble* lista);
nododoble* borrarnodo(nododoble* lista,char dato[]);
void mostrarlista(nododoble* lista);
nododoble* buscar(nododoble* lista,char dato[]);

#endif // CODITO2_H_INCLUDED
