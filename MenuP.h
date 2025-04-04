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

//ESTRUCTURAS:
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
} jugadores;

typedef struct {
	jugadores jug[2];
} jug_vect;

typedef struct {
	int tam_tablero;		//Valor n que representa los tamaños de los tableros
	char tipo_bar[13];		//Tipos de barco a utilizar
	int num_tipo_bar;		//Número de tipos de barco a utilizar
	int *num_bar_tipo;		//Número de unidades de cada tipo de barco que conformarán la flota
	int num_total_bar;		//Número total de barcos que conformarán la flota
}juego;

//---> GESTIÓN DE MEMORIA: <---

//PRECONDICIÓN: jv debe ser un puntero válido
//POSCONDICIÓN: Libera la memoria de los tableros de ambos jugadores
void liberar_tableros(jug_vect *, int);

//PRECONDICIÓN: b debe ser un puntero válido
//POSCONDICIÓN: Libera la memoria de los barcos
void liberar_barcos(bar_vect *);

//PRECONDICIÓN: j debe ser un puntero válido
//POSCONDICIÓN: Libera la memoria del juego
void liberar_juego(juego *);

//---> VALIDACIÓN: <---

//PRECONDICIÓN: nombre debe ser una cadena válida
//POSCONDICIÓN: Devuelve 1 si el nombre es válido, 0 si no lo es
int validar_nombre(const char *);

//PRECONDICIÓN: id debe ser un carácter
//POSCONDICIÓN: Devuelve 1 si el id es válido, 0 si no lo es
int validar_id_barco(char);

//PRECONDICIÓN: tam debe ser un entero
//POSCONDICIÓN: Devuelve 1 si el tamaño es válido, 0 si no lo es
int validar_tam_barco(int);

//---> BARCOS: <---

//PRECONDICIÓN: Ninguna
//POSCONDICIÓN: Devuelve 0 si la carga fue exitosa, -1 si hubo error. La estructura apuntada por b se actualiza con los datos cargados
int cargar_barcos(bar_vect *);

//PRECONDICIÓN: b debe ser un puntero válido
//POSCONDICIÓN: Devuelve 0 si el guardado fue exitoso, -1 si hubo error
int guardar_barcos(bar_vect *);

//---> JUEGO: <---

//PRECONDICIÓN: j, b y jv deben ser punteros válidos
//POSCONDICIÓN: Devuelve 0 si la carga fue exitosa, -1 si hubo error. Las estructuras apuntadas se actualizan con los datos cargados
int cargar_datajuego(juego *, bar_vect *, jug_vect *);

//PRECONDICIÓN: j, b y jv deben ser punteros válidos
//POSCONDICIÓN: Devuelve 0 si el guardado fue exitoso, -1 si hubo error
int guardar_datajuego(juego *, bar_vect *, jug_vect *);

//---> RESUMEN: <---

void resumen_partida();

//---> MENÚS: <---

//PRECONDICIÓN: j, b y jv deben ser punteros válidos
//POSCONDICIÓN: Devuelve 0 si la ejecución fue exitosa, -1 si hubo error
int menu_configuracion(juego *, bar_vect *, jug_vect *);

//PRECONDICIÓN: j, b y jv deben ser punteros válidos
//POSCONDICIÓN: Devuelve 0 si la ejecución fue exitosa, -1 si hubo error
int menu_partida(juego *, bar_vect *, jug_vect *);

//PRECONDICIÓN: j, b y jv deben ser punteros válidos
//POSCONDICIÓN: Devuelve 0 si la ejecución fue exitosa, -1 si hubo error
int menu_principal(juego *, bar_vect *, jug_vect *);

#endif