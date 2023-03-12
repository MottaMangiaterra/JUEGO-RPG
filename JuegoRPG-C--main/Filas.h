#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED
#include "Codito2.h"

typedef struct
{
    struct nododoble* cabecera;
    struct nododoble* cola;
}Fila;

void inicfila(Fila* tufila);
void agregar(Fila* tufila, Objeto conjuro);
Objeto extraer(Fila* tufila);
nododoble* borrarPrimero(nododoble* lista);
Objeto verPrimero(nododoble* lista);

#endif // FILAS_H_INCLUDED
