#include "complementos.h"

void clear () {
	system ("cls");
}

void titulo () {
	
}

void terminador_cad (char cad[]) {
	int i, len = strlen(cad);
	
	for (i = 0; i < len; i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
			len = i;	//SE ACABA EL BUCLE SI CAMBIA EL SALTO DE LINEA POR TERMINADOR
		}
	}
}

char confirmacion () {
	char resp = '0';
	
	fflush(stdin);
	scanf ("%c", &resp);
	fflush(stdin);
	
	while (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n') {
		printf ("Seleccione una opcion valida: ");
		scanf ("%c", &resp);
		fflush(stdin);
	}
	
	return resp;
}

int input_int () {
	int verif_int, num;
	
	fflush(stdin);
	
	do{
		verif_int = scanf ("%d", &num);
		
		fflush(stdin);
		
		if (verif_int != 1) {
			printf ("Introduzca un numero entero: ");
		}
	}while (verif_int != 1);
	
	return num;
}