/*
int i, N;
int **mat;

mat = (int**)malloc(N * sizeof(int*));

for (i = 0; i < N; i++) {
	mat[i] = (int*)malloc(N * sizeof(int));
}

for (i = 0; i < N; i++) {
	free(mat[i]);
}
free(mat);
*/

#ifndef MENUP_H_
#define MENUP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
	char nomb_barco[21];	//Nombre del barco
	char id_barco;			//Identificador del barco
	int tam_barco;			//Tamaño del barco
	int num_bar_tipo;
}barcos;

typedef struct {
	barcos *bar;
	int num_tipo_bar;
}bar_vect;

typedef struct {
	char nomb_jugador[21];	//Nombre del jugador
	char tipo_disp;			//Tipo de disparo (Automático/Manual)
	int tam_tablero;		//Valor n que representa los tamaños de los tableros
	int num_tipo_bar;		//Tipo de barcos a utilizar (Posible vector)
	int num_bar_tipo;		//Número de unidades de cada tipo de barco que conformarán la flota (Posible vector)
	char jugador_com[21];	//Jugador que comienza la partida
}juego;

//---> BARCOS: <---
//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Inicializa una estructura tipo bar_vect con datos almacenados de un fichero
bar_vect cargar_barcos ();

//PRECONDICIÓN: Se le pasa una estructura tipo bar_vect
//POSCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_barcos (bar_vect);

//---> JUEGO: <---
//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Inicializa una estructura tipo jug_vect con datos almacenados de un fichero
juego cargar_datajuego ();

//PRECONDICIÓN: Se le pasa una estructura tipo jug_vect
//POSCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_datajuego (juego);

#endif