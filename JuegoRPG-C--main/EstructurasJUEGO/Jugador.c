#include "Jugador.h"

void cargaUsuario(Heroe* jug)
{
    printf("Ingrese el nombre de su heroe: ");
    fflush(stdin);
    gets(jug->nombre);
    jug->armadura=0;
    jug->vidaMax=10;
    jug->atk=0;
    jug->vidaActual=10;
    jug->habitacionActual=4;
    jug->cantidadCombates=0;
    jug->inventarioheroe=inicinventario();
}

Heroe recogerLootCofre(Heroe jugador)
{
    srand(time(NULL));

    printf("En frente de nuestro heroe se encuentra un cofre, con mucho cuidado va a abrirlo y en el.");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf("\n");

    int cantEspaciosUsados=contarItemsInventario(jugador.inventarioheroe);

    if(cantEspaciosUsados<LIMITE)
    {
        printf("Encuentra una pocion, un pergamino y algo mas!!\n");
        Sleep(2300);
        int decisionCofre=3;

        if(cantEspaciosUsados==9)
        {
            printf("Tu inventario tiene espacio solo para un objeto mas!\n");

            printf("desea tomar la pocion o el pergamino?\n");
            printf("1. pocion\t2. pergamino\n");
            fflush(stdin);
            scanf("%i",&decisionCofre);

            jugador=dropsp(jugador,decisionCofre);
        }
        else
        {
            jugador=dropsp(jugador,decisionCofre);
        }
    }

    jugador=armaduraoarma(jugador);

    return jugador;
}

Heroe dropsp(Heroe jugador,int designado)
{
    switch(designado)
    {
    case 1:
        jugador.inventarioheroe=agregarobjeto(jugador.inventarioheroe,dropoti());
        break;
    case 2:
        jugador.inventarioheroe=agregarobjeto(jugador.inventarioheroe,dropperga());
        break;
    case 3:
        jugador.inventarioheroe=agregarobjeto(jugador.inventarioheroe,dropoti());
        jugador.inventarioheroe=agregarobjeto(jugador.inventarioheroe,dropperga());
        break;
    }

    return jugador;
}

Heroe armaduraoarma(Heroe jugador)
{
    int var=rand()%2;

    if(var==0)
    {
        Objeto arma=droparmauarmadura(jugador.atk,3);
        printf("Ataque del arma: %i \n",arma.modificador);
        jugador.atk=arma.modificador;
    }
    else
    {

        Objeto armadura=droparmauarmadura(jugador.armadura,4);
        printf("Defensa de la armadura: %i \n",armadura.modificador);
        jugador.armadura=armadura.modificador;
    }
    Sleep(2300);
    system("cls");
    return jugador;
}

int combate(Heroe* jug)
{
    Mob aux=depersistenciamob(jug->cantidadCombates);
    int seescapo=0;///Si escapa se cambiaria a 1 este valor y si no queda igual
    Heroe heroeaux=(*jug);

    printf("Al entrar a la habitacion, sucecede algo inesperado y se encuentra a %s, %s\n",aux.nombre,aux.prefacio);
    printf("PREPARESE PARA EL COMBATE!!\n");
    system("pause");
    system("cls");

    int variableSwitch=0;

    while(heroeaux.vidaActual>=0 && aux.estado!=0)
    {
        printf("VIDA: %d/%d\t\t\t\t%s: %d\n\n\n\n",jug->vidaActual,jug->vidaMax,aux.nombre,aux.vida);
        printf("Que desea hacer?\n");
        printf("1: atacar\t");
        printf("2: utilizar objeto\t");
        printf("3: intentar retroceder\n");
        fflush(stdin);
        scanf("%i",&variableSwitch);

        switch (variableSwitch)
        {
        case 1:
            heroeaux=ataque(heroeaux,&aux);
            break;
        case 2:
            heroeaux=utilizarObjetoEnCombate(heroeaux,&aux);
            break;
        case 3:
            seescapo=intentoescape(seescapo,&aux);
            if(seescapo==1)
            {
                aux.vida=0;
            }
            break;
        }

        (*jug)=heroeaux;
        system("pause");
        system("cls");
    }

    if((aux.estado==0)&&(seescapo!=1))
    {
        system("cls");
        jug->cantidadCombates++;
        jug->vidaMax+=2;     //sube su vida en 2
        jug->vidaActual+=2;  //se cura en 2
        printf("Ha Muerto\n");
        system("pause");
        system("cls");
    }
    return seescapo;
}

Heroe ataque(Heroe jugador,Mob* elmob)
{
    int variableAtaque=rand()%11+1;
    int danioAtaque=rand()%7+1;;
    variableAtaque+=jugador.atk;
    Mob aux=(*elmob);

    if(variableAtaque>=10)
    {
        printf("atacas con todas tus fuerzas y impactas contra el %s\n", aux.nombre);
        danioAtaque+=jugador.atk;
        aux=mobatacado(aux,danioAtaque);
    }
    else if(variableAtaque<=9 && variableAtaque>=4)
    {
        printf("en un cruce de ataques tanto %s como %s reciben danio por igual\n",jugador.nombre,aux.nombre);
        aux=mobatacado(aux,danioAtaque);
        printf("el %s recibe %d puntos de danio\n",aux.nombre,danioAtaque);
        jugador=recibedanio(jugador,aux.danio);
    }
    else
    {
        printf("tu ataque fallo y el %s aprovecha y te ataca\n",aux.nombre);
        jugador=recibedanio(jugador,aux.danio);
    }

    (*elmob)=aux;

    return jugador;
}

Heroe ataqueBossMagico(Heroe jugador,Mob* elmob, Objeto conjuro)
{
    int variableAtaque=rand()%11+1;
    int danioAtaque=rand()%7+1;;
    variableAtaque+=jugador.atk;
    Mob aux=(*elmob);

    if(variableAtaque>=10)
    {
        printf("atacas con todas tus fuerzas y impactas contra el %s\n", aux.nombre);
        danioAtaque+=jugador.atk;
        aux=mobatacado(aux,danioAtaque);
    }
    else if(variableAtaque<=9 && variableAtaque>=5)
    {
        printf("en un cruce de ataques tanto %s como %s reciben danio por igual\n",jugador.nombre,elmob->nombre);
        printf("el %s uso el conjuro: %s\n",aux.nombre, conjuro.nombre);
        if(strcmp(aux.nombre,"Mago Oscuro")==0)
        {
            conjuro.modificador=conjuro.modificador/2;
        }
        aux=mobatacado(aux,danioAtaque);
        printf("el %s recibe %d puntos de danio\n",aux.nombre,danioAtaque);
        jugador=recibedanio(jugador,conjuro.modificador);
    }
    else
    {
        printf("tu ataque fallo y el %s aprovecha y te ataca\n",elmob->nombre);
        printf("el %s uso el conjuro: %s\n",aux.nombre, conjuro.nombre);
        if(strcmp(aux.nombre,"Mago Oscuro")==0)
        {
            conjuro.modificador=conjuro.modificador/2;
        }
        jugador=recibedanio(jugador,conjuro.modificador);
    }

    (*elmob)=aux;

    return jugador;
}

Heroe recibedanio(Heroe jugador,int danio)
{
    danio-=jugador.armadura;
    jugador.vidaActual-=danio;

    return jugador;
}

Heroe utilizarObjetoFueraDeCombate(Heroe jugador)
{
    verinventario(jugador.inventarioheroe);
    if(jugador.inventarioheroe!=NULL)
    {
        int opusuario;
        fflush(stdin);
        scanf("%i",&opusuario);

        while((opusuario<1)&&(opusuario>contarItemsInventario(jugador.inventarioheroe)))
        {
            system("cls");
            verinventario(jugador.inventarioheroe);
            printf("Reingrese su opcion: ");
            fflush(stdin);
            scanf("%i",&opusuario);
            system("pause");
        }
        opusuario=opusuario-1;
        Objeto elobjeto=buscarobjeto(jugador.inventarioheroe,opusuario);
        if(elobjeto.tipo!=1)
        {
            jugador.inventarioheroe=usarobjeto(jugador.inventarioheroe,elobjeto);
        }
        efectoObjetoFueraDeCombate(elobjeto,&jugador);
    }
    return jugador;
}

Heroe utilizarObjetoEnCombate(Heroe jugador,Mob*mob)
{
    printf("En medio del combate, abres tu bolsa con esperanza de encontrar algo que te ayude en este combate\n");
    verinventario(jugador.inventarioheroe);
    if(jugador.inventarioheroe!=NULL)
    {
        int opusuario;
        fflush(stdin);
        scanf("%i",&opusuario);

        while((opusuario<1)&&(opusuario>contarItemsInventario(jugador.inventarioheroe)))
        {
            system("cls");
            verinventario(jugador.inventarioheroe);
            printf("Reingrese su opcion: ");
            fflush(stdin);
            scanf("%i",&opusuario);
            system("pause");
        }
        opusuario=opusuario-1;
        Objeto elobjeto=buscarobjeto(jugador.inventarioheroe,opusuario);
        jugador.inventarioheroe=usarobjeto(jugador.inventarioheroe,elobjeto);
        efectoObjetoEnCombate(elobjeto,&jugador,mob);

        if(mob->vida<=0)
        {
            mob->estado=0;
        }
    }
    return jugador;
}

int intentoescape(int seescapo,Mob* elmob)
{
    seescapo=rand()%2;
    if(seescapo==1)
    {
        printf("escapaste de la habitacion con exito");
    }
    else
    {
        printf("intentaste escapar pero el %s bloquea la salida",elmob->nombre);
    }

    return seescapo;
}

void efectoObjetoEnCombate(Objeto objetito,Heroe*jug,Mob*mob)
{
    if(objetito.tipo==2 && jug->vidaActual!=jug->vidaMax) //el item es pocion
    {
        jug->vidaActual=jug->vidaActual+5;
        if(jug->vidaActual>jug->vidaMax)
        {
            jug->vidaActual=jug->vidaMax;
            printf("te curas todos tus puntos de golpe");
        }
        else
        {
            printf("te curas 5 puntos de golpe");
        }
        Sleep(2300);
        system("cls");
    }
    else//es pergamino
    {
        printf("utilizando tu pergamino de %s atacas al %s",objetito.nombre, mob->nombre);
        (mob->vida)-=objetito.modificador;
        Sleep(2300);
        system("cls");
    }
}

void efectoObjetoFueraDeCombate(Objeto objetito,Heroe*jug)
{
    if(objetito.tipo==2 && jug->vidaActual!=jug->vidaMax) //el item es pocion
    {
        jug->vidaActual=jug->vidaActual+5;
        if(jug->vidaActual>jug->vidaMax)
        {
            jug->vidaActual=jug->vidaMax;
            printf("te curas todos tus puntos de golpe");
        }
        else
        {
            printf("te curas 5 puntos de golpe");
        }
        Sleep(2000);
        system("cls");
    }
    else
    {
        printf("no es momento de usar eso");
    }
}

void combateBoss(Heroe* jug, int nivelMazmorra,int *finNivel)
{
    Boss boss;
    Heroe heroeaux=(*jug);
    if(nivelMazmorra==0)
    {
        boss=creacionBoss1();
    }
    else if(nivelMazmorra==1)
    {
        boss=creacionBoss2();
    }
    else
    {
        boss=creacionBoss3();
    }
    printf("Al entrar a la habitacion, sucecede algo inesperado y te encuentras a %s, %s\n",boss.theboss.nombre,boss.theboss.prefacio);
    printf("PREPARESE PARA EL COMBATE!!\n");
    system("pause");
    system("cls");

    int variableSwitch=0;
    int varianzaAtaquesLiche=0;
    Objeto conjuro;

    while(heroeaux.vidaActual>=0 && boss.theboss.estado!=0)
    {
        printf("VIDA: %d/%d\t\t\t\t%s: %d\n\n\n\n",jug->vidaActual,jug->vidaMax,boss.theboss.nombre,boss.theboss.vida);
        printf("Que desea hacer?\n");
        printf("1: atacar\t");
        printf("2: utilizar objeto\t");
        fflush(stdin);
        scanf("%i",&variableSwitch);

        switch (variableSwitch)
        {
        case 1:
            if(nivelMazmorra==2)
            {
                if(varianzaAtaquesLiche%2==0)
                {
                    heroeaux=ataque(heroeaux,&boss.theboss);
                    varianzaAtaquesLiche++;
                }
                else
                {
                    conjuro=extraer(&boss.conjuros);
                    heroeaux=ataqueBossMagico(heroeaux,&boss.theboss,conjuro);
                    varianzaAtaquesLiche++;
                }

            }
            else if(nivelMazmorra==0)
            {
                heroeaux=ataque(heroeaux,&boss.theboss);
            }
            else
            {
                conjuro=extraer(&boss.conjuros);
                heroeaux=ataqueBossMagico(heroeaux,&boss.theboss,conjuro);
            }
            break;
        case 2:
            heroeaux=utilizarObjetoEnCombate(heroeaux,&boss.theboss);
            break;
        }
        if(boss.theboss.vida<=0)
        {
            boss.theboss.estado=0;
        }
        (*jug)=heroeaux;
        system("pause");
        system("cls");
    }

    if(boss.theboss.estado==0)
    {
        system("cls");
        jug->cantidadCombates++;
        jug->vidaMax+=2;     //sube su vida en 2
        jug->vidaActual+=2;  //se cura en 2
        printf("Ha Muerto el Jefe del Piso\n");
        (*finNivel)=1;
        jug->habitacionActual=4;
        system("pause");
        system("cls");
    }
    else
    {
        printf("perdiste");
        exit(1);
    }
}
