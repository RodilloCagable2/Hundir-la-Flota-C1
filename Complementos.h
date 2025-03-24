#ifndef COMPLEMENTOS_H_
#define COMPLEMENTOS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Estructura para manejar la animación del título
typedef struct {
    HANDLE hThread;
    int activo;
    int posicion;
} TituloAnimado;

void clear();
void titulo();
void iniciar_titulo_animado(TituloAnimado* titulo);
void detener_titulo_animado(TituloAnimado* titulo);

//PRECONDICIÓN: Se le pasa una cadena
//POSCONDICIÓN: Se le cambia el caracter salto de linea por terminador
void terminador_cad(char*);

//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Devuelve un caracter para respuestas si/no
void confirmacion(char*);

//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Devuelve siempre un número entero
int input_int();

#endif