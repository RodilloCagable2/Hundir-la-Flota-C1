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
}barcos;

typedef struct {
	barcos *bar;
	int num_bar;
}bar_vect;

typedef struct {
	int id_jugador;			//Índice del jugador
	char nomb_jugador[21];	//Nombre del jugador
	char tipo_disp;			//Tipo de disparo (manual o automático)
	int num_disp;			//Número de disparos realizados por el jugador
	int ganador;			//Indicador que informa si el jugador ha sido el ganador en la última ronda
}jugadores;

typedef struct {
	jugadores *jug;
	int num_jug;
}jug_vect;

//---> BARCOS: <---
//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Inicializa una estructura tipo bar_vect con datos almacenados de un fichero
bar_vect cargar_barcos ();

//PRECONDICIÓN: Se le pasa una estructura tipo bar_vect
//POSCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_barcos (bar_vect);

//---> JUGADORES: <---
//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Inicializa una estructura tipo jug_vect con datos almacenados de un fichero
jug_vect cargar_jugadores ();

//PRECONDICIÓN: Se le pasa una estructura tipo jug_vect
//POSCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_jugadores (jug_vect);

#endif