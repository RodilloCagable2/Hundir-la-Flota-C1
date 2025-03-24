#include "MenuP.h"
#include "Complementos.h"

//GESTIÓN DE MEMORIA:
void liberar_tableros (jug_vect *jv, int tam_tablero) {
	int i, fila;
	
	if (jv == NULL) {
		return;
	}
	
	for (i = 0; i < 2; i++) {
		if (jv->jug[i].tablero1 != NULL) {
			for (fila = 0; fila < tam_tablero; fila++) {
				free (jv->jug[i].tablero1[fila]);
			}
			
			free (jv->jug[i].tablero1);
		}
		
		if (jv->jug[i].tablero2 != NULL) {
			for (fila = 0; fila < tam_tablero; fila++) {
				free (jv->jug[i].tablero2[fila]);
			}
			
			free (jv->jug[i].tablero2);
		}
	}
}

void liberar_barcos (bar_vect *b) {
	if (b != NULL && b->bar != NULL) {
		free (b->bar);
		b->bar = NULL;
	}
}

void liberar_juego (juego *j) {
	if (j != NULL && j->num_bar_tipo != NULL) {
		free (j->num_bar_tipo);
		j->num_bar_tipo = NULL;
	}
}

//VALIDACIÓN:
int validar_nombre (const char *nombre) {
	if (nombre == NULL || strlen(nombre) == 0 || strlen(nombre) > 20) {
		return 0;
	}
	
	return 1;
}

int validar_id_barco (char id) {
	return (id >= 'A' && id <= 'Z');
}

int validar_tam_barco (int tam) {
	return (tam > 0 && tam <= 5);
}

//BARCOS:
bar_vect cargar_barcos () {
	char filename[] = "Barcos.txt";
	int num_tipo_bar = 0;						//Número de tipos de barcos registrados
	int i = 0;
	char cad_linea[250];						//Caracteres máximos que puede ocupar una linea en fichero
	int campo_barcos = 0;						//Entero que verifica nº campos de la estructura barcos
	char default_bar[] = "Defaultname-D-1";		//Creación de un barco estandar que ocupará la posición 0 del fichero
	
	FILE *f_bar;
	
	f_bar = fopen (filename, "r");
	
	if (f_bar == NULL) {
		f_bar = fopen (filename, "w");			//Excepción si no encuentra fichero
		fclose (f_bar);
		perror ("No se pudo abrir el archivo de barcos. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_bar);								//Necesario para volver a leer el fichero
	
	if (fgetc(f_bar) == EOF) {					//Si fichero vacío, añadimos barco predeterminado
		f_bar = fopen (filename, "w");
		fprintf (f_bar, default_bar);
		fclose (f_bar);
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_bar)) {		//Contador de barcos en el programa a partir de fichero
		num_tipo_bar++;
	}
	
	rewind (f_bar);
	
	bar_vect b;
	
	b.num_tipo_bar = num_tipo_bar;
	
	b.bar = (barcos*)malloc(b.num_tipo_bar*sizeof(barcos));		//Asignación de memoria dinámica "b.bar[num_bar]"
	
	if (b.bar == NULL) {
		printf ("No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
	
	//BUCLE PARA RELLENAR LA ESTRUCTURA DE BARCOS//
	while (fgets (cad_linea, sizeof(cad_linea), f_bar) && i < num_tipo_bar) {
		campo_barcos = sscanf (cad_linea, "%21[^-]-%c-%d",
		b.bar[i].nomb_barco,
		&b.bar[i].id_barco,
		&b.bar[i].tam_barco);
		
		if (campo_barcos != 3 ||
		!validar_nombre (b.bar[i].nomb_barco) ||
		!validar_id_barco (b.bar[i].id_barco) ||
		!validar_tam_barco (b.bar[i].tam_barco)) {
			printf ("Error en los datos del barco %d\n", i + 1);
			liberar_barcos (&b);
			fclose (f_bar);
			return b;
		}
		
		i++;
	}
	
	fclose (f_bar);
	
	return b;
}

void guardar_barcos (bar_vect b) {
	int i;
	
	FILE *f_bar;
	char filename[] = "Barcos.txt";
	f_bar = fopen (filename, "w");
	
	if (f_bar == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DE CADA BARCO EN FICHERO//
	for (i = 0; i < b.num_tipo_bar; i++) {
		fprintf (f_bar, "%s-%c-%d\n",
		b.bar[i].nomb_barco,
		b.bar[i].id_barco,
		b.bar[i].tam_barco);
	}
	
	fclose (f_bar);
}

//JUEGO:
juego cargar_datajuego (bar_vect b, jug_vect jv) {
	char filename[] = "Juego.txt";
	int i = 0, fila, colum;
	char cad_linea[250];							//Caracteres máximos que puede ocupar una linea en fichero
	int campo_juego = 0;							//Entero que verifica nº campos de la estructura juego
	char default_jue[] = "03-00-1\nA-00\n1-Defaultname1-000-A-0\n~~~\n~~~\n~~~\n~~~\n~~~\n~~~\n2-Defaultname2-000-A-0\n~~~\n~~~\n~~~\n~~~\n~~~\n~~~";	//Creación de un juego estandar
	
	FILE *f_jue;
	
	f_jue = fopen (filename, "r");
	
	if (f_jue == NULL) {
		f_jue = fopen (filename, "w");				//Excepción si no encuentra fichero
		fclose (f_jue);
		perror ("No se pudo abrir el archivo de juego. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_jue);									//Necesario para volver a leer el fichero
	
	if (fgetc(f_jue) == EOF) {						//Si fichero vacío, añadimos juego predeterminado
		f_jue = fopen (filename, "w");
		fprintf (f_jue, default_jue);
		fclose (f_jue);
	}
	
	rewind (f_jue);
	
	juego j;
	
	j.num_tipo_bar = b.num_tipo_bar;
	j.tam_tablero = 3;
	
	j.num_bar_tipo = (int*)malloc(j.num_tipo_bar*sizeof(int));	//Asignación de memoria dinámica "j.num_bar_tipo[num_tipo_bar]"
	
	if (j.num_bar_tipo == NULL) {
		printf ("1: No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
	
	for (i = 0; i < 2; i++) {
		jv.jug[i].tablero1 = (char**)malloc(j.tam_tablero*sizeof(char*));
		
		if (jv.jug[i].tablero1 == NULL) {
			printf ("2: No se ha podido reservar memoria suficiente\n");
			getchar ();
			exit (1);
		}
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			jv.jug[i].tablero1[fila] = (char*)malloc(j.tam_tablero*sizeof(char));
			
			if (jv.jug[i].tablero1[fila] == NULL) {
				printf ("3: No se ha podido reservar memoria suficiente\n");
				getchar ();
				exit (1);
			}
		}
	}
	
	for (i = 0; i < 2; i++) {
		jv.jug[i].tablero2 = (char**)malloc(j.tam_tablero*sizeof(char*));
		
		if (jv.jug[i].tablero2 == NULL) {
			printf ("4: No se ha podido reservar memoria suficiente\n");
			getchar ();
			exit (1);
		}
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			jv.jug[i].tablero2[fila] = (char*)malloc(j.tam_tablero*sizeof(char));
			
			if (jv.jug[i].tablero2[fila] == NULL) {
				printf ("5: No se ha podido reservar memoria suficiente\n");
				getchar ();
				exit (1);
			}
		}
	}	
	
	j.num_total_bar = 0;
	
	for (i = 0; i < j.num_tipo_bar; i++) {
		j.num_total_bar += j.num_bar_tipo[i];
	}
	
	//PROCESO PARA RELLENAR LA ESTRUCTURA DE JUEGO//
	if (fgets (cad_linea, sizeof(cad_linea), f_jue)) {
		campo_juego = sscanf (cad_linea, "%d-%d-%d",
		&j.tam_tablero,
		&j.num_total_bar,
		&j.num_tipo_bar);
		
		if (campo_juego != 3) {							//Excepción si fallo en dato de juego
			printf ("1: Se produjo un error con los datos\n");
			getchar ();
			exit (EXIT_FAILURE);
		}	
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_jue) && i < j.num_tipo_bar) {
		campo_juego = sscanf (cad_linea, "%c-%d",
		&b.bar[i].id_barco,
		&j.num_bar_tipo[i]);
		
		if (campo_juego != 2) {
			printf ("2: Se produjo un error con los datos\n");
			getchar ();
			exit (EXIT_FAILURE);
		}
		
		i++;
	}
	
	for (i = 0; i < 2; i++) {
		if (fgets (cad_linea, sizeof(cad_linea), f_jue)) {
			campo_juego = sscanf (cad_linea, "%d-%21[^-]-%d-%c-%d",
			&jv.jug[i].id_jug,
			jv.jug[i].nomb_jug,
			&jv.jug[i].num_disp,
			&jv.jug[i].tipo_disp,
			&jv.jug[i].ganador);
			
			if (campo_juego != 5 || !validar_nombre (jv.jug[i].nomb_jug)) {
				printf ("Error en los datos del jugador %d\n", i + 1);
				liberar_tableros (&jv, j.tam_tablero);
				liberar_juego (&j);
				fclose (f_jue);
				return j;
			}	
		}
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			fgets (cad_linea, sizeof(cad_linea), f_jue);	//Leer línea del tablero1
			for (colum = 0; colum < j.tam_tablero; colum++) {
				jv.jug[i].tablero1[fila][colum] = cad_linea[colum * 2];
				campo_juego = sscanf (cad_linea, "%c", &jv.jug[i].tablero1[fila][colum]);
			}
		}
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			fgets (cad_linea, sizeof(cad_linea), f_jue);	//Leer línea del tablero2
			for (colum = 0; colum < j.tam_tablero; colum++) {
				jv.jug[i].tablero2[fila][colum] = '~';
				campo_juego = sscanf (cad_linea, "%c", &jv.jug[i].tablero2[fila][colum]);
			}
		}
	}
	
	fclose (f_jue);
	
	return j;
}

void guardar_datajuego (juego j, bar_vect b, jug_vect jv) {
	int i, fila, colum;
	
	FILE *f_jue;
	char filename[] = "Juego.txt";
	f_jue = fopen (filename, "w");
	
	if (f_jue == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DEL JUEGO EN FICHERO//
	fprintf (f_jue, "%02d-%02d-%d\n",
	j.tam_tablero,
	j.num_total_bar,
	j.num_tipo_bar);
	
	for (i = 0; i < j.num_tipo_bar; i++) {
		fprintf (f_jue, "%c-%02d\n",
		b.bar[i].id_barco,
		j.num_bar_tipo[i]);
	}
	
	for (i = 0; i < 2; i++) {
		fprintf (f_jue, "%d-%s-%03d-%c-%d\n",
		jv.jug[i].id_jug,
		jv.jug[i].nomb_jug,
		jv.jug[i].num_disp,
		jv.jug[i].tipo_disp,
		jv.jug[i].ganador);
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			for (colum = 0; colum < j.tam_tablero; colum++) {
				fprintf (f_jue, "%c", jv.jug[i].tablero1[fila][colum]);
			}
		}
		
		for (fila = 0; fila < j.tam_tablero; fila++) {
			for (colum = 0; colum < j.tam_tablero; colum++) {
				fprintf (f_jue, "%c", jv.jug[i].tablero2[fila][colum]);
			}
		}
	}
	
	fclose (f_jue);
}

//MENÚS:
void menu_principal() {
	int op;
	char resp;
	
	do {
		do {
			titulo();
			printf("\nQue desea hacer?\n\n");
			Sleep(1000);
			printf("1. Ir al menu de configuracion\n");
			printf("2. Jugar una partida\n");
			printf("3. Salir del juego\n");
			scanf("%d", &op);
			fflush(stdin);
		} while (op < 1 || op > 3);
		
		switch (op) {
			case 1:
				//TODO: Implementar menú de configuración
				break;
			
			case 2:
				//TODO: Implementar juego
				break;
			
			case 3:
				break;
			
			default:
				break;
		}
		
		if (op != 3) {
			printf("\nDesea hacer algo mas? (S/N): ");
			scanf("%c", &resp);
			confirmacion(&resp);
			clear();
		}
	} while (resp == 'S' || resp == 's');
}




