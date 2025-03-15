#include "MenuP.h"
#include "complementos.h"

//BARCOS:
bar_vect cargar_barcos () {
	char filename[] = "Barcos.txt";
	int num_tipo_bar = 0;					//Número de tipos de barcos registrados
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
	for (i = 0; i < b.num_tipo_bar; i++) {
		fprintf (f_bar, "%s-%s-%d\n",
		b.bar[i].nomb_barco,
		b.bar[i].id_barco,
		b.bar[i].tam_barco);
	}
	
	fclose (f_bar);
}

//JUGADORES:
juego cargar_datajuego () {
	char filename[] = "Juego.txt";
	char cad_linea[250];							//Caracteres máximos que puede ocupar una linea en fichero
	char default_jue[] = "0-0-0\nA-0\n\n0-Defaultname-0-A-0\n---\n---\n---\n\n---\n---\n---\n\n0-Defaultname-0-A-0\n---\n---\n---\n\n---\n---\n---";	//Creación de un juego estandar
	
	FILE *f_jue;
	
	f_jue = fopen (filename, "r");
	
	if (f_jue == NULL) {
		f_jue = fopen (filename, "w");				//Excepción si no encuentra fichero
		fclose (f_jue);
		printf ("No se pudo abrir el archivo de juego. Se ha creado un nuevo archivo\n");
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
	
	//BUCLE PARA RELLENAR LA ESTRUCTURA DE JUGADORES//
	while (fgets (cad_linea, sizeof(cad_linea), f_jue)) {
		
	}
	
	fclose (f_jue);
	
	return j;
}

void guardar_datajuego (juego j) {
	int i;
	
	FILE *f_jue;
	char filename[] = "Juego.txt";
	f_jue = fopen (filename, "w");
	
	if (f_jue == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS EN FICHERO//
	
	
	fclose (f_jue);
}



