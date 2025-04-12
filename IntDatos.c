//Archivo de código del Módulo Introducir Datos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MenuP.h"
#include "IntDatos.h"
#include "Complementos.h"

void int_nombre(char nombre[]){
    static int i,ng;
    static char ctrl;
    //Bucle para repetir la introducción del nombre en caso de quererlo
    do{
        //Bucle que se encarga de que el nombre introducido no tenga guiones
        do{
        ng=0;
        fflush(stdin);
        printf("\n================================\nIntroduzca su nombre por favor:\n");
        fgets(nombre,21,stdin);
        //Bucle que analiza todos los caracteres de la cadena en busca de guiones
        for(i=0;i<21;i++){
            if(nombre[i]=='-')
                ng=1;
        }
        if(ng==1)
            printf("No se admiten guiones ('-'), introduzca el nombre de nuevo\n");
        }while(ng=!0);
        terminador_cad(nombre);
        //Mostrar el nombre escrito por si no es del agrado del usuario
        printf("\n================================\nEl nombre introducido es:\n");
        printf("%s",nombre);
        //Easter eggs
        if(strcmp(nombre,"Among Us\0")==0) printf("\nYou're so sussy\n");
        if(strcmp(nombre,"Harry Potter\0")==0) printf("\nYou're a wizard Harry\n");
        //Opcion para sobreescribir el nombre en caso de necesitarlo
        printf("\n================================\n¿Desea cambiar el nombre? [S] [N]\n");
        confirmacion(&ctrl);
    }while(ctrl!='N' && ctrl!='n');
}

void comienza(int *valor){
    static char ctrl;
    //Bucle para repetir la función en caso de quererlo
    do{
        //Bucle para asegurarse de que lo introducido es un 0 o un 1
        do{
            printf("\n================================\nIntroduzca si desea comenzar el primero de la partida: [S]=1 [N]=0\n");
            scanf("%i",valor);
            fflush(stdin);
            if(*valor!=0 && *valor!=1) printf("\nDebe introducir un 0 o un 1\n");
        }while(*valor!=0 && *valor!=1);
        //Mostrar lo establecido por si no es del agrado del jugador
        if(*valor==0) printf("\nUsted ha establecido no comenzar primero\n");
        if(*valor==1) printf("\nUsted ha establecido comenzar primero\n");
        printf("\n================================\n¿Desea cambiar este ajuste? [S] [N]\n");
        confirmacion(&ctrl);
    }while(ctrl!='N' && ctrl!='n');
}

void tipo_disparo(char *valor){
    static char ctrl;
    //Bucle para repetir la función en caso de quererlo
    do{
        do{
            printf("\n================================\nIntroduzca el tipo de disparo deseado: [Automatico]=A [Manual]=M\n");
            scanf("%c",valor);
            fflush(stdin);
            if(*valor!='A' && *valor!='a' && *valor!='M' && *valor!='m') printf("\nDebe introducir un caracter valido\n");
        }while(*valor!='A' && *valor!='a' && *valor!='M' && *valor!='m');
        //Mostrar lo establecido por si no es del agrado del jugador
        if(*valor=='M' || *valor=='m') printf("\nUsted ha establecido disparo manual\n");
        if(*valor=='A' || *valor=='a') printf("\nUsted ha establecido disparo automatico\n");
        printf("\n================================\n¿Desea cambiar este ajuste? [S] [N]\n");
        confirmacion(&ctrl);
    }while(ctrl!='N' && ctrl!='n');
}

void tam_tab(barcos v_barcos[],int n_barcos, int *valor){
    static char ctrl1;
    static int i,max,ctrl2;
    max=0;
    //Sumatorio para saber el espacio máximo teórico que ocuparían los barcos ya establecidos
    for(i=0;i<n_barcos;i++){
        max=max+((9+((v_barcos[i].tam_barco)-1)*3)*v_barcos[i].num_bar_tipo);
    }
    //Bucle para repetir la función en caso de quererlo
    do{
        printf("\n================================\nIntroduzca el numero que determinara las dimensiones del tablero\n");
        //Bucle que se asegura de que en el espacio establecido quepan todos los barcos
        do{
        ctrl2=1;
        scanf("%i",valor);
        fflush(stdin);
        //Comparación para saber si todos los barcos cabrían en el nuevo tablero
        if(((*valor)*(*valor))<max){
            printf("\nLas dimensiones del tablero no son lo suficientemente grandes, por favor, escoja un numero mayor que %i\n",max);
            ctrl2=0;
        }}while(ctrl2==0);
        //Mostrar lo establecido por si no es del agrado del jugador
        printf("\n================================\nLas dimensiones de su tablero seran de %i x %i\n¿Desea cambiarlas? [S] [N]\n",*valor,*valor);
        confirmacion(&ctrl1);
    }while(ctrl1!='N' && ctrl1!='n');
}

void cantipbar(barcos v_barcos[],int n_barcos){
    static char ctrl1,ctrl2;
    static int i, pos;
    printf("\n================================\nEL ASTILLERO\n================================\n");
    //Escritura de todos los barcos que se encuentran en memoria antes de hacer ningún cambio
    for(i=0;i<n_barcos;i++){
            printf("%i-",v_barcos[i].id_barco);
            printf("%s: ",v_barcos[i].nomb_barco);
            if(v_barcos[i].num_bar_tipo==NULL)
                v_barcos[i].num_bar_tipo=0;
            printf("%i\n",v_barcos[i].num_bar_tipo);
    }
    //Bucle para repetir la función en caso de quererlo
    do{
            //Bucle para cambiar la cantidad de los barcos
            do{
            printf("\n================================\nSeleccione la id del barco cuya cantidad desea modificar\n");
            //Bucle que se asegura de que el jugador coja una id válida
            do{
            scanf("%i",&pos);
            fflush(stdin);
            i=0;
            while(pos!=v_barcos[i].id_barco&&i<n_barcos)
                i++;
            if(i==n_barcos)
            printf("La id indicada no esta definida, inserte otro valor\n");
            }while(i==n_barcos);
            printf("\nIntroduzca la nueva cantidad de %s\n",v_barcos[i].nomb_barco);
            scanf("%i",&v_barcos[i].num_bar_tipo);
            fflush(stdin);
            printf("\n================================\n¿Desea cambiar otra cantidad de otro barco? [S] [N]");
            confirmacion(&ctrl1);
            }while(ctrl1!='N' && ctrl1!='n');
        //Mostrar por pantalla el nuevo astillero con los cambios ya aplicados
        printf("\n================================\nEL ASTILLERO\n================================\n");
        for(i=0;i<n_barcos;i++){
        printf("%i-",v_barcos[i].id_barco);
        printf("%s: ",v_barcos[i].nomb_barco);
        if(v_barcos[i].num_bar_tipo==NULL)
            v_barcos[i].num_bar_tipo=0;
        printf("%i\n",v_barcos[i].num_bar_tipo);
        }
        printf("\n================================\nEste es su astillero actual. ¿Desea hacer algun otro cambio a la cantidad de los barcos? [S] [N]\n");
        confirmacion(&ctrl2);
    }while(ctrl2!='N' && ctrl2!='n');
}

void crear_barco(bar_vect *barc, juego *jug){
    char ctrl2;
    int i,j,max,ctrl1;
    printf("\n================================\nA continuación usted va a crear barcos nuevos para la flota\n================================\n");
    //Bucle para repetir la función en caso de quererlo
    do{
        //Aumento del vector dinamico y la cantidad de tipos de barco
        barc->num_tipo_bar++;
        barc->bar=(barcos*)realloc(barc->bar,(barc->num_tipo_bar)*sizeof(barcos));
        printf("\nVamos a proceder con el ingreso de datos para este nuevo barco\n");
        printf("\n----\nNombre:\n----\n");
        //Se resta 1 a la cantidad de tipos porque i será nuestro acceso a la posición en el vector
        i=barc->num_tipo_bar-1;
        int_nombre(barc->bar[i].nomb_barco);
        printf("\n----\nID:\n----\n");
        ctrl1=0;
        //Bucle que se asegura de que la nueva id no este ya cogida por otro barco
        do{
           printf("Introduzca la id del nuevo barco: ");
           fflush(stdin);
           scanf("%c",&barc->bar[i].id_barco);
           for(j=0;j<=i;j++){
            if(barc->bar[i].id_barco==barc->bar[j].id_barco){
                ctrl1=1;
                printf("El id establecido ya esta ocupado por otro barco, por favor, utilize otro caracter\n");
            }
           }
        }while(ctrl1==1);
        printf("\n----\nDimensiones del barco:\n----\n");
        fflush(stdin);
        scanf("%i",&barc->bar[i].tam_barco);
        printf("\n----\nNumero de unidades:\n----\n");
        fflush(stdin);
        scanf("%i",&barc->bar[i].num_bar_tipo);
        max=0;
        //Calculo del nuevo tamaño máximo teórico que podrían ocupar los barcos
        for(j=0;j<=i;j++){
                max=max+((9+((barc->bar[j].tam_barco)-1)*3)*(barc->bar[j].num_bar_tipo));
        }
        //En caso de que los barcos no cupieran en el tablero viejo, se obligará al jugador a aumentar el tablero
        if(max>((jug->tam_tablero)*(jug->tam_tablero))){
            printf("\nCon la nueva adicion ya no es posible colocar todos los barcos en el tablero.\nA continuacion vamos a cambiar las dimensiones del tablero");
            tam_tab(barc->bar,barc->num_tipo_bar,&jug->tam_tablero);
        }
        printf("\n================================\nImplementacion terminada. ¿Desea crear otro barco? [S] [N]\n");
        confirmacion(&ctrl2);
    }while(ctrl2=='S' || ctrl2=='s');
}
