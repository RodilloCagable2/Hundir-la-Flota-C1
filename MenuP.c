#include "MenuP.h"
#include "Complementos.h"
#include "Configuracion.h"
#include "IntDatos.h"
#include "disparar.h"

//GESTIÓN DE MEMORIA:
void liberar_tableros(jug_vect *jv, int tam_tablero) {
	int i, fila;

	if (jv == NULL) {
		return;
	}

	for (i = 0; i < 2; i++) {
		if (jv->jug[i].tablero1 != NULL) {
			for (fila = 0; fila < tam_tablero; fila++) {
				free(jv->jug[i].tablero1[fila]);
			}
			free(jv->jug[i].tablero1);
		}

		if (jv->jug[i].tablero2 != NULL) {
			for (fila = 0; fila < tam_tablero; fila++) {
				free(jv->jug[i].tablero2[fila]);
			}
			free(jv->jug[i].tablero2);
		}
	}
}

void liberar_barcos(bar_vect *b) {
	if (b != NULL && b->bar != NULL) {
		free(b->bar);
		b->bar = NULL;
	}
}

void liberar_juego(juego *j) {
	if (j != NULL && j->num_bar_tipo != NULL) {
		free(j->num_bar_tipo);
		j->num_bar_tipo = NULL;
	}
}

//VALIDACIÓN:
int validar_nombre(const char *nombre) {
	if (nombre == NULL || strlen(nombre) == 0 || strlen(nombre) > 20) {
		return 0;
	}
	return 1;
}

int validar_id_barco(char id) {
	return (id >= 'A' && id <= 'Z');
}

int validar_tam_barco(int tam) {
	return (tam > 0 && tam <= 5);
}

//BARCOS:
int cargar_barcos(bar_vect *b) {
	char filename[] = "Barcos.txt";
	int num_tipo_bar = 0;
	int i = 0;
	char cad_linea[250];
	int campo_barcos = 0;
	char default_bar[] = "Defaultname-D-1";

	FILE *f_bar = fopen(filename, "r");

	if (f_bar == NULL) {
		f_bar = fopen(filename, "w");
		if (f_bar == NULL) {
			perror("Error al crear el archivo de barcos");
			return -1;
		}
		fprintf(f_bar, "%s\n", default_bar);
		fclose(f_bar);
		f_bar = fopen(filename, "r");
		if (f_bar == NULL) {
			perror("Error al abrir el archivo de barcos");
			return -1;
		}
	}

	// Verificar si el archivo está vacío
	if (fgetc(f_bar) == EOF) {
		fclose(f_bar);
		f_bar = fopen(filename, "w");
		if (f_bar == NULL) {
			perror("Error al abrir el archivo de barcos");
			return -1;
		}
		fprintf(f_bar, "%s\n", default_bar);
		fclose(f_bar);
		f_bar = fopen(filename, "r");
		if (f_bar == NULL) {
			perror("Error al abrir el archivo de barcos");
			return -1;
		}
	} else {
		rewind(f_bar);
	}

	// Contar número de barcos
	while (fgets(cad_linea, sizeof(cad_linea), f_bar)) {
		num_tipo_bar++;
	}

	rewind(f_bar);

	b->num_tipo_bar = num_tipo_bar;
	b->bar = (barcos*)malloc(b->num_tipo_bar * sizeof(barcos));

	if (b->bar == NULL) {
		perror("Error al asignar memoria para barcos");
		fclose(f_bar);
		return -1;
	}

	// Cargar datos de los barcos
	while (fgets(cad_linea, sizeof(cad_linea), f_bar) && i < num_tipo_bar) {
		campo_barcos = sscanf(cad_linea, "%21[^-]-%c-%d",
			b->bar[i].nomb_barco,
			&b->bar[i].id_barco,
			&b->bar[i].tam_barco);

		if (campo_barcos != 3 ||
			!validar_nombre(b->bar[i].nomb_barco) ||
			!validar_id_barco(b->bar[i].id_barco) ||
			!validar_tam_barco(b->bar[i].tam_barco)) {
			printf("Error en los datos del barco %d\n", i + 1);
			liberar_barcos(b);
			fclose(f_bar);
			return -1;
		}

		i++;
	}

	fclose(f_bar);
	return 0;
}

int guardar_barcos(bar_vect *b) {
	int i;
	FILE *f_bar;
	char filename[] = "Barcos.txt";

	f_bar = fopen(filename, "w");
	if (f_bar == NULL) {
		perror("Error al abrir el archivo de barcos");
		return -1;
	}

	for (i = 0; i < b->num_tipo_bar; i++) {
		if (fprintf(f_bar, "%s-%c-%d\n",
			b->bar[i].nomb_barco,
			b->bar[i].id_barco,
			b->bar[i].tam_barco) < 0) {
			perror("Error al escribir en el archivo de barcos");
			fclose(f_bar);
			return -1;
		}
	}

	fclose(f_bar);
	return 0;
}

//JUEGO:
int cargar_datajuego(juego *j, bar_vect *b, jug_vect *jv) {
    FILE *f_jue = NULL;
    char filename[] = "Juego.txt";
    char cad_linea[250];
    char default_jue[] = "03-01-1\nS-01\n1-Defaultname1-000-M-0\n~X~\n~~~\n~~~\n~~~\n~~~\n~~~\n2-Defaultname2-000-A-0\n~X~\n~~~\n~~~\n~~~\n~~~\n~~~";
    int i, fila, colum, campo_juego, len_linea;

    // Intentar abrir el archivo
    f_jue = fopen(filename, "r");

    if (f_jue == NULL) {
        // Crear archivo con contenido por defecto
        f_jue = fopen(filename, "w");
        if (f_jue == NULL) {
            perror("Error al crear el archivo de juego");
            return -1;
        }
        fprintf(f_jue, "%s\n", default_jue);
        fclose(f_jue);
        f_jue = fopen(filename, "r");
        if (f_jue == NULL) {
            perror("Error al abrir el archivo de juego");
            return -1;
        }
    }

    // Verificar si el archivo está vacío
    if (fgetc(f_jue) == EOF) {
        fclose(f_jue);
        f_jue = fopen(filename, "w");
        if (f_jue == NULL) {
            perror("Error al crear el archivo de juego");
            return -1;
        }
        fprintf(f_jue, "%s\n", default_jue);
        fclose(f_jue);
        f_jue = fopen(filename, "r");
        if (f_jue == NULL) {
            perror("Error al abrir el archivo de juego");
            return -1;
        }
    } else {
        rewind(f_jue);
    }

    // Leer cabecera del juego
    if (fgets(cad_linea, sizeof(cad_linea), f_jue)) {
        campo_juego = sscanf(cad_linea, "%d-%d-%d", &j->tam_tablero, &j->num_total_bar, &j->num_tipo_bar);
        if (campo_juego != 3 || j->tam_tablero <= 0) {
            printf("Error en el formato o tamaño inválido en los datos del juego\n");
            fclose(f_jue);
            return -1;
        }
    }

    // Asignar memoria para cantidad de barcos
    j->num_bar_tipo = (int*)malloc(j->num_tipo_bar * sizeof(int));
    if (j->num_bar_tipo == NULL) {
        perror("Error al asignar memoria para num_bar_tipo");
        fclose(f_jue);
        return -1;
    }

    // Cargar información de tipos de barcos
    for (i = 0; i < j->num_tipo_bar; i++) {
        if (!fgets(cad_linea, sizeof(cad_linea), f_jue)) {
            printf("Error: Datos de barcos incompletos\n");
            liberar_juego(j);
            fclose(f_jue);
            return -1;
        }
        campo_juego = sscanf(cad_linea, "%c-%d", &b->bar[i].id_barco, &j->num_bar_tipo[i]);
        if (campo_juego != 2) {
            printf("Error en el formato de los datos de los barcos\n");
            liberar_juego(j);
            fclose(f_jue);
            return -1;
        }
    }

    // Reservar memoria para tableros de los jugadores
    for (i = 0; i < 2; i++) {
        jv->jug[i].tablero1 = (char**)malloc(j->tam_tablero * sizeof(char*));
        jv->jug[i].tablero2 = (char**)malloc(j->tam_tablero * sizeof(char*));

        if (jv->jug[i].tablero1 == NULL || jv->jug[i].tablero2 == NULL) {
            perror("Error al asignar memoria para tableros");
            liberar_tableros(jv, j->tam_tablero);
            liberar_juego(j);
            fclose(f_jue);
            return -1;
        }

        for (fila = 0; fila < j->tam_tablero; fila++) {
            jv->jug[i].tablero1[fila] = (char*)malloc(j->tam_tablero * sizeof(char));
            jv->jug[i].tablero2[fila] = (char*)malloc(j->tam_tablero * sizeof(char));
            if (jv->jug[i].tablero1[fila] == NULL || jv->jug[i].tablero2[fila] == NULL) {
                perror("Error al asignar memoria para filas de tableros");
                liberar_tableros(jv, j->tam_tablero);
                liberar_juego(j);
                fclose(f_jue);
                return -1;
            }
        }
    }

    // Cargar información de los jugadores
    for (i = 0; i < 2; i++) {
        if (!fgets(cad_linea, sizeof(cad_linea), f_jue)) {
            printf("Error: Datos de jugador %d incompletos\n", i + 1);
            liberar_tableros(jv, j->tam_tablero);
            liberar_juego(j);
            fclose(f_jue);
            return -1;
        }
        campo_juego = sscanf(cad_linea, "%d-%21[^-]-%d-%c-%d",
            &jv->jug[i].id_jug,
            jv->jug[i].nomb_jug,
            &jv->jug[i].num_disp,
            &jv->jug[i].tipo_disp,
            &jv->jug[i].ganador);

        if (campo_juego != 5 || !validar_nombre(jv->jug[i].nomb_jug)) {
            printf("Error en los datos del jugador %d\n", i + 1);
            liberar_tableros(jv, j->tam_tablero);
            liberar_juego(j);
            fclose(f_jue);
            return -1;
        }

        // Cargar tablero1
        for (fila = 0; fila < j->tam_tablero; fila++) {
            if (!fgets(cad_linea, sizeof(cad_linea), f_jue)) {
                printf("Error: Datos incompletos en tablero1 del jugador %d\n", i + 1);
                liberar_tableros(jv, j->tam_tablero);
                liberar_juego(j);
                fclose(f_jue);
                return -1;
            }
            len_linea = strlen(cad_linea);
            if (len_linea < j->tam_tablero) {
                printf("Error: Línea de tablero1 muy corta para el jugador %d\n", i + 1);
                liberar_tableros(jv, j->tam_tablero);
                liberar_juego(j);
                fclose(f_jue);
                return -1;
            }
            for (colum = 0; colum < j->tam_tablero; colum++) {
                jv->jug[i].tablero1[fila][colum] = cad_linea[colum];
            }
        }

        // Cargar tablero2
        for (fila = 0; fila < j->tam_tablero; fila++) {
            if (!fgets(cad_linea, sizeof(cad_linea), f_jue)) {
                printf("Error: Datos incompletos en tablero2 del jugador %d\n", i + 1);
                liberar_tableros(jv, j->tam_tablero);
                liberar_juego(j);
                fclose(f_jue);
                return -1;
            }
            len_linea = strlen(cad_linea);
            if (len_linea < j->tam_tablero) {
                printf("Error: Línea de tablero2 muy corta para el jugador %d\n", i + 1);
                liberar_tableros(jv, j->tam_tablero);
                liberar_juego(j);
                fclose(f_jue);
                return -1;
            }
            for (colum = 0; colum < j->tam_tablero; colum++) {
                jv->jug[i].tablero2[fila][colum] = cad_linea[colum];
            }
        }
    }

    fclose(f_jue);
    return 0;
}

int guardar_datajuego(juego *j, bar_vect *b, jug_vect *jv) {
    FILE *f_jue = NULL;
    char filename[] = "Juego.txt";
    int i, fila, colum;

    // Abrir archivo en modo escritura
    f_jue = fopen(filename, "w");
    if (f_jue == NULL) {
        perror("Error al abrir el archivo de juego");
        return -1;
    }

    // Guardar datos generales del juego
    if (fprintf(f_jue, "%02d-%02d-%d\n", j->tam_tablero, j->num_total_bar, j->num_tipo_bar) < 0) {
        perror("Error al escribir datos generales del juego");
        fclose(f_jue);
        return -1;
    }

    // Guardar datos de los tipos de barcos
    for (i = 0; i < j->num_tipo_bar; i++) {
        if (fprintf(f_jue, "%c-%02d\n", b->bar[i].id_barco, j->num_bar_tipo[i]) < 0) {
            perror("Error al escribir datos de barcos");
            fclose(f_jue);
            return -1;
        }
    }

    // Guardar datos de los jugadores
    for (i = 0; i < 2; i++) {
        if (fprintf(f_jue, "%d-%s-%03d-%c-%d\n",
            jv->jug[i].id_jug,
            jv->jug[i].nomb_jug,
            jv->jug[i].num_disp,
            jv->jug[i].tipo_disp,
            jv->jug[i].ganador) < 0) {
            perror("Error al escribir datos de jugadores");
            fclose(f_jue);
            return -1;
        }

        // Guardar tablero1 del jugador
        for (fila = 0; fila < j->tam_tablero; fila++) {
            for (colum = 0; colum < j->tam_tablero; colum++) {
                if (fprintf(f_jue, "%c", jv->jug[i].tablero1[fila][colum]) < 0) {
                    perror("Error al escribir tablero1");
                    fclose(f_jue);
                    return -1;
                }
            }
            if (fprintf(f_jue, "\n") < 0) {
                perror("Error al escribir salto de línea en tablero1");
                fclose(f_jue);
                return -1;
            }
        }

        // Guardar tablero2 del jugador
        for (fila = 0; fila < j->tam_tablero; fila++) {
            for (colum = 0; colum < j->tam_tablero; colum++) {
                if (fprintf(f_jue, "%c", jv->jug[i].tablero2[fila][colum]) < 0) {
                    perror("Error al escribir tablero2");
                    fclose(f_jue);
                    return -1;
                }
            }
            if (fprintf(f_jue, "\n") < 0) {
                perror("Error al escribir salto de línea en tablero2");
                fclose(f_jue);
                return -1;
            }
        }
    }

    // Cerrar archivo
    fclose(f_jue);
    return 0;
}

//FUNCIONES VARIAS:
void resumen_partida() {

}

int cambiar_tam_tablero(juego *j, bar_vect *b, jug_vect *jv) {
    int i, fila, colum, nuevo_tam;
    char resp;
    char *nueva_fila = NULL;
    char **nuevo_tablero1 = NULL;
    char **nuevo_tablero2 = NULL;
    
    clear();

    printf("Las dimensiones actuales del tablero son: %dx%d", j->tam_tablero, j->tam_tablero);
    printf("\nDeseas actualizar el tamano del tablero? (S/N): ");
    scanf("%c", &resp);
    fflush(stdin);
    confirmacion(&resp);

    if (resp == 'S' || resp == 's') {
        printf("\n\nIntroduce el nuevo tamano del tablero (3-26): ");
        scanf("%d", &nuevo_tam);
        fflush(stdin);

        while (nuevo_tam < 3 || nuevo_tam > 26) {
            printf("\n\nEl tamano introducido no es valido, introduce un valor entre 3 y 26: ");
            scanf("%d", &nuevo_tam);
            fflush(stdin);
        }

        // Para cada jugador
        for (i = 0; i < 2; i++) {
            // Reasignar memoria para tablero1
            nuevo_tablero1 = (char**)realloc(jv->jug[i].tablero1, nuevo_tam * sizeof(char*));
            
            if (nuevo_tablero1 == NULL) {
                printf("\nError al reasignar memoria para el tablero1");
                return -1;
            }
            
            jv->jug[i].tablero1 = nuevo_tablero1;

            for (fila = 0; fila < nuevo_tam; fila++) {
                if (fila >= j->tam_tablero) {
                    // Nueva fila
                    jv->jug[i].tablero1[fila] = (char*)malloc(nuevo_tam * sizeof(char));
                    
                    if (jv->jug[i].tablero1[fila] == NULL) {
                        printf("\nError al asignar nueva fila en tablero1");
                        return -1;
                    }
                    
                    for (colum = 0; colum < nuevo_tam; colum++) {
                        jv->jug[i].tablero1[fila][colum] = '~';
                    }
                } 
				else {
                    // Fila existente, ampliar columnas
                    nueva_fila = (char*)realloc(jv->jug[i].tablero1[fila], nuevo_tam * sizeof(char));
                    
                    if (nueva_fila == NULL) {
                        printf("\nError al reasignar fila en tablero1");
                        return -1;
                    }
                    
                    jv->jug[i].tablero1[fila] = nueva_fila;
                    
                    for (colum = j->tam_tablero; colum < nuevo_tam; colum++) {
                        jv->jug[i].tablero1[fila][colum] = '~';
                    }
                }
            }

            // Reasignar memoria para tablero2
            nuevo_tablero2 = (char**)realloc(jv->jug[i].tablero2, nuevo_tam * sizeof(char*));
            
            if (nuevo_tablero2 == NULL) {
                printf("\nError al reasignar memoria para el tablero2");
                return -1;
            }
            
            jv->jug[i].tablero2 = nuevo_tablero2;

            for (fila = 0; fila < nuevo_tam; fila++) {
                if (fila >= j->tam_tablero) {
                    // Nueva fila
                    jv->jug[i].tablero2[fila] = (char*)malloc(nuevo_tam * sizeof(char));
                    
                    if (jv->jug[i].tablero2[fila] == NULL) {
                        printf("\nError al asignar nueva fila en tablero2");
                        return -1;
                    }
                    
                    for (colum = 0; colum < nuevo_tam; colum++) {
                        jv->jug[i].tablero2[fila][colum] = '~';
                    }
                } 
				else {
                    // Fila existente, ampliar columnas
                    nueva_fila = (char*)realloc(jv->jug[i].tablero2[fila], nuevo_tam * sizeof(char));
                    
                    if (nueva_fila == NULL) {
                        printf("\nError al reasignar fila en tablero2");
                        return -1;
                    }
                    
                    jv->jug[i].tablero2[fila] = nueva_fila;
                    
                    for (colum = j->tam_tablero; colum < nuevo_tam; colum++) {
                        jv->jug[i].tablero2[fila][colum] = '~';
                    }
                }
            }
        }

        // Actualizar tamaño del tablero
        j->tam_tablero = nuevo_tam;

        // Guardar cambios
        if (guardar_datajuego(j, b, jv) == -1) {
            return -1;
        }
    } 
	else {
        printf("\nVolviendo al menu principal...\n");
        Sleep(1000);

        if (menu_principal(j, b, jv) == -1) {
            return -1;
        }
    }

    return 0;
}


//MENÚS:
int menu_configuracion(juego *j, bar_vect *b, jug_vect *jv) {
	int op,op2;
	char resp;

	do {
		do {
			clear();
			printf("\n<<<CONFIGURACION>>>\n\n");
			Sleep(1000);
			printf("1. Introducir datos\n");
			printf("2. Mostrar\n");
			printf("3. Borrar\n");
			printf("4. Guardar\n");
			printf("5. Cargar\n");
			printf("6. Volver\n\n");
			scanf("%d", &op);
			fflush(stdin);
		} while (op < 1 || op > 6);

		switch (op) {
			case 1:
				//Función que contiende todas las funciones para la introducción de datos
				cambiar_tam_tablero(j, b, jv);
				//intro_dat(jv, j, b);
				break;

			case 2:
			    //Funciones que se encargan de mostrar lo almacenado en la configuración y/o barcos
				printf("Que desea ver? [1] Configuracion Global [2] Barcos [3] Ambas\n");
				//Bucle para asegurarse de que se seleccione una opción correcta
				do{
                    scanf("%i",&op2);
                    fflush(stdin);
				}while(op2 != 1 || op2 != 2 || op != 3);
				
				switch(op2){
				    case 1:
				        mostrar_config(jv, *j);
				        break;
                    case 2:
                        mostrar_barcos(b);
                        break;
                    case 3:
                        mostrar_config(jv, *j);
                        mostrar_barcos(b);
                        break;
				}
				break;

			case 3:
				//Función que borra los ficheros que el jugador desee
				Borrar();
				break;

			case 4:
				if (guardar_datajuego(j, b, jv) == -1) {
					return -1;
				}
				break;

			case 5:
				if (cargar_datajuego(j, b, jv) == -1) {
					return -1;
				}
				break;

			case 6:
				printf("\nVolviendo al menu principal...\n");
				Sleep(1000);

				if (menu_principal(j, b, jv) == -1) {
					return -1;
				}
				break;

			default:
				printf("Seleccione una opcion valida: ");
				break;
		}
		
		if (op != 6) {
			printf("\nDeseas hacer algo mas? (S/N): ");
			scanf("%c", &resp);
			fflush(stdin);
			confirmacion(&resp);
			clear();
		}
		if (resp == 'N' || resp == 'n') {
			printf("\nVolviendo al menu principal...\n");
			Sleep(1000);

			if (menu_principal(j, b, jv) == -1) {
				return -1;
			}
		}
	}while (op != 6 && (resp == 'S' || resp == 's'));

	return 0;
}

int menu_partida(juego *j, bar_vect *b, jug_vect *jv) {
	int op;
	char resp;

	do {
		do {
			clear();
			printf("\n<<<JUGAR PARTIDA>>>\n\n");
			Sleep(1000);
			printf("1. Jugar partida\n");
			printf("2. Reiniciar partida\n");
			printf("3. Resumen\n");
			printf("4. Volver\n\n");
			scanf("%d", &op);
			fflush(stdin);
		} while (op < 1 || op > 4);

		switch (op) {
			case 1:
				//TODO: Implementar juego
				break;

			case 2:
				//TODO: Implementar reinicio
				break;

			case 3:
				resumen_partida();
				break;

			case 4:
				printf("\nVolviendo al menu principal...\n");
				Sleep(1000);

				if (menu_principal(j, b, jv) == -1) {
					return -1;
				}
				break;

			default:
				printf("Seleccione una opcion valida: ");
				break;
		}

		if (op != 4) {
			printf("\nDeseas hacer algo mas? (S/N): ");
			scanf("%c", &resp);
			fflush(stdin);
			confirmacion(&resp);
			clear();
		}
		if (resp == 'N' || resp == 'n') {
			printf("\nVolviendo al menu principal...\n");
			Sleep(1000);

			if (menu_principal(j, b, jv) == -1) {
				return -1;
			}
		}
	}while (op != 4 && (resp == 'S' || resp == 's'));

	return 0;
}

int menu_principal(juego *j, bar_vect *b, jug_vect *jv) {
	int op;
	char resp;

	do {
		do {
			clear();
			titulo();
			printf("\n<<<HUNDIR LA FLOTA>>>\n\n");
			Sleep(1000);
			printf("1. Configuracion\n");
			printf("2. Jugar\n");
			printf("3. Salir\n\n");
			scanf("%d", &op);
			fflush(stdin);
		} while (op < 1 || op > 3);

		switch (op) {
			case 1:
				if (menu_configuracion(j, b, jv) == -1) {
					return -1;
				}
				break;

			case 2:
				if (menu_partida(j, b, jv) == -1) {
					return -1;
				}
				break;

			case 3:
				printf("\nHasta la proxima!\n");
				exit(1);
				break;

			default:
				printf("Seleccione una opcion valida: ");
				break;
		}

		if (op != 3) {
			printf("\nDesea hacer algo mas? (S/N): ");
			scanf("%c", &resp);
			fflush(stdin);
			confirmacion(&resp);
			clear();
		}
	}while (op != 3 && (resp == 'S' || resp == 's'));

	return 0;
}