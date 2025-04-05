//Archivo de cabecera del M�dulo Introducir Datos

#ifndef INTDATOS_H_INCLUDED
#define INTDATOS_H_INCLUDED
#include "MenuP.h"

//Funciones que usara la configuracion

//Funci�n Introducir Nombre
//Precondicion: char nombre[] es el vector de caracteres donde almacenaremos la cadena, su tama�o maximo es 20
//Postcondicion: Introducir una cadena de caracteres a un vector desde el teclado
void int_nombre(char nombre[]);

//Funci�n Determinar si comienza
//Precondici�n: int *valor es un puntero a entero donde se introducir� el valor
//Postcondici�n: Introducir un 0 o 1 y almacenarlo mediante el puntero, adem�s de asegurarse que solo pueda ser un 1 o un 0.
void comienza(int *valor);

//Funci�n selectora del tipo de disparo
//Precondici�n: int *valor es un puntero a caracter donde se introducir� el valor
//Postcondici�n: Introducir un A o M y almacenarlo mediante el puntero, adem�s de asegurarse que solo pueda ser un A o un M.
void tipo_disparo(char *valor);

//Funci�n tama�o tablero
/*Precondici�n: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos. int *valor
                sera el puntero donde guardaremos el tama�o del tablero*/
/*Postcondici�n: Establecer el tama�o del tablero y asegurarse de que este no pueda ser m�s peque�o al tama�o te�rico m�ximo que ocupanr�n
                 los barcos*/
void tam_tab(barcos v_barcos[],int n_barcos, int *valor);

//Funci�n determinar cantidad de barco por tipo
//Precondici�n: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos.
//Postcondici�n: Establecer la cantidad de barcos que hay por cada tipo.
void cantipbar(barcos v_barcos[],int n_barcos);

//Funci�n a�adir barcos nuevos
//Precondici�n bar_vect *barc es un puntero que pasa la totalidad del registro bar_vect, juego *jug es un puntero que pasa la totalidad del registro juego
//Postcondici�n A�adir un barco nuevo al registro con todas sus caracter�sticas sin afectar a los ya establecidos
void crear_barco(bar_vect *barc, juego *jug);

#endif // INTDATOS_H_INCLUDED
