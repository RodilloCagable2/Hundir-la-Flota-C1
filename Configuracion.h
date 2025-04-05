//Archivo de cabecera del M�dulo Configuraci�n

#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGRACION_H_INCLUDED
#include "MenuP.h"

//Funciones para el manejo de ficheros

//Funci�n Borrar Ficheros
//Precondici�n: N/A
//Postcondici�n: Dar a elegir al usuario cual de los ficheros eliminar y eliminarlos en el acto
void Borrar();

//Funci�n Mostrar Barcos + La Cantidad de cada uno
//Precondici�n: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos.
//Postcondici�n: Mostrar por pantalla todos los tipos de barco y la cantidad de cada uno.
void mostrar_barcos(barcos v_barcos[],int n_barcos);

//Funci�n Mostrar Configuracion
/*Precondici�n: jugadores jug_vect es un vector que almacena datos con esctructura jugadores y  juego jueg es una variable que nos pasar�
                por valor lo almacenado en el registro para su impresi�n*/
//Postcondici�n: Mostrar por pantall la configuraci�n establecida para el juego.
void mostrar_config(jugadores jug_vect[],juego jueg);

//Funcion Introducir Datos
/*Precondici�n: jug_vect *jueg es un puntero que pasa la totalidad del registro jug_vect, juego *j es un puntero que pasa la totalidad del registro juego
                bar_vect *barc es un puntero que pasa la totalidad del registro bar_vect*/
//Postcondici�n: Anexionar todas las funciones de la librer�a IntDatos.h en un menu para facilitar su implementaci�n en MenuP.c
void intro_dat(jug_vect *jueg, juego *j,bar_vect *barc);

#endif // CONFIGURACION_H_INCLUDED
