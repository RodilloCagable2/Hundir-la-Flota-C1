//DATOS NECESARIOS PARA COLOCAR BARCOS:
//  CONFIGURACIÓN-> 
        //- TIPO JUEGO: automático o manual
        //- valor n que representa los tamaños de los tableros
        //- tipos de barcos a utilizar
        //- número de unidades de cada barco que conformaran la flota
//  MENU-> 
        //- cargar barcos (para mirar los barcos que hay)


#include "MenuP.h"

void colocar_barcos(){
    //definimos una variable de tipo bar_vect en la que almacenaremos la información sobre los barcos
    bar_vect v_barcos;
    v_barcos=cargar_barcos();   //cargamos la información de los barcos en la variable creada anteriormente

    //definimos una variable de tipo jug_vect en la que almacenaremos la información sobre los jugadores
    jug_vect v_jugadores;
    v_jugadores=cargar_jugadores();     //cargamos la información de los jugadores en la variable creada anteriormente

    //otras variables
    int i, j, id_b;     //id_b almacena la id del barco seleccionado por el usuario 
    for(i=0;i<v_jugadores.num_jug;i++){
        print("TABLERO FLOTA JUGADOR CON ID: %d", v_jugadores.jug[i].id_jugador);
        mostrar_info_barcos(v_barcos);  //mostramos por pantalla todos los barcos que se deben colocar y su tamaño
        print("Selecciona el barco que deseas colocar \n");
        scanf("%d", &id_b);
        
    }




}

void mostrar_info_barcos(bar_vect v_barcos){
    int i;
    for(i=0;i<v_barcos.num_bar;i++){
        print("%d - %s - %d \n", v_barcos.bar[i].id_barco, v_barcos.bar[i].nomb_barco, v_barcos.bar[i].tam_barco);
    }

}

