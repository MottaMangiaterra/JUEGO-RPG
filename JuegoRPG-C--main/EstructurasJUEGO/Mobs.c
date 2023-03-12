#include "Mobs.h"

///Mobs
void crearmob()
{
    Mob nuevomob;

    for(int i=0; i<CANTMOBS; i++)
    {
        printf("Ingrese el nombre del Mob a crear: ");
        fflush(stdin);
        gets(nuevomob.nombre);

        printf("De una breve descripcion de su Mob (Prefacio): ");
        fflush(stdin);
        gets(nuevomob.prefacio);

        printf("Ingrese el danio del Mob a crear: ");
        fflush(stdin);
        scanf("%i",&nuevomob.danio);

        printf("Ingrese la vida del Mob a crear: ");
        fflush(stdin);
        scanf("%i",&nuevomob.vida);

        nuevomob.estado=1;

        persistenciamobs(nuevomob);
    }
}

void persistenciamobs(Mob mob)
{
    FILE* fp=fopen(MOBS,"ab");

    if(fp!=NULL)
    {
        fwrite(&mob,sizeof(Mob),1,fp);

        fclose(fp);
    }
}

Mob depersistenciamob(int ultimo)
{
    Mob nuevo;

    FILE* fp=fopen(MOBS,"rb");

    if(fp!=NULL)
    {
        fseek(fp,sizeof(Mob)*ultimo,SEEK_SET);
        fread(&nuevo,sizeof(Mob),1,fp);

        fclose(fp);
    }

    return nuevo;
}

Mob mobatacado(Mob elmob,int danio)
{
    elmob.vida-=danio;

    if(elmob.vida<=0)
    {
        elmob.estado=0;
    }

    return elmob;
}

///Boss
Boss creacionBoss1()
{
    Boss Abominacion;
    Abominacion.theboss.danio=5;
    Abominacion.theboss.estado=1;
    strcpy(Abominacion.theboss.nombre,"Abominacion");
    strcpy(Abominacion.theboss.prefacio,"Una aberracion de gran tamanio, el Abominacion, una criatura muy fuerte conformada por varios cadaveres cocidos se encuentra frente a nuestro heroe");
    Abominacion.theboss.vida=15;

    return Abominacion;
}
Boss creacionBoss2()
{
    Boss magoOscuro;
    magoOscuro.theboss.estado=1;
    strcpy(magoOscuro.theboss.nombre,"Mago Oscuro");
    strcpy(magoOscuro.theboss.prefacio,"El alumno preferido del liche, o por lo menos el unico que sobrevivio, ten cuidado con su magia");
    magoOscuro.theboss.vida=20;
    inicfila(&magoOscuro.conjuros);


    FILE*fp=fopen("pergaminos.bin","rb");
    Objeto conjuro;
    for(int i=0; i<4; i++)
    {
        while(fread(&conjuro,sizeof(Objeto),1,fp)>0)
        {
            agregar(&magoOscuro.conjuros, conjuro);
        }
    }
    return magoOscuro;
}
Boss creacionBoss3()
{
    Boss liche;
    liche.theboss.estado=1;
    liche.theboss.danio=7;
    strcpy(liche.theboss.nombre,"Liche");
    strcpy(liche.theboss.prefacio,"Es el duenio de este castillo y amo de las almas");
    liche.theboss.vida=30;
    inicfila(&liche.conjuros);


    FILE*fp=fopen("pergaminos.bin","rb");
    Objeto conjuro;
    for(int i=0; i<4; i++)
    {
        while(fread(&conjuro,sizeof(Objeto),1,fp)>0)
        {
            agregar(&liche.conjuros, conjuro);
        }
    }
    return liche;
}


