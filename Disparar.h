#ifndef DISPARAR_H_INCLUDED
#define DISPARAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "MenuP.h"

// Cabecera: int numeroAleatorio(int)
// Precondici?n: variables no nulas
// Postcondici?n: devuelve un n?mero aleatorio acotado al tama?o del tablero
int numeroAleatorio(int);

// Cabecera: void moverCursorConsola(int, int)
// Precondici?n: Se conoce la posici?n x e y de la matriz
// Postcondici?n: devuelve un n?mero aleatorio acotado al tama?o del tablero
void moverCursorConsola(int, int);

// Cabecera imprimirtablero(int, int, int, jug_vect, int)
// Precondici?n: Variables no nulas
// Postcondici?n: imprime el estado actual del tablero dependiendo del turno actual
void imprimirtablero(int, int, int, jug_vect, int);

// Cabecera: void moverCursor(char, int *, int *, int)
// Precondic??n: Se conoce la posici?n x e y de la matriz y el tama?o del vector
// Postcondici?n: Dependiendo de la tecla presionada modifica las variables cursores.
void moverCursor(char, int *, int *, int);

// Cabecera: tocadoHundido(int, int, jug_vect, int, int, int)
// Precondici?n: Variables no nula
// Postcondici?n: Devuelve la diferencia de las casillas tocadas por el jugador y la cantidad total de casillas que compone un barco
int tocadoHundido(int, int, jug_vect, int, int, int);

// Cabecera: actualizarHundido(int, int, jug_vect, int, int, int, int [])
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica en el tablero del jugador dado las casillas tocadas por casillas hundidas
void actualizarHundido(int, int, jug_vect, int, int, int, int []);

// Cabecera: apuntarJugador(int *, int *, jug_vect, int, int *, int *, int [])
// Precondici?n: Variable no nulas
// Postcondici?n: Modifica el tablero del jugador cu?ndo se cumplen las condiciones
void apuntarJugador(int *, int *, jug_vect, int, int *, int *, int []);

// Cabecera: desplazarCpu(int *, int *, int *, int *, int, jug_vect, int)
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica la posici?n de la Cpu paso a paso dada la posici?n final que deber? tomar dicho valor
void desplazarCpu(int *, int *, int *, int *, int, jug_vect, int);

// Cabecera: apuntarCPU(int *, int *, int *, int *, int *, int *, jug_vect, int, int *, int *, int *, int *, int [])
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica el tablero de la Cpu
void apuntarCPU(int *, int *, int *, int *, int *, int *, jug_vect, int, int *, int *, int *, int *, int []);

// Cabecera: void disparar_jue(jug_vect, bar_vect)
// Precondici?n: Recibo los registros de jugadores y de barcos
// Postcondici?n: modifica la informaci?n de los jugadores
void disparar_jue(jug_vect, bar_vect, juego);

#endif DISPARAR_H_INCLUDED
