#ifndef COMPLEMENTOS_H_
#define COMPLEMENTOS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void clear ();
void titulo ();

//PRECONDICIÓN: Se le pasa una cadena
//POSCONDICIÓN: Se le cambia el caracter salto de linea por terminador
void terminador_cad (char *);

//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Devuelve un caracter para respuestas si/no
void confirmacion (char *);

//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Devuelve siempre un número entero
int input_int ();

#endif