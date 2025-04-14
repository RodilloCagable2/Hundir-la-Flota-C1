//Archivo de código del Módulo Configuración

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MenuP.h"
#include "Complementos.h"
#include "Configuracion.h"
#include "IntDatos.h"
#define MAX 100

void Borrar(){
    static char ctrl,ctrl1;
    static int ctrl2;
    FILE *in;
    //Bucle para repetir la funcion en caso de quererlo
    do{
        ctrl1=0;
        ctrl=0;
        ctrl2=0;
        printf("\n================================\nIntroduzca cual de los ficheros desea eliminar.\n [1] Juego.txt | [2] Barcos.txt | [3] Ambos | [0] Salir\n");
        //Bucle para asegurarse de que el jugador elige una opcion correcta
        do{
            scanf("%i",&ctrl2);
            fflush(stdin);
            if(ctrl2!=0 && ctrl2!=1 && ctrl2!=2 && ctrl2!=3 && ctrl2!=4) printf("\nEl numero introducido no es válido, por favor, introduzca un numero del 1 al 4.\n");
        }while(ctrl2!=0 && ctrl2!=1 && ctrl2!=2 && ctrl2!=3 && ctrl2!=4);
        switch(ctrl2){
        //Caso 0 = Salir sin borrar nada
        case 0:
            return;
        //Caso 1 = Borrar Juego.txt
        case 1:
            //Asegurarse de que el borrado no es accidental
            printf("\nUsted va a eliminar el fichero Juego.txt. ¿Esta seguro? (Esta operacion no se podra deshacer) [S] [N]\n");
            confirmacion(&ctrl);
            if(ctrl=='S'||ctrl=='s'){
                if((in=fopen("./Juego.txt","w"))!=NULL){
                   fclose(in);
                   printf("\nEliminacion completada\n");
                }
                else
                    printf("\nError al borrar el fichero\n");
            }
            else
                printf("\nEliminacion cancelada\n");
            break;
        //Caso 2 = Borrar Barcos.txt
        case 2:
            //Asegurarse de que el borrado no es accidental
            printf("\nUsted va a eliminar el fichero Barcos.txt. ¿Esta seguro? (Esta operacion no se podra deshacer) [S] [N]\n");
            confirmacion(&ctrl);
            if(ctrl=='S'||ctrl=='s'){
                if((in=fopen("./Barcos.txt","w"))!=NULL){
                   fclose(in);
                   printf("\nEliminacion completada\n");
                }
                else
                    printf("\nError al borrar el fichero\n");
            }
            else
                printf("\nEliminacion cancelada\n");
            break;
        //Caso 3 = Borrar ambos ficheros
        case 3:
            printf("\nUsted va a eliminar ambos ficheros. ¿Esta seguro? (Esta operacion no se podra deshacer) [S] [N]\n");
            confirmacion(&ctrl);
            if(ctrl=='S'||ctrl=='s'){
                if((in=fopen("./Juego.txt","w"))!=NULL){
                   fclose(in);
                }
                else
                    printf("\nError al borrar Juego.txt\n");
                if((in=fopen("./Barcos.txt","w"))!=NULL){
                   fclose(in);
                }
                else
                    printf("\nError al borrar Barcos.txt\n");
                printf("\nEliminacion completada\n");
            }
            else
                printf("\nEliminacion cancelada\n");
            break;
        }
        printf("\n================================\n¿Desea eliminar otro fichero? [S] [N]\n");
        confirmacion(&ctrl1);
    }while(ctrl1!='N' && ctrl1!='n');
}

void mostrar_barcos(bar_vect *b){
    static int i;
    printf("\n================================\nEL ASTILLERO\n================================\n");
    printf("ID---Nombre---Cantidad\n\n");
    for(i=0;i<b->num_tipo_bar;i++){
            printf("%c-",b->bar[i].id_barco);
            printf("%s: ",b->bar[i].nomb_barco);
            printf("%i\n",b->bar[i].num_bar_tipo);
    }
}

void mostrar_config(jug_vect *j,juego jueg){
    static int i;
    printf("\n================================\nConfiguracion actual\n================================\n");
    //Bucle que imprime ambos jugadores del registro
    for(i=0;i<2;i++){
        printf("\nDatos del jugador %i:\n",i+1);
        printf("Id: %i\n",j->jug[i].id_jug);
        printf("Nombre: %s\n",j->jug[i].nomb_jug);
        //Condicional que traduce a o m en Automatico o Manual respectivamente
        if(j->jug[i].tipo_disp=='m' || j->jug[i].tipo_disp=='M')
            printf("Tipo de disparo: Manual\n");
        else{
            if(j->jug[i].tipo_disp=='a' || j->jug[i].tipo_disp=='A')
            printf("Tipo de disparo: Automatico\n");
        }
        //Condicional que traduce el 0 o 1 en si desea comenzar o no
        if(j->jug[i].comienza==0)
            printf("Comienza: Este jugador no desea comenzar primero\n");
        else{
            if(j->jug[i].comienza==1)
            printf("Comienza: Este jugador desea comenzar primero\n");
        }
        printf("\n================================\n");
    }
    printf("\nDimensiones del tablero: %i x %i\n",jueg.tam_tablero,jueg.tam_tablero);
    printf("\n================================\n");
}

void intro_dat(jug_vect *jueg, juego *j,bar_vect *barc){
    int op,op2,auxi;
    char ctrl,auxc;
    //Bucle para repetir la función en caso de quererlo
    do{
        ctrl=0;
        op2=0;
        //Menu que le muestra al jugador las opciones y no le deja salir hasta que la op indique una de las opciones
        do {
			printf("\n<<<Introducir Datos>>>\n\n");
			Sleep(1000);
			printf("1. Nombre de un jugador\n");
			printf("2. Tipo de disparo\n");
			printf("3. Comienzo\n");
			printf("4. Dimensiones del tablero\n");
			printf("5. Cantidad de barcos por tipo\n");
			printf("6. Crear barcos nuevo\n");
			printf("7. Volver\n\n");
			scanf("%d", &op);
			fflush(stdin);
		}while (op < 1 || op > 7);
        switch(op){
            case 1:
                //Cambiar o Introducir el nombre a un jugador
                printf("\n================================\nSeleccione el jugador cuyo nombre desea cambiar. [1] [2]\n");
                //Bucle que se asegura de que se escoja un jugador valido
                do{
                    scanf("%d",&op2);
                    fflush(stdin);
                    if(op2!=1 && op2!=2) printf("El valor introducido no es válido, por favor intentelo de nuevo\n");
                }while(op2!=1 && op2!=2);
                op2=op2-1;
                int_nombre(jueg->jug[op2].nomb_jug);
                break;
            case 2:
                //Seleccionar si el disparo es automatico o manual
                auxc=0;
                printf("\n================================\nSeleccione el jugador cuyo tipo de disparo desea cambiar. [1] [2]\n");
                //Bucle que se asegura de que se escoja un jugador valido
                do{
                    scanf("%d",&op2);
                    fflush(stdin);
                    if(op2!=1 && op2!=2) printf("El valor introducido no es válido, por favor intentelo de nuevo\n");
                }while(op2!=1 && op2!=2);
                op2=op2-1;
                tipo_disparo(&auxc);
                jueg->jug[op2].tipo_disp=auxc;
                break;
            case 3:
                //Seleccionar si el jugador seleccionado quiere empezar o no
                auxi=0;
                printf("\n================================\nSeleccione el jugador cuya variable de comienzo desea cambiar. [1] [2]\n");
                //Bucle que se asegura de que se escoja un jugador valido
                do{
                    scanf("%d",&op2);
                    fflush(stdin);
                    if(op2!=1 && op2!=2) printf("El valor introducido no es válido, por favor intentelo de nuevo\n");
                }while(op2!=1 && op2!=2);
                op2=op2-1;
                comienza(&auxi);
                jueg->jug[op2].comienza=auxi;
                break;
            case 4:
                //Modificar las dimensiones del tablero
                auxi=0;
                tam_tab(barc->bar,barc->num_tipo_bar,&auxi);
                j->tam_tablero=auxi;
                break;
            case 5:
                //Modificar la cantidad de barcos de cada tipo
                cantipbar(barc->bar,barc->num_tipo_bar);
                break;
            case 6:
                //Crear barcos nuevos
                crear_barco(barc,j);
                break;
        }
        printf("\n================================\nDesea hacer algo mas? [S] [N]\n");
        confirmacion(&ctrl);
    }while(ctrl!='N' && ctrl!='n');
}
