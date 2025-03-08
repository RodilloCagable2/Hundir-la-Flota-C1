//Archivo de código del Módulo Introducir Datos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IntDatos.h"

void int_nombre(char nombre[]){
    static char ctrl;
    do{
        fflush(stdin);
        printf("\n================================\nIntroduzca su nombre por favor:\n");
        fgets(nombre,20,stdin);
        nombre[strcspn(nombre, "\n")] = 0;
        //Mostrar el nombre escrito por si no es del agrado del usuario
        printf("\n================================\nEl nombre introducido es:\n");
        printf("%s",nombre);
        //Easter eggs
        if(strcmp(nombre,"Among Us")==0) printf("\nYou're so sussy\n");
        if(strcmp(nombre,"Harry Potter")==0) printf("\nYou're a wizard Harry\n");
        //Opcion para sobreescribir el nombre en caso de necesitarlo
        do{
                printf("\n================================\n¿Desea cambiar el nombre? [S] [N]");
                fflush(stdin);
                scanf("%c",&ctrl);
                if(ctrl!='S' && ctrl!='s'&& ctrl!='N'&& ctrl!='n') printf("\nSu respuesta no es valida, introduzca S o N por favor\n");
        }while(ctrl!='S' && ctrl!='s'&& ctrl!='N'&& ctrl!='n');
    }while(ctrl!='N' && ctrl!='n');
}

/*void num_barco(int barcos[],int tam){
    static int ctrl;
    printf("\n================================\nIntroduzca la cantidad de barcos con la que desea jugar:\n");
    do{
        ctrl=1;
        printf("\nSubmarinos (1x1):");
        scanf("%i",&barcos[0]);
        printf("\nFragatas (1x2):");
        scanf("%i",&barcos[1]);
        printf("\nDestructores (1x3):");
        scanf("%i",&barcos[2]);
        printf("\nCruceros (1x4):");
        scanf("%i",&barcos[3]);
        printf("\nAcorazados (1x5):");
        scanf("%i",&barcos[4]);
        printf("\nPortaaviones (1x6):");
        scanf("%i",&barcos[5]);
        /*El condicional impedira que el jugador añada demasiados barcos, esto lo hace mediante una aproximación, que consiste en la comparación de las casillas totales,
        con las casillas teoricas ocupadas, siendo estas las casillas que ocupa un barco y sus adyacentes
        if((tam*tam)<(9*barcos[0]+12*barcos[1]+15*barcos[2]+18*barcos[3]+21*barcos[4]+24*barcos[5])){
            printf("\nUsted a puesto demasiados barcos, introduzcalos de nuevo\n");
            //La variable de control se encargara de reiniciar el bucle
            ctrl=0;
        }
    }while(ctrl!=1);
}*/

int comienza(int valor){
    static char ctrl;
    do{
        do{
        printf("\n================================\nIntroduzca si desea comenzar el primero de la partida: [S]=1 [N]=0\n");
        scanf("%i",&valor);
        if(valor!=0 && valor!=1) printf("\nDebe introducir un 0 o un 1\n");
        }while(valor!=0 && valor!=1);
        if(valor==0) printf("\nUsted ha establecido no comenzar primero\n");
        if(valor==1) printf("\nUsted ha establecido comenzar primero\n");
        do{
                printf("\n================================\n¿Desea cambiar este ajuste? [S] [N]");
                scanf("%c",&ctrl);
                if(ctrl!='S' && ctrl!='s'&& ctrl!='N'&& ctrl!='n') printf("\nSu respuesta no es valida, introduzca S o N por favor\n");
        }while(ctrl!='S' && ctrl!='s'&& ctrl!='N'&& ctrl!='n');
    }while(ctrl!='N' && ctrl!='n');
    return valor;
}

int tipo_disparo(int valor){
    static char ctrl;
    do{
        do{
        printf("\n================================\nIntroduzca el tipo de disparo que desea: [Automatico]=1 [Manual]=0\n");
        scanf("%i",&valor);
        if(valor!=0 && valor!=1) printf("\nDebe introducir un 0 o un 1\n");
        }while(valor!=0 && valor!=1);
        if(valor==0) printf("\nUsted ha establecido disparo manual\n");
        if(valor==1) printf("\nUsted ha establecido disparo automatico\n");
        do{
                printf("\n================================\n¿Desea cambiar este ajuste? [S] [N]");
                scanf("%c",&ctrl);
                if(ctrl!='S' && ctrl!='s'&&ctrl!='N'&&ctrl!='n') printf("\nSu respuesta no es valida, introduzca S o N por favor\n");
        }while(ctrl!='S' && ctrl!='s'&&ctrl!='N'&&ctrl!='n');
    }while(ctrl!='N' && ctrl!='n');
    return valor;
}

int tam_tab(int valor){
    static char ctrl;
    do{
        fflush(stdin);
        printf("\n================================\nIntroduzca el numero que determinara las dimensiones del tablero\n");
        scanf("%i",&valor);
        printf("\nLas dimensiones de su tablero son %i x %i\n",valor,valor);
        do{
            fflush(stdin);
                printf("\n================================\n¿Desea cambiar este ajuste? [S] [N]");
                scanf("%c",&ctrl);
                if(ctrl!='S'&& ctrl!='s'&&ctrl!='N'&&ctrl!='n') printf("\nSu respuesta no es valida, introduzca S o N por favor\n");
        }while(ctrl!='S' && ctrl!='s'&&ctrl!='N'&&ctrl!='n');
    }while(ctrl!='N' && ctrl!='n');
    return valor;
}
int cont_barco(){
    FILE *in;
    char c;
    int cont;
    cont=0;
    if((in=fopen("./Ficheros/Barcos.txt","r"))!=NULL){
    while(c!=EOF){
        c=fgetc(in);
        if(c=='\n') cont++;
    }}
     else
        printf("\nError al abrir el archivo\n");
    fclose(in);
    return cont;
}
void perso_barco(){
    FILE *in;
    char aux[20];
    int cont,tam,can;
    char c,ctrl;
    cont=cont_barco();
    if((in=fopen("./Ficheros/Barcos.txt","a"))!=NULL){
        do{
            system("cls");
            fprintf(in,"%i",cont);
            cont++;
            fprintf(in,"%c",'-');
            printf("\nIntroduzca el nombre del barco. Para terminar con el nombre\n");
            fflush(stdin);
            fgets(aux,20,stdin);
            aux[strcspn(aux, "\n")] = 0;
            fprintf(in,"%s",aux);
            fprintf(in,"%c",'-');
            printf("\nIntroduzca la dimension del barco\n");
            do{
                    scanf("%i",&tam);
                    fflush(stdin);
                    if(tam==0) printf("La dimension no puede ser 0\n");
            }while(tam==0);
            fprintf(in,"%i",tam);
            fprintf(in,"%c",'-');
            printf("\nIntroduzca cuantos barcos de este tipo desea\n");
              do{
                    scanf("%i",&can);
                    fflush(stdin);
                    if(can<0) printf("No puede haber barcos negativos\n");
              }while(can<0);
            fprintf(in,"%i",can);
            fprintf(in,"%c",'\n');
            do{
            fflush(stdin);
                printf("\n================================\n¿Desea terminar? [S] [N]");
                scanf("%c",&ctrl);
                if(ctrl!='S'&& ctrl!='s'&&ctrl!='N'&&ctrl!='n') printf("\nSu respuesta no es valida, introduzca S o N por favor\n");
        }while(ctrl!='S' && ctrl!='s'&&ctrl!='N'&&ctrl!='n');
        }while(ctrl!='S' && ctrl!='s');
    }
    else
        printf("\nError al abrir el archivo\n");
    fclose(in);
}
