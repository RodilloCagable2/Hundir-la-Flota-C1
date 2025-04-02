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
	char id_barco;			//Identificador del tipo de barco
	int tam_barco;			//Tamaño del barco
	int num_bar_tipo;
}barcos;

typedef struct {
	barcos *bar;
	int num_tipo_bar;
}bar_vect;

typedef struct {
	int id_jug;				//Índice del jugador
	char nomb_jug[21];		//Nombre del jugador
	int num_disp;			//Número de disparos
	char tipo_disp;			//Tipo de disparo (A = Automático / M = Manual)
	int comienza;			//Jugador que comienza la partida
	int ganador;			//0 = False / 1 = True
	char **tablero1;		//Tablero con la flota del jugador
	char **tablero2;		//Tablero con la flota del oponente en el cual se dispara
}jugadores;

typedef struct {
	jugadores jug[2];
}jug_vect;

typedef struct {
	int tam_tablero;		//Valor n que representa los tamaños de los tableros
	char tipo_bar[13];		//Tipos de barco a utilizar
	int num_tipo_bar;		//Número de tipos de barco a utilizar
	int *num_bar_tipo;		//Número de unidades de cada tipo de barco que conformarán la flota
	int num_total_bar;		//Número total de barcos que conformarán la flota
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
juego cargar_datajuego (bar_vect, jug_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo jug_vect
//POSCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_datajuego (juego, bar_vect, jug_vect);

//---> RESUMEN: <---
void resumen_partida ();

//---> MENÚS: <---
void menu_configuracion ();

void menu_partida ();

void menu_principal ();

//---> GESTIÓN DE MEMORIA: <---
//PRECONDICIÓN: Se le pasa una estructura tipo jug_vect
//POSCONDICIÓN: Libera la memoria de los tableros
void liberar_tableros(jug_vect *jv, int tam_tablero);

//PRECONDICIÓN: Se le pasa una estructura tipo bar_vect
//POSCONDICIÓN: Libera la memoria de los barcos
void liberar_barcos(bar_vect *b);

//PRECONDICIÓN: Se le pasa una estructura tipo juego
//POSCONDICIÓN: Libera la memoria de num_bar_tipo
void liberar_juego(juego *j);

//---> VALIDACIÓN: <---
//PRECONDICIÓN: Se le pasa un nombre
//POSCONDICIÓN: Devuelve 1 si el nombre es válido, 0 si no
int validar_nombre(const char *nombre);

//PRECONDICIÓN: Se le pasa un identificador de barco
//POSCONDICIÓN: Devuelve 1 si el ID es válido, 0 si no
int validar_id_barco(char id);

//PRECONDICIÓN: Se le pasa un tamaño de barco
//POSCONDICIÓN: Devuelve 1 si el tamaño es válido, 0 si no
int validar_tam_barco(int tam);

#endif