#ifndef DISPARAR_H_INCLUDED
#define DISPARAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "MenuP.h"
#include "Complementos.h"

// Cabecera: int numeroAleatorio(int)
// Precondición: variables no nulas
// Postcondición: devuelve un número aleatorio acotado al tamaño del tablero
int numeroAleatorio(int);

// Cabecera: void moverCursorConsola(int, int)
// Precondición: Se conoce la posición x e y de la matriz
// Postcondición: devuelve un número aleatorio acotado al tamaño del tablero
void moverCursorConsola(int, int);

// Cabecera imprimirtablero(int, int, int, int, jug_vect *, int)
// Precondición: Variables no nulas
// Postcondición: imprime el estado actual del tablero dependiendo del turno actual
void imprimirtablero(int, int, int, int, jug_vect *, int);

// Cabecera: void moverCursor(char, int *, int *, int)
// Precondicíón: Se conoce la posición x e y de la matriz y el tamaño del vector
// Postcondición: Dependiendo de la tecla presionada modifica las variables cursores.
void moverCursor(char, int *, int *, int);

// Cabecera: tocadoHundido(int, int, jug_vect *, int, int, int)
// Precondición: Variables no nula
// Postcondición: Devuelve la diferencia de las casillas tocadas por el jugador y la cantidad total de casillas que compone un barco
int tocadoHundido(int, int, jug_vect *, int, int, int);

// Cabecera: actualizarHundido(int, int, jug_vect *, int, int, int, int [])
// Precondición: Variables no nulas
// Postcondición: Modifica en el tablero del jugador dado las casillas tocadas por casillas hundidas
void actualizarHundido(int, int, jug_vect *, int, int, int, int []);

// Cabecera: apuntarJugador(int *, int *, jug_vect *, int, int *, int *, int [])
// Precondición: Variable no nulas
// Postcondición: Modifica el tablero del jugador cuándo se cumplen las condiciones
void apuntarJugador(int *, int *, jug_vect *, int, int *, int *, int []);

// Cabecera: desplazarCpu(int *, int *, int *, int *, int, int, jug_vect *, int)
// Precondición: Variables no nulas
// Postcondición: Modifica la posición de la Cpu paso a paso dada la posición final que deberá tomar dicho valor
void desplazarCpu(int *, int *, int *, int *, int, int, jug_vect *, int);

// Cabecera: apuntarCPU(int *, int *, int *, int *, int *, int *, jug_vect *, int, int *, int *, int *, int *, int [])
// Precondición: Variables no nulas
// Postcondición: Modifica el tablero de la Cpu
void apuntarCPU(int *, int *, int *, int *, int *, int *, jug_vect *, int, int *, int *, int *, int *, int []);

// Cabecera: void disparar_jue(jug_vect *, bar_vect *, juego *)
// Precondición: Recibo los registros de jugadores y de barcos
// Postcondición: modifica la información de los jugadores
void disparar_jue(jug_vect *, bar_vect *, juego *);

#endif // DISPARAR_H_INCLUDED