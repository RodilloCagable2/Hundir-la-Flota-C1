#include "MenuP.h"
#include "complementos.h"

//BARCOS:
bar_vect cargar_barcos () {
	char filename[] = "Barcos.txt";
	int num_bar = 0;						//Número de barcos registrados
	int i = 0;
	char cad_linea[250];					//Caracteres máximos que puede ocupar una linea en fichero
	int campo_barcos;						//Entero que verifica nº campos de la estructura barcos
	char default_bar[] = "Defaultname-D-0";	//Creación de un barco estandar que ocupará la posición 0 del fichero
	
	FILE *f_bar;
	
	f_bar = fopen (filename, "r");
	
	if (f_bar == NULL) {
		f_bar = fopen (filename, "w");		//Excepción si no encuentra fichero
		fclose (f_bar);
		printf ("No se pudo abrir el archivo de barcos. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_bar);							//Necesario para volver a leer el fichero
	
	if (fgetc(f_bar) == EOF) {				//Si fichero vacío, añadimos barco predeterminado
		f_bar = fopen (filename, "w");
		fprintf (f_bar, default_bar);
		fclose (f_bar);
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_bar)) {	//Contador de barcos en el programa a partir de fichero
		num_bar++;
	}
	
	rewind (f_bar);
	
	bar_vect b;
	
	b.num_bar = num_bar;
	
	b.bar = (barcos*)malloc(b.num_bar*sizeof(barcos));		//Asignación de memoria dinámica "b.bar[num_bar]"
	
	if (b.bar == NULL) {
		printf ("No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
	
	//BUCLE PARA RELLENAR LA ESTRUCTURA DE BARCOS//
	while (fgets (cad_linea, sizeof(cad_linea), f_bar) && i < num_bar) {
		campo_barcos = sscanf (cad_linea, "%21[^-]-%2[^-]-%d",
		b.bar[i].nomb_barco,
		b.bar[i].id_barco,
		&b.bar[i].tam_barco);
		
		if (campo_barcos != 3) {							//Excepción si fallo en dato de barco
			printf ("Se produjo un error con los datos de un barco. ID_barco: %d\n", i + 1);
			getchar ();
			exit (EXIT_FAILURE);
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
	for (i = 0; i < b.num_bar; i++) {
		fprintf (f_bar, "%s-%s-%d\n",
		b.bar[i].nomb_barco,
		b.bar[i].id_barco,
		b.bar[i].tam_barco);
	}
	
	fclose (f_bar);
}

//JUGADORES:
jug_vect cargar_jugadores () {
	char filename[] = "Jugadores.txt";
	int num_jug = 0;								//Número de jugadores registrados
	int i = 0;
	char cad_linea[250];							//Caracteres máximos que puede ocupar una linea en fichero
	int campo_jugadores;							//Entero que verifica nº campos de la estructura jugadores
	char default_jug[] = "0-defaultname-A-000-0";	//Creación de un jugador estandar que ocupará la posición 0 del fichero
	
	FILE *f_jug;
	
	f_jug = fopen (filename, "r");
	
	if (f_jug == NULL) {
		f_jug = fopen (filename, "w");				//Excepción si no encuentra fichero
		fclose (f_jug);
		printf ("No se pudo abrir el archivo de jugadores. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_jug);									//Necesario para volver a leer el fichero
	
	if (fgetc(f_jug) == EOF) {						//Si fichero vacío, añadimos jugador predeterminado
		f_jug = fopen (filename, "w");
		fprintf (f_jug, default_jug);
		fclose (f_jug);
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_jug)) {		//Contador de jugadores en el programa a partir de fichero
		num_jug++;
	}
	
	rewind (f_jug);
	
	jug_vect j;
	
	j.num_jug = num_jug;
	
	j.jug = (jugadores*)malloc(j.num_jug*sizeof(jugadores));	//Asignación de memoria dinámica "j.jug[num_jug]"
	
	if (j.jug == NULL) {
		printf ("No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
	
	//BUCLE PARA RELLENAR LA ESTRUCTURA DE JUGADORES//
	while (fgets (cad_linea, sizeof(cad_linea), f_jug) && i < num_jug) {
		campo_jugadores = sscanf (cad_linea, "%d-%21[^-]-%2[^-]-%d-%d",
		&j.jug[i].id_jugador,
		j.jug[i].nomb_jugador,
		j.jug[i].tipo_disp,
		&j.jug[i].num_disp,
		&j.jug[i].ganador);
		
		if (campo_jugadores != 5) {								//Excepción si fallo en dato de jugador			
			printf ("Se produjo un error con los datos de un jugador. ID_jugador: %d\n", i + 1);
			getchar ();
			exit (EXIT_FAILURE);
		}
		
		i++;
	}
	
	fclose (f_jug);
	
	return j;
}

void guardar_jugadores (jug_vect j) {
	int i;
	
	FILE *f_jug;
	char filename[] = "Jugadores.txt";
	f_jug = fopen (filename, "w");
	
	if (f_jug == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DE CADA JUGADOR EN FICHERO//
	for (i = 0; i < j.num_jug; i++) {
		fprintf (f_jug, "%d-%s-%s-%03d-%d\n",
		j.jug[i].id_jugador,
		j.jug[i].nomb_jugador,
		j.jug[i].tipo_disp,
		j.jug[i].num_disp,
		j.jug[i].ganador);
	}
	
	fclose (f_jug);
}






