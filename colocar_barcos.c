//COLOCAR BARCOS.C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "MenuP.h"
#include "colocar_barcos.h"
#include "Complementos.h"


void jug_colocar_barcos(bar_vect *v_barcos, juego *jug, jug_vect *j_vect){
    printf("inicio");
    int i, id;
    char d;
    printf("COLOCAR BARCOS");
    for(i=0;i<2;i++){
        
        id=j_vect->jug[i].id_jug;
        d=j_vect->jug[i].tipo_disp;
        //printf("tipo disparo: %c", d);
        if(d=='M'){
            //printf("llega a usuario");
            colocar_barcos_manual(v_barcos,jug,j_vect, id);
        }
        else{
            //llamara a la funcion colocar barcos de forma automatica
            colocar_barco_automatico(v_barcos, jug, j_vect, id);
        }
    }
}


void colocar_barcos_manual(bar_vect *v_barcos, juego *jug, jug_vect *j_vect, int id_jug){
    //otras variables
    int i, id_encontrada, total, cont, fila, colum, tam, dir, sol, j, x_aux, y_aux, car;
    char id_b;     //id_b almacena la id del barco seleccionado por el usuario 
    double porcentaje;

       
    total=jug->num_total_bar; //contador para ir restando cada vez que coloquemos un barco
    
    

    int num_tipo_col[v_barcos->num_tipo_bar];   //creamos un vector en el que cada posicion almacenará cuantos barcos de ese tipo se han colocado ya
    for (i = 0; i < v_barcos->num_tipo_bar; i++) {
        num_tipo_col[i] = 0; // Inicializamos manualmente cada posición a 0
    }

    //se pregunta al usuario que introduzca una id tantas veces como barcos hay5
    do{
        //clear();
        //printf("total: %d ", total);
        mostrar_info_barcos(v_barcos);  //mostramos por  pantalla todos los barcos que se deben colocar y su tamaño
        //volvemos a cargar los datos del fichero para tener la ultima actualizacion del tablero 
        car=cargar_datajuego(jug, v_barcos, j_vect);
        
        printf("TABLERO ACTUAL\n");
        mostrar_tablero(jug, j_vect, id_jug);

        //comprobamos si la id seleccionada por el usuario es valida
        printf("\nINTRODUCE UNA ID VALIDA\n");
        scanf("%c", &id_b);
        fflush(stdin);
        id_encontrada=id_valida(id_b, v_barcos);

        if(id_encontrada == 0)
            printf("--- NO ES UNA ID VALIDA, INTENTELO DE NUEVO ---\n");
        
        
        //comprobamos si ya se han colocado todos los barcos de ese tipo
        for(i=0;i<v_barcos->num_tipo_bar;i++){
            if(v_barcos->bar[i].id_barco==id_b){
                //comprobamos si quedan disponibles barcos de ese tipo
                //printf("%c - %d\n", v_barcos->bar[i].id_barco, v_barcos->bar[i].num_bar_tipo );
                //printf("vector num_tipo_col: %d\n", num_tipo_col[i]);
                if(num_tipo_col[i]<v_barcos->bar[i].num_bar_tipo){
                    printf("INTRODUCE LA PRIMERA COORDENADA: \n");
                    printf("- (FILA): ");
                    scanf("%d", &fila);
                    printf("- (COLUMNA): ");
                    scanf("%d", &colum);

                    printf("INTRODUCE LA DIRECCIÓN EN LA QUE VAS A COLOCAR EL BARCO \n");
                    printf("    1. NORTE\n");
                    printf("    2. SUR\n");
                    printf("    3. ESTE\n");
                    printf("    4. OESTE\n");
                    printf("    5. NORESTE\n");
                    printf("    6. NOROESTE\n");
                    printf("    7. SURESTE\n");
                    printf("    8. SUROESTE\n");
                    dir = input_int();

                    tam=v_barcos->bar[i].tam_barco;
                    printf("direccion elegida: %d\n", dir);
                    printf("tamaño del barco elegido: %d\n", tam);
                    coordenada c[tam]; //vector del tamaño del barco en cada posicion hay una coordenada del barco
                    //printf("crea c\n");
                    sol=calcular_coordenadas(fila, colum, dir, c, tam, jug, j_vect, id_jug);
                    //printf("todas coordenadas son correctas?: %d", sol);
                    
                    if(sol==1){
                        //colocar barco en el tablero flota
                        for(j=0;j<tam;j++){
                            /*printf("coordenadas en c\n");
                            printf("coordenada x en c: %d\n", c[j].fila);
                            printf("coordenada y en c: %d\n", c[j].colum);*/

                            fila=c[j].fila;
                            colum=c[j].colum;
                            
                            j_vect->jug[id_jug].tablero1[fila][colum]='X';
                        }

                        
                        guardar_datajuego(jug, v_barcos, j_vect);   //se guarda en el fichero el tablero modificado

                        printf("TABLERO DESPUES DE COLOCAR EL BARCO: \n");
                        mostrar_tablero(jug, j_vect, id_jug);
                        num_tipo_col[i]++;            //aumentamos el numero de barcos colocados de ese tipo
                        total--;


                        //despues de colocar el barco, calculamos el porcentaje de tablero ocupado para que ya no deje colocar mas barcos
                        car=cargar_datajuego(jug, v_barcos, j_vect);
                        porcentaje=porcentaje_tablero(jug, j_vect, id_jug);
                        //printf("PORCENTAJE: %f\n", porcentaje);
                        if(porcentaje>70){
                            printf("- NO ES POSIBLE COLOCAR MAS BARCOS - \n");
                            printf("    - el tablero no dispone de suficiente espacio\n");
                        }

                    }
                    else{
                        printf("LA COORDENADA ES INCORRECTA - INTENTELO DE NUEVO\n");
                    }

                }
                else{
                    printf("YA SE HAN COLOCADO TODOS LOS BARCOS DE ESE TIPO - INTRODUCE OTRO BARCO\n");
                }
            }
        }
        
    }while(total > 0 && porcentaje<70);


}    



void mostrar_info_barcos(bar_vect *v_barcos){
    int i;
    printf("BARCOS DE LA FLOTA \n");
    printf("ID  -   NOMBRE  -   TAMANIO  -   CANTIDAD\n");
    for(i=0;i<v_barcos->num_tipo_bar;i++){
        printf("%c  -   %s  -   %d  -   %d \n", v_barcos->bar[i].id_barco, v_barcos->bar[i].nomb_barco, v_barcos->bar[i].tam_barco, v_barcos->bar[i].num_bar_tipo);
    }

}

void mostrar_tablero(juego*jug, jug_vect *j_vect, int id_jug){
    int k, l;
    //mostrar tablero
    for(k=0;k<jug->tam_tablero;k++){
        for(l=0;l<jug->tam_tablero;l++){
            printf("%c", j_vect->jug[id_jug].tablero1[k][l]);
        }
        printf("\n");
    }
}

int id_valida(char id_b, bar_vect* v_barcos){
    int i, sol=0;
    for(i=0;i<v_barcos->num_tipo_bar;i++){
        if(id_b==v_barcos->bar[i].id_barco){
            sol=1;
        }
    }
    return sol;
    
}

int calcular_coordenadas(int fila, int colum,int dir, coordenada *c, int tam, juego *jug, jug_vect *j_vect, int id_jug){
    int i, valida=0; 
    //printf("COMPROBAR COORDENADAS\n");
    //comprobamos la primera coordenada
    valida=comprobar_coordenada(fila, colum, jug, j_vect, id_jug);
    printf("primera coordenada correcta?: %d\n", valida);
    if(valida==1){
        //la primera cordenada es correcta
        c[0].fila=fila;
        c[0].colum=colum;
        //printf("entra en comprobar mas a alla de primera coordenada\n");
        //comprobamos las siguientes coordenadas
        for(i=1;i<tam;i++){
            //printf("COORDENADAS PARA VALIDAR\n");
            //printf("numero coordenada: %d+1\n", i);
            valida=0;
            switch(dir){
                case 1:
                    fila=fila-1;
                    break;
                case 2:
                    fila=fila+1;
                    break;
                case 3:
                    colum=colum+1;
                    break;
                case 4:
                    colum=colum-1;
                    break;
                case 5:
                    colum=colum+1;
                    fila=fila-1;
                    break;
                case 6:
                    colum=colum-1;
                    fila=fila-1;
                    break;
                case 7:
                    colum=colum+1;
                    fila=fila+1;
                    break;
                case 8:
                    colum=colum-1;
                    fila=fila+1;
                    break;
        
            }
            //printf("columna: %d\n", colum);
            //printf("fila: %d\n", fila);
            //comprobamos si la siguiente coordenada es correcta    
            valida=comprobar_coordenada(fila, colum, jug, j_vect, id_jug);
            //printf("%d coordenada es correcta?: %d\n", i+1, valida);

            if(valida==1){
                //si es correcta la añadimos al vector
                c[i].colum=colum;
                c[i].fila=fila;
            }
            else{
                //si no es correcta devolvemos cero para no comprobar las siguientes
                //printf("una coordenada ya es incorrecta\n");
                return 0;
            }
        }
        //si ha llegado al final del bucle significa que todas las coordenadas son correctas
        //por tanto devuelvo 1
        return 1;
    }
    else{
        //la primera coordenada es incorrecta
        //printf("primera coordenada incorrecta\n");
        return 0;
    }
    
}


int comprobar_coordenada(int fila, int colum, juego *jug, jug_vect *j_vect, int id_jug){

    int i, j;
    int aux_colum, aux_fila;
   
    //printf("llega a comprobar coordenada\n");
    //comprobamos si las coordenadas estan dentro de los limites del tablero
    if(fila>=jug->tam_tablero || colum>=jug->tam_tablero || fila<0 || colum<0){
        printf("- SUPERA LOS LIMITES DEL TABLERO - \n");
        return 0;
    }
    //printf("dentro de los limites del tablero\n");
    //comprobamos si ya hay un barco en esa coordenada
    //printf("fila: %d\n", fila);
    //printf("columna: %d\n", colum);

    if(j_vect->jug[id_jug].tablero1[fila][colum]=='X'){
        printf("- YA EXISTE UN BARCO - ");
        return 0;
        
    }
    //printf("No sobreescribe un barco\n");
    //comprobamos que no hay barcos alrededor de esa coordenada
    for(i=-1;i<=1;i++){
        aux_fila = fila+i;
        for(j=-1;j<=1;j++){
            aux_colum = colum+j;
            
            if(aux_fila >= 0 && aux_fila< jug->tam_tablero && aux_colum >=0  && aux_colum < jug->tam_tablero /*!(aux_fila==fila && aux_fila==fila)*/){
                /*printf("aux_fila:%d\n", aux_fila);
                printf("aux_colum:%d\n", aux_colum);
                printf("casilla: %c\n", j_vect->jug[id_jug].tablero1[aux_fila][aux_colum]);*/
                if(j_vect->jug[id_jug].tablero1[aux_fila][aux_colum]=='X'){
                    printf("- AL LADO DE ESA COORDENADA SE ENCUENTRA UN BARCO\n");
                    return 0;
                }
            }
            
        }
    }

    //printf("Posicion es valida\n");
    return 1; 

}



void colocar_barco_automatico(bar_vect *v_barcos, juego *jug, jug_vect *j_vect, int id_jug){
    
    int total, pos, cont, i, fila, colum, dir, tam, sol, j, fila_aux, colum_aux, car;
    double porcentaje;

    total=jug->num_total_bar; //contador para ir restando cada vez que coloquemos un barco

    //calculamos la secuencia de valores aleatorios
    //semilla 
    srand(100);

    //creamos un vector en el que cada posicion almacenará cuantod barcos de ese tipo se han colocado ya
    int num_tipo_col[v_barcos->num_tipo_bar];
    for (i = 0; i < v_barcos->num_tipo_bar; i++) {
        num_tipo_col[i] = 0; // Inicializamos manualmente cada posición a 0
    }

    do{

        car=cargar_datajuego(jug, v_barcos, j_vect);

        printf("TABLERO ACTUAL\n");
        mostrar_tablero(jug, j_vect, id_jug);

        //como no podemos generar un caracter aleatorio, elegimos aleatoriamente la posicion 
        //de un tipo de barco en la estructura

        //para obtener un numero entre el numero de tipos de barcos que hay
        //el numero de tipos de barcos que hay lo obtenemos en la estructura bar_vect la variable num_tipo_bat
        pos=rand()%v_barcos->num_tipo_bar; 
            
        //no tenemos que comprobar que una id es valida ya que se genera un numero aleatoriamente que indica la pos

        //comprobamos si ya se han colocado todos los barcos de ese tipo
        if(num_tipo_col[pos]<v_barcos->bar[pos].num_bar_tipo){
            //generamos aleatoriamente la primera coordenada del barco
            fila=rand()%jug->tam_tablero;           //generamos la coordenada x
            colum=rand()%jug->tam_tablero;          //generamos la coordenada y

            //calculamos la direccion en la que se va a colocar el barco                //hay ocho direcciones posibles
            dir=(rand()%7)+1 ;

            /*printf("fila: %d\n", fila);
            printf("columna: %d\n", colum);
            printf("direccion: %d\n", dir);*/
            fflush(stdout);
            /*printf("barco a colocar: %s\n", v_barcos->bar[pos].nomb_barco);
            printf("id: %c\n",v_barcos->bar[pos].id_barco);*/


            tam=v_barcos->bar[pos].tam_barco;
            coordenada c[tam];
            
            sol=calcular_coordenadas(fila, colum, dir, c, tam, jug, j_vect, id_jug);

            
            if(sol==1){
                //colocar barco en el tablero flota
                for(j=0;j<tam;j++){
                    fila=c[j].fila;
                    colum=c[j].colum;
                    j_vect->jug[id_jug].tablero1[fila][colum]='X';
                }

                guardar_datajuego(jug, v_barcos, j_vect);   //se guarda en el fichero el tablero modificado

                printf("TABLERO DESPUES DE COLOCAR UN NUEVO BARCO\n");
                mostrar_tablero(jug, j_vect, id_jug); 

                num_tipo_col[i]++;
                total--; 

                //despues de colocar el barco, calculamos el porcentaje de tablero ocupado para que ya no deje colocar mas barcos
                /*porcentaje=porcentaje_tablero(jug, j_vect, id_jug);
                if(porcentaje>70){
                    printf("- NO ES POSIBLE COLOCAR MAS BARCOS - \n");
                    printf("    - el tablero no dispone de suficiente espacio\n");
                }*/
            }

            else{
                printf("la coordenada es incorrecta\n");
            }
        }
        else{
            printf("ya se han colocado todos los barcos de ese tipo\n");
        }

    }while(total>0 /*&& porcentaje<70*/);
        


        
    

    
}


double porcentaje_tablero(juego *jug, jug_vect*j_vect, int id){
    int i, j, sol, cont=0;     //cont almacena el numero de posiciones ocupadas de un tablero
                                //sol almacena el resultado de la llamada a la funcion alrededor_barco
    double porcentaje=0.0, aux, tam;
    
    for(i=0;i<jug->tam_tablero;i++){
        for(j=0;j<jug->tam_tablero;j++){
            /*printf("fila: %d\n", i);
            printf("columna: %d\n", j);*/
            sol=alrededor_barco(jug, j_vect, i, j, id);
            //printf("sol: %d\n", sol);
            if(sol==1 || j_vect->jug[id].tablero1[i][j]=='X'){
                cont++;
                //printf("cont: %d\n", cont);
            }
        }
    }

    //printf("contador casillas ocupadas: %d\n", cont);
    tam=pow(jug->tam_tablero,2);
    //printf("tam: %f\n", tam);
    aux=cont*100.0;
    //printf("aux:%f\n",aux);
    porcentaje=aux/tam;
    //printf("porcentaje:%f\n", porcentaje);



    return porcentaje;


}


int alrededor_barco(juego *jug, jug_vect *j_vect, int fila, int col, int id){
    int i, j, aux_fila, aux_colum;
    for(i=-1;i<=1;i++){ 
        aux_fila=fila+i;
        for(j=-1;j<=1;j++){
            aux_colum=col+j;
            /*printf("fila alrededor: %d\n", aux_fila);
            printf("columna alrededor: %d\n", aux_colum);*/

            if(aux_fila >= 0 && aux_fila< jug->tam_tablero && aux_colum >=0  && aux_colum < jug->tam_tablero /*&& !(aux_fila==fila && aux_colum==col*/){
                //printf("dentro tablero\n");
                if(j_vect->jug[id].tablero1[aux_fila][aux_colum]=='X'){
                    //printf("hay un barco en esa posicion\n");
                    //printf("encuentra un barco alrededor\n");
                    //printf("devuelve 1\n");
                    return 1;
                }
            }
            
        }
    }
    return 0;
}





