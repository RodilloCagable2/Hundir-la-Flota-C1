//COLOCAR BARCOS.H

#ifndef _COLCAR_BARCOS_H_
#define _COLOCAR_BARCOS_H

#include"MenuP.h"

//cabeceras de funciones y definición de las clases

//clase coordenadas: servira para hacer un vector de este tipo y que en cada posicion almacene una coordenada del barco
typedef struct{
    int fila;
    int colum;
}coordenada;


//Cabecera: void jug_colocar_barcos(bar_vect, juego, jug_vect, coordenada *)
//Precondidicón: variables no nulas
//Postcondicion: depende del tipo de barco que haya seleccionado cada jugador los barcos se colocaran de la misma manera
void jug_colocar_barcos(bar_vect*, juego*, jug_vect*);


//Cabecera: void colocar_barcos_manual(int id_jug)
//Precondición: existe esa id de jugador y ese jugador quiere realizar la colocación de barcos de manera manual
//Postcondición: rellena el tablero Flota de un jugador de forma manual, y lo escribe en un fichero 
void colocar_barcos_manual(bar_vect*, juego*, jug_vect*, int);

//Cabecera: void mostrar_info_barcos(bar_vec v_barcos)
//Precondición: la variable v_barcos no debe ser nula
//Postcondición: muestra la información de todos los barcos que debe colocar el usuario
void mostrar_info_barcos(bar_vect*);

void mostrar_tablero(juego*, jug_vect*, int);
//Cabecera: int id_valida(char id_b, bar_vect v_barcos)
//Precondición: las variables no deben ser nula
//Postcondición:compreba si la id de un barco esta en la lista de barcos. Devuelve 0 si no está en la lista y 1 si si está
int id_valida(char, bar_vect*);


//Cabecera: calcular_coordenada(int x, int y, int dir, int tam)
//Precondición: la variables no deben ser nulas
//Postcondición: calcula las coordenadas donde esta colocado el barco y comprueba si son correctas. Si todas las coordenadas son 
//  correctas devuelve un 1 y si alguna es incorrecta devuelve un 0
int calcular_coordenadas(int , int , int , coordenada *, int, juego*, jug_vect*, int);

//Cabecera: int comprobar_coordenada(int x, int y);
//Precondición: las variables no deben ser nulas
//Postcondición: devuelve 1 si la coordenada indicada es correcta y 0 si es incorrecta
int comprobar_coordenada(int , int, juego*, jug_vect*, int);


//Cabecera: void colocar_barco_automatico(bar_vect, juego, jug_vect, coordenada*, int)
//Precondición: las variables no deben ser nulas
//Postcondición: rellena el tabledro flota del jugador que haya elegido colocar barcos de forma automatica
void colocar_barco_automatico(bar_vect*, juego*, jug_vect*, coordenada*, int);

#endif
