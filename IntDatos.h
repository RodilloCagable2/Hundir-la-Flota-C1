//Archivo de cabecera del Módulo Introducir Datos

#ifndef INTDATOS_H_INCLUDED
#define INTDATOS_H_INCLUDED
#include "MenuP.h"

//Funciones que usara la configuracion

//Función Introducir Nombre
//Precondicion: char nombre[] es el vector de caracteres donde almacenaremos la cadena, su tamaño maximo es 20
//Postcondicion: Introducir una cadena de caracteres a un vector desde el teclado
void int_nombre(char nombre[]);

//Función Determinar si comienza
//Precondición: int *valor es un puntero a entero donde se introducirá el valor
//Postcondición: Introducir un 0 o 1 y almacenarlo mediante el puntero, además de asegurarse que solo pueda ser un 1 o un 0.
void comienza(int *valor);

//Función selectora del tipo de disparo
//Precondición: int *valor es un puntero a caracter donde se introducirá el valor
//Postcondición: Introducir un A o M y almacenarlo mediante el puntero, además de asegurarse que solo pueda ser un A o un M.
void tipo_disparo(char *valor);

//Función tamaño tablero
/*Precondición: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos. int *valor sera el puntero donde guardaremos el tamaño del tablero*/
/*Postcondición: Establecer el tamaño del tablero y asegurarse de que este no pueda ser más pequeño al tamaño teórico máximo que ocupanrán los barcos*/
void tam_tab(barcos v_barcos[],int n_barcos, int *valor);

//Función determinar cantidad de barco por tipo
//Precondición: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos.
//Postcondición: Establecer la cantidad de barcos que hay por cada tipo.
void cantipbar(barcos v_barcos[],int n_barcos);

//Función añadir barcos nuevos
//Precondición bar_vect *barc es un puntero que pasa la totalidad del registro bar_vect, juego *jug es un puntero que pasa la totalidad del registro juego
//Postcondición Añadir un barco nuevo al registro con todas sus características sin afectar a los ya establecidos
void crear_barco(bar_vect *barc, juego *jug);

//Función que cuenta el total de barcos
//Precondición int *valor es un puntero a entero que será donde se guarda el total, bar_vect *barc es un puntero que pasa la totalidad del registro bar_vect
//Postcondición Contar el número total de barcos y almacenarlo mediante un puntero.
void tot_barco(int *valor,bar_vect *barc);

#endif // INTDATOS_H_INCLUDED