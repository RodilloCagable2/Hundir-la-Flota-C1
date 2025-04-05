//Archivo de cabecera del Módulo Configuración

#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGRACION_H_INCLUDED
#include "MenuP.h"

//Funciones para el manejo de ficheros

//Función Borrar Ficheros
//Precondición: N/A
//Postcondición: Dar a elegir al usuario cual de los ficheros eliminar y eliminarlos en el acto
void Borrar();

//Función Mostrar Barcos + La Cantidad de cada uno
//Precondición: barcos v_barcos[] es un vector que almacena datos con estructura barcos e int n_barcos el numero total de tipos de barcos.
//Postcondición: Mostrar por pantalla todos los tipos de barco y la cantidad de cada uno.
void mostrar_barcos(barcos v_barcos[],int n_barcos);

//Función Mostrar Configuracion
/*Precondición: jugadores jug_vect es un vector que almacena datos con esctructura jugadores y  juego jueg es una variable que nos pasará
                por valor lo almacenado en el registro para su impresión*/
//Postcondición: Mostrar por pantall la configuración establecida para el juego.
void mostrar_config(jugadores jug_vect[],juego jueg);

//Funcion Introducir Datos
/*Precondición: jug_vect *jueg es un puntero que pasa la totalidad del registro jug_vect, juego *j es un puntero que pasa la totalidad del registro juego
                bar_vect *barc es un puntero que pasa la totalidad del registro bar_vect*/
//Postcondición: Anexionar todas las funciones de la librería IntDatos.h en un menu para facilitar su implementación en MenuP.c
void intro_dat(jug_vect *jueg, juego *j,bar_vect *barc);

#endif // CONFIGURACION_H_INCLUDED
