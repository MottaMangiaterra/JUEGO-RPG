#ifndef MOBS_H_INCLUDED
#define MOBS_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Filas.h"
#define MOBS "mobs.bin"
#define CANTMOBS 6

typedef struct Mob
{
    char nombre[30];
    char prefacio[200];
    int vida;
    int danio;
    int defensa;
    int estado;///0 muerto, 1 vivo
}Mob;

typedef struct Boss
{
    struct Mob theboss;
    Fila conjuros;
}Boss;

///Mob
void crearmob();///Crea un mob y lo carga a un archivo
void persistenciamobs(Mob mob);
Mob depersistenciamob(int ultimo);///Toma en cuenta la cant de combates del pj, para aumentar gradualmente la dificultad
Mob mobatacado(Mob elmob,int danio);///Mide cuanta vida se le resta a un enemigo cuando es atacado, actualiza su estado en caso que sea necesario

///Boss
Boss crearboss();
Boss creacionBoss1();
Boss creacionBoss2();
Boss creacionBoss3();

#endif // MOBS_H_INCLUDED
