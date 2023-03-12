#include "Objeto.h"

Objeto crearobjeto()
{
    Objeto acrear;

    int flag=0;
    char nombres[4][10]= {"Pergamino","Pocion","Arma","Armadura"}; ///Solo tiene un fin visual

    while(flag==0)
    {
        printf("Tipos de objetos\n");
        printf("1. Pergamino\n");
        printf("2. Pocion\n");
        printf("3. Arma\n");
        printf("4. Armadura\n");
        printf("Que tipo de objeto creara: ");
        fflush(stdin);
        scanf("%i",&acrear.tipo);

        if((acrear.tipo>0)&&(acrear.tipo<5))
        {
            flag=1;
        }
        else
        {
            printf("Ingrese una opcion valida");
            system("pause");
            system("cls");
        }
    }

    printf("Termine de cargar su %s\n",nombres[acrear.tipo-1]);

    printf("Nombre: ");
    fflush(stdin);
    gets(acrear.nombre);

    printf("Prefacio: ");
    fflush(stdin);
    gets(acrear.prefacio);

    printf("Modificador: ");
    fflush(stdin);
    scanf("%i",&acrear.modificador);

    return acrear;
}

Objeto dropoti()
{
    Objeto poti;
    strcpy(poti.nombre,"Curacion");
    poti.modificador=5;
    poti.tipo=2;

    return poti;
}

Objeto dropperga()
{
    srand(time(NULL));

    Objeto pergamino;
    int aleer=rand()%PERGASENARCHI;

    pergamino=depersistirpergamino(aleer);

    return pergamino;
}

Objeto droparmauarmadura(int ultimo,int tipo)
{
    Objeto elobjeto;

    if(tipo==3)
    {
        elobjeto=depersistirarma(ultimo);
    }
    else
    {
        elobjeto=depersistirarmadura(ultimo);
    }

    printf("Encontraste %s \n",elobjeto.nombre);
    printf("%s \n",elobjeto.prefacio);
    Sleep(3100);
    system("cls");

    return elobjeto;
}

Objeto depersistirpergamino(int ultimo)
{
    Objeto drop;

    FILE* fp=fopen(PERGAMINO,"rb");

    if(fp!=NULL)
    {
        fseek(fp,sizeof(Objeto)*ultimo,SEEK_SET);
        fread(&drop,sizeof(Objeto),1,fp);
        drop.tipo=1;

        fclose(fp);
    }

    return drop;
}

Objeto depersistirarma(int ultimo)
{
    Objeto drop;

    FILE* fp=fopen(ARMA,"rb");

    if(fp!=NULL)
    {
        fseek(fp,sizeof(Objeto)*ultimo,SEEK_SET);
        fread(&drop,sizeof(Objeto),1,fp);
        fclose(fp);
    }

    return drop;
}

Objeto depersistirarmadura(int ultimo)
{
    Objeto drop;

    FILE* fp=fopen(ARMADURA,"rb");

    if(fp!=NULL)
    {
        fseek(fp,ultimo*sizeof(Objeto),SEEK_SET);
        fread(&drop,sizeof(Objeto),1,fp);
        fclose(fp);
    }

    return drop;
}
