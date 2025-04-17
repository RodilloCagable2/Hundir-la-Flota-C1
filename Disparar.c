#include "disparar.h"

#define MAX_NOMBRE 20
#define MAX_TABLERO 25

// Cabecera: int numeroAleatorio(int)
// Precondici?n: variables no nulas
// Postcondici?n: devuelve un n?mero aleatorio acotado al tama?o del tablero
int numeroAleatorio(int tam_vector) {
    return (rand() % tam_vector);
}

// Cabecera: void moverCursorConsola(int, int)
// Precondici?n: Se conoce la posici?n x e y de la matriz
// Postcondici?n: devuelve un n?mero aleatorio acotado al tama?o del tablero
void moverCursorConsola(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

// Cabecera imprimirtablero(int, int, int, Jugador, int)
// Precondici?n: Variables no nulas
// Postcondici?n: imprime el estado actual del tablero dependiendo del turno actual
void imprimirtablero(int cursorX, int cursorY, int turno, jug_vect jv, int tam_vector) {
    int i;
    char c;
    int j;

    moverCursorConsola(0, 0);  // En lugar de limpiar la pantalla, movemos el cursor arriba

    printf("                      ");
    for (c = 'A'; c < 'A' + tam_vector; c++)
        printf("  %c", c);
    printf("\n");

    for (i = 0; i < tam_vector; i++) {
        printf("                    %2d ", i);
        for (j = 0; j < tam_vector; j++) {
            if (i == cursorY && j == cursorX)
                printf("[%c]", jv.jug[turno].tablero2[i][j]);  // Resaltamos donde est? el cursor
            else
                printf(" %c ", jv.jug[turno].tablero2[i][j]);
        }
        printf("\n");
    }
    printf("disp: %i ganador: %i", jv.jug[turno].num_disp, jv.jug[turno].ganador);
}

// Cabecera: void moverCursor(char, int *, int *, int)
// Precondic??n: Se conoce la posici?n x e y de la matriz y el tama?o del vector
// Postcondici?n: Dependiendo de la tecla presionada modifica las variables cursores.
void moverCursor(char input, int *cursorX, int *cursorY, int tam_vector) {
    switch (input) {
        case 'w': if (*cursorY > 0) (*cursorY)--; break;
        case 's': if (*cursorY < tam_vector - 1) (*cursorY)++; break;
        case 'a': if (*cursorX > 0) (*cursorX)--; break;
        case 'd': if (*cursorX < tam_vector - 1) (*cursorX)++; break;
    }
}

// Cabecera: tocadoHundido(int, int, Jugador, int, int, int)
// Precondici?n: Variables no nula
// Postcondici?n: Devuelve la diferencia de las casillas tocadas por el jugador y la cantidad total de casillas que compone un barco
int tocadoHundido(int cursorX, int cursorY, jug_vect jv, int turno, int turnoOpuesto, int tamTablero) {
    int numAciertosMapa = 1; // El disparo original ya cuenta como acierto
    int numAciertosJugador =1; // De la misma forma el disparo del jugador tambien cuenta como acierto
    int aciertos = 0;
    int dx, dy; // Variables para manejar direcciones
    int x, y;

    // Recorremos las 8 direcciones sin necesidad de una matriz
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Evita la posici?n original

            x = cursorX + dx;
            y = cursorY + dy;
            if ((x >= 0) && (x < tamTablero) && (y >= 0) && (y < tamTablero) && (jv.jug[turnoOpuesto].tablero1[y][x] == 'X')) {
                numAciertosMapa++;
                if(jv.jug[turno].tablero2[y][x] == 'X'){
                        numAciertosJugador++;
                    }
                // Seguir avanzando en la misma direcci?n
                while ((x += dx) >= 0 && x < tamTablero &&
                       (y += dy) >= 0 && y < tamTablero &&
                       jv.jug[turnoOpuesto].tablero1[y][x] == 'X') {
                    if(jv.jug[turno].tablero2[y][x] == 'X'){
                        numAciertosJugador++;
                    }
                    numAciertosMapa++;
                }
            }
            if (aciertos >= 2) return numAciertosMapa; // Terminamos si ya hay dos aciertos
        }
    }
    return numAciertosMapa - numAciertosJugador; //devuelve la diferencia de barcos que han sido impactados para saber si un barco ha sido tocado o hundido
}

// Cabecera: actualizarHundido(int, int, Jugador, int, int, int, int [])
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica en el tablero del jugador dado las casillas tocadas por casillas hundidas
void actualizarHundido(int cursorX, int cursorY, jug_vect jv, int turno, int turnoOpuesto, int tamTablero, int barcosRestantes[]) {
    int dx, dy, x, y; // Variables para manejar direcciones

    // Recorremos las 8 direcciones sin necesidad de una matriz
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            x = cursorX + dx;
            y = cursorY + dy;
            if ((x >= 0) && (x < tamTablero) && (y >= 0) && (y < tamTablero) && (jv.jug[turnoOpuesto].tablero1[y][x] == 'X')) {
                // Seguir avanzando en la misma direcci?n
                jv.jug[turno].tablero2[y][x] = 'H';
                while ((x += dx) >= 0 && x < tamTablero &&
                       (y += dy) >= 0 && y < tamTablero &&
                       jv.jug[turno].tablero2[y][x] == 'X') {
                    jv.jug[turno].tablero2[y][x] = 'H';
                }
            }
        }
    }
    barcosRestantes[turno]--;
}

// Cabecera: apuntarJugador(int *, int *, Jugador, int, int *, int *, int [])
// Precondici?n: Variable no nulas
// Postcondici?n: Modifica el tablero del jugador cu?ndo se cumplen las condiciones
void apuntarJugador(int *cursorX, int *cursorY, jug_vect jv, int tam_vector, int *turno, int *turnoOpuesto, int barcosRestantes[]){
    int valTocado;
    char input;

    printf("\n\nBB%iBB\n\n", barcosRestantes[*turno]);
    imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
    input = getch();

    if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
        moverCursor(input, cursorX, cursorY, tam_vector);
    } else if ((input == ' ') && (jv.jug[*turno].tablero2[*cursorY][*cursorX] == '~')) { // Impide progresar si la casilla seleccionada ya ha sido revelada
        char *casilla = &jv.jug[*turnoOpuesto].tablero1[*cursorY][*cursorX];

        if (*casilla == 'X') {
            jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
            valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
            if(valTocado == 0) {
                actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
            }
            imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
        } else {
            jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'O';
            imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
            *turno = 1 - *turno;
            *turnoOpuesto = 1 - *turnoOpuesto;
        }
        jv.jug[*turno].num_disp++;
    }
}

// Cabecera: desplazarCpu(int *, int *, int *, int *, int, Jugador, int)
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica la posici?n de la Cpu paso a paso dada la posici?n final que deber? tomar dicho valor
void desplazarCpu(int *cursorX, int *cursorY, int *posX, int *posY, int turno, jug_vect jv, int tamTablero) {
    // Aseg?rate de que las coordenadas se modifican correctamente.
    while (*cursorX != *posX || *cursorY != *posY) {
        Sleep(50);
        if (*cursorX < *posX) {
            (*cursorX)++;
        } else if (*cursorX > *posX) {
            (*cursorX)--;
        } else if (*cursorY < *posY) {
            (*cursorY)++;
        } else if (*cursorY > *posY) {
            (*cursorY)--;
        }
        imprimirtablero(*cursorX, *cursorY, turno, jv, tamTablero);
    }
}

// Cabecera: apuntarCPU(int *, int *, int *, int *, int *, int *, Jugador, int, int *, int *, int *, int *, int [])
// Precondici?n: Variables no nulas
// Postcondici?n: Modifica el tablero de la Cpu
void apuntarCPU(int *cursorX, int *cursorY, int *posX, int *posY, int *auxX, int *auxY, jug_vect jv, int tam_vector,
                int *turno, int *turnoOpuesto, int *aciertoPrevioCpu, int *continuarDireccion, int barcosRestantes[]) {
    int valTocado;
    int i, j;
    int intento = 0; // Contador de intentos para evitar bucles infinitos
    printf("\n\nAA%iAA\n\n", barcosRestantes[*turno]);
    // Seleccionar una posici?n aleatoria v?lida para disparar si no se ha acertado previamente
    if (*aciertoPrevioCpu == 0) {
        do {
            *posY = numeroAleatorio(tam_vector);
            *posX = numeroAleatorio(tam_vector);
        } while (jv.jug[*turno].tablero2[*posY][*posX] != '~');

        desplazarCpu(cursorX, cursorY, posX, posY, *turno, jv, tam_vector);

        // Evaluar impacto del disparo
        char *casilla = &jv.jug[*turno].tablero1[*cursorY][*cursorX];
        char *casillaPropia = &jv.jug[*turno].tablero2[*cursorY][*cursorX];

        if (*casillaPropia != '~') { // Ya se dispar? aqu?
            intento++;
            if (intento > 10) return;
        }

        if (*casilla == 'X') {
            if (*aciertoPrevioCpu == 0) {
                *auxY = *cursorY;
                *auxX = *cursorX;
            }
            jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
            valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
            if (valTocado == 0) {
                actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
                *aciertoPrevioCpu = 0;
                *continuarDireccion = 0;
            } else {
                *aciertoPrevioCpu = 1;
                *continuarDireccion = 1;
            }
            imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
            Sleep(100);
        } else {
            jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'O';
            imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
            *turno = 1 - *turno;
            *turnoOpuesto = 1 - *turnoOpuesto;
            Sleep(800);
        }
        jv.jug[*turno].num_disp++;
    }
    else { // Si la CPU acert? antes
        desplazarCpu(cursorX, cursorY, auxX, auxY, *turno, jv, tam_vector);

        // Generar una direcci?n v?lida
        do {
            i = -1 + numeroAleatorio(3);
            j = -1 + numeroAleatorio(3);
        } while ((*cursorX + i < 0 || *cursorX + i >= tam_vector ||
                  *cursorY + j < 0 || *cursorY + j >= tam_vector ||
                  jv.jug[*turno].tablero2[*cursorY + j][*cursorX + i] != '~'));

        *posX = *cursorX + i;
        *posY = *cursorY + j;
        desplazarCpu(cursorX, cursorY, posX, posY, *turno, jv, tam_vector);

        if (jv.jug[*turnoOpuesto].tablero1[*cursorY][*cursorX] == 'X') {
            *continuarDireccion = 1;
            do {
                jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
                valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
                if (valTocado == 0) {
                    actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
                    *aciertoPrevioCpu = 0;
                    *continuarDireccion = 0;
                }
                // Asegurar que no se sale del tablero
                if (*cursorX + i >= 0 && *cursorX + i < tam_vector && *cursorY + j >= 0 && *cursorY + j < tam_vector) {
                    *posX = *cursorX + i;
                    *posY = *cursorY + j;
                    desplazarCpu(cursorX, cursorY, posX, posY, *turno, jv, tam_vector);
                } else {
                    break; // Si se sale, no continuar
                }
                imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
                Sleep(100);
                jv.jug[*turno].num_disp++;
            } while (jv.jug[*turnoOpuesto].tablero1[*cursorY][*cursorX] == 'X');
        } else {
            jv.jug[*turno].tablero2[*cursorY][*cursorX] = 'O';
            imprimirtablero(*cursorX, *cursorY, *turno, jv, tam_vector);
            *turno = 1 - *turno;
            *turnoOpuesto = 1 - *turnoOpuesto;
            Sleep(800);
        }
        jv.jug[*turno].num_disp++;
    }
}

// Cabecera: void disparar_jue(jug_vect, bar_vect)
// Precondici?n: Recibo los registros de jugadores y de barcos
// Postcondici?n: modifica la informaci?n de los jugadores
void disparar_jue(jug_vect jv, bar_vect bv, juego j) {
    srand(time(NULL));

    int cursorX[2] = {0, 0}, cursorY[2] = {0, 0}; // Cursores de cada jugador
    int posX[2], posY[2], auxX[2], auxY[2]; //Cursores para el funcionamiento de la Cpu
    int aciertoPrevioCpu[2] = {0,0}, continuarDireccion[2] = {0,0};
    int num_barcos, tam_lista_barcos, turno = 0, turnoOpuesto = 1;
    int barcosRestantes[2];

    while (1) {
        if (jv.jug[turno].tipo_disp == 'M') {
            apuntarJugador(&cursorX[turno], &cursorY[turno], jv, j.tam_tablero, &turno, &turnoOpuesto, barcosRestantes);
        } else {
            apuntarCPU(&cursorX[turno], &cursorY[turno], &posX[turno], &posY[turno], &auxX[turno], &auxY[turno], jv,
                       j.tam_tablero, &turno, &turnoOpuesto, &aciertoPrevioCpu[turno], &continuarDireccion[turno], barcosRestantes);
        }
    }
}

