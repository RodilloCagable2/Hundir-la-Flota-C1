#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_NOMBRE 20
#define MAX_TABLERO 25

typedef struct {
    char id;
    int cantidad;
} Barco;

typedef struct {
    int indice;
    char nombre[MAX_NOMBRE];
    int disparos;
    char tipo;
    int ganador;
    char tablero[MAX_TABLERO][MAX_TABLERO];
    char tablero2[MAX_TABLERO][MAX_TABLERO];
} Jugador;

void leer_tablero(int *tam_vector, int *num_barcos, int *tam_lista_barcos, Jugador jugadores[], Barco barcos[]) {
    FILE *fich;
    int i, j, fila, col, sumatorio = 0;
    char buffer[100];

    if ((fich = fopen("juego.txt", "r")) == NULL) {
        printf("Error abriendo el fichero juego.txt\n");
        return;
    }

    // Leer configuración
    fscanf(fich, "%d-%d-%d\n", tam_vector, num_barcos, tam_lista_barcos);
    printf("Tamaño vector: %d, Número de barcos: %d, Tamaño lista barcos: %d\n", *tam_vector, *num_barcos, *tam_lista_barcos);

    // Leer los barcos
    i = 0;
    while (sumatorio < *num_barcos) {
        fscanf(fich, "%c-%i\n", &barcos[i].id, &barcos[i].cantidad);
        sumatorio += barcos[i].cantidad;
        i++;
    }

    // Leer jugadores
    for (j = 0; j < 2; j++) {
        fgets(buffer, sizeof(buffer), fich);
        sscanf(buffer, "%d-%19[^-]-%d-%c-%d",
               &jugadores[j].indice,
               jugadores[j].nombre,
               &jugadores[j].disparos,
               &jugadores[j].tipo,
               &jugadores[j].ganador);

        // Leer tableros
        for (fila = 0; fila < *tam_vector; fila++) {
            fgets(buffer, sizeof(buffer), fich);
            for (col = 0; col < *tam_vector; col++) {
                jugadores[j].tablero[fila][col] = buffer[col * 2];
                jugadores[j].tablero2[fila][col] = '~'; // Inicializar tablero de disparos con agua
            }
        }
    }

    fclose(fich);
}

void imprimirtablero(int cursorX, int cursorY, int turno, Jugador jugadores[], int tam_vector) {
    system("cls"); // Limpia pantalla en Windows

    char caracter = 'A';
    printf("  "); // Espacio para la primera columna numérica
    for (int i = 0; i < tam_vector; i++) {
        printf(" %c ", caracter + i);
    }
    printf("\n");

    for (int i = 0; i < tam_vector; i++) {
        printf("%d ", i);
        for (int j = 0; j < tam_vector; j++) {
            if (i == cursorY && j == cursorX)
                printf("[%c]", jugadores[turno].tablero2[i][j]);
            else
                printf(" %c ", jugadores[turno].tablero2[i][j]);
        }
        printf("\n");
    }
}

void apuntar(int *cursorX, int *cursorY, int turno, Jugador jugadores[], int tam_vector) {
    char input;
    while (1) {
        imprimirtablero(*cursorX, *cursorY, turno, jugadores, tam_vector);
        input = getch();
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            moverCursor(input, cursorX, cursorY, tam_vector);
        } else if (input == ' ') { // Espacio para disparar
            if (jugadores[turno].tablero[*cursorY][*cursorX] == 'X') {
                printf("¡Impacto!\n");
                jugadores[turno].tablero2[*cursorY][*cursorX] = 'X'; // Marcar impacto en tablero de disparos
            } else {
                printf("¡Fallaste!\n");
                jugadores[turno].tablero2[*cursorY][*cursorX] = 'O'; // Marcar fallo en tablero de disparos
            }

        }
    }
}

void moverCursor(char direction, int *cursorX, int *cursorY, int tam_vector) {
    if (direction == 'w' && *cursorY > 0) (*cursorY)--;
    if (direction == 's' && *cursorY < tam_vector - 1) (*cursorY)++;
    if (direction == 'a' && *cursorX > 0) (*cursorX)--;
    if (direction == 'd' && *cursorX < tam_vector - 1) (*cursorX)++;
}

int main() {
    int cursorX = 0, cursorY = 0, turno = 0;
    int tam_vector = 0, num_barcos = 0, tam_lista_barcos = 0;

    Barco barcos[10];
    Jugador jugadores[2];

    leer_tablero(&tam_vector, &num_barcos, &tam_lista_barcos, jugadores, barcos);
    apuntar(&cursorX, &cursorY, turno, jugadores, tam_vector);

    return 0;
}
