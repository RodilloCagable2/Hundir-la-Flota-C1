#include "MenuP.h"
#include "disparar.h"

// Cabecera: int numeroAleatorio(int)
// Precondición: variables no nulas
// Postcondición: devuelve un número aleatorio acotado al tamaño del tablero
int numeroAleatorio(int tam_vector) {
    return (rand() % tam_vector);
}

// Cabecera: void moverCursorConsola(int, int)
// Precondición: Se conoce la posición x e y de la matriz
// Postcondición: devuelve un número aleatorio acotado al tamaño del tablero
void moverCursorConsola(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

// Cabecera imprimirtablero(int, int, int, int, Jugador, int)
// Precondición: Variables no nulas
// Postcondición: imprime el estado actual del tablero dependiendo del turno actual
void imprimirtablero(int cursorX, int cursorY, int turno, int turnoOpuesto, jug_vect *jv, int tam_vector) {
    int i;
    char c;

    if(turno == 0){
        moverCursorConsola(0, 0);  // En lugar de limpiar la pantalla, movemos el cursor arriba

        printf(" ");
        for (i = 0; i < tam_vector; i++)
            printf("  %i", i);
        printf("\n");

        c = 'A';
        for (i = 0; i < tam_vector; i++) {
            printf("%c ", c);
            for (int j = 0; j < tam_vector; j++) {
                if (i == cursorY && j == cursorX)
                    printf("[%c]", jv->jug[turno].tablero2[i][j]);  // Resaltamos donde está el cursor
                else
                    printf(" %c ", jv->jug[turno].tablero2[i][j]);
            }
            printf("\n");
            c++;
        }

        printf("\n");

        printf(" ");
        for (i = 0; i < tam_vector; i++)
            printf("  %i", i);
        printf("\n");

        c = 'A';
        for (i = 0; i < tam_vector; i++) {
            printf("%c ", c);
            for (int j = 0; j < tam_vector; j++) {
                printf(" %c ", jv->jug[turnoOpuesto].tablero2[i][j]);  // Resaltamos donde está el cursor
            }
            printf("\n");
            c++;
        }
        printf("\n");
    }
    else{
        moverCursorConsola(0, 0);  // En lugar de limpiar la pantalla, movemos el cursor arriba

        printf(" ");
        for (i = 0; i < tam_vector; i++)
            printf("  %i", i);
        printf("\n");

        c = 'A';
        for (i = 0; i < tam_vector; i++) {
            printf("%c ", c);
            for (int j = 0; j < tam_vector; j++) {
                printf(" %c ", jv->jug[turnoOpuesto].tablero2[i][j]);  // Resaltamos donde está el cursor
            }
            printf("\n");
            c++;
        }

        printf("\n");

        printf(" ");
        for (i = 0; i < tam_vector; i++)
            printf("  %i", i);
        printf("\n");

        c = 'A';
        for (i = 0; i < tam_vector; i++) {
            printf("%c ", c);
            for (int j = 0; j < tam_vector; j++) {
                if (i == cursorY && j == cursorX)
                    printf("[%c]", jv->jug[turno].tablero2[i][j]);  // Resaltamos donde está el cursor
                else
                    printf(" %c ", jv->jug[turno].tablero2[i][j]);
            }
            printf("\n");
            c++;
        }
        printf("\n");
    }
    if (jv->jug[turno].tipo_disp == 'M') {
        printf("[Presiona E para salir y guardar la partida]\n");
    }
}

// Cabecera: void moverCursor(char, int *, int *, int)
// Precondicíón: Se conoce la posición x e y de la matriz y el tamaño del vector
// Postcondición: Dependiendo de la tecla presionada modifica las variables cursores.
void moverCursor(char input, int *cursorX, int *cursorY, int tam_vector) {
    switch (input) {
        case 'w': if (*cursorY > 0) (*cursorY)--; break;
        case 's': if (*cursorY < tam_vector - 1) (*cursorY)++; break;
        case 'a': if (*cursorX > 0) (*cursorX)--; break;
        case 'd': if (*cursorX < tam_vector - 1) (*cursorX)++; break;
        case 'W': if (*cursorY > 0) (*cursorY)--; break;
        case 'S': if (*cursorY < tam_vector - 1) (*cursorY)++; break;
        case 'A': if (*cursorX > 0) (*cursorX)--; break;
        case 'D': if (*cursorX < tam_vector - 1) (*cursorX)++; break;
    }
}

// Cabecera: tocadoHundido(int, int, Jugador, int, int, int)
// Precondición: Variables no nula
// Postcondición: Devuelve la diferencia de las casillas tocadas por el jugador y la cantidad total de casillas que compone un barco
int tocadoHundido(int cursorX, int cursorY, jug_vect *jv, int turno, int turnoOpuesto, int tamTablero) {
    int numAciertosMapa = 1; // El disparo original ya cuenta como acierto
    int numAciertosJugador = 1; // De la misma forma el disparo del jugador tambien cuenta como acierto
    int aciertos = 0;
    int dx, dy; // Variables para manejar direcciones
    int x, y;

    // Recorremos las 8 direcciones sin necesidad de una matriz
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Evita la posición original

            x = cursorX + dx;
            y = cursorY + dy;
            if ((x >= 0) && (x < tamTablero) && (y >= 0) && (y < tamTablero) && (jv->jug[turnoOpuesto].tablero1[y][x] == 'X')) {
                numAciertosMapa++;
                if(jv->jug[turno].tablero2[y][x] == 'X'){
                        numAciertosJugador++;
                    }
                // Seguir avanzando en la misma dirección
                while ((x += dx) >= 0 && x < tamTablero &&
                       (y += dy) >= 0 && y < tamTablero &&
                       jv->jug[turnoOpuesto].tablero1[y][x] == 'X') {
                    if(jv->jug[turno].tablero2[y][x] == 'X'){
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
// Precondición: Variables no nulas
// Postcondición: Modifica en el tablero del jugador dado las casillas tocadas por casillas hundidas
void actualizarHundido(int cursorX, int cursorY, jug_vect *jv, int turno, int turnoOpuesto, int tamTablero, int barcosRestantes[]) {
    int dx, dy, x, y, x2, y2; // Variables para manejar direcciones

    // Recorremos las 8 direcciones sin necesidad de una matriz
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
            x = cursorX + dx;
            y = cursorY + dy;

            if ((x >= 0) && (x < tamTablero) && (y >= 0) && (y < tamTablero) && (jv->jug[turnoOpuesto].tablero1[y][x] == 'X')) {
                // Seguir avanzando en la misma dirección
                jv->jug[turno].tablero2[y][x] = 'H';
                for(x2 = -1; x2 <= 1; x2++){ // Cambia las casillas '~' adyascentes de X por O
                    	for(y2 = -1; y2 <= 1; y2++){
                    		if (((x2 + x) >= 0) && ((x2 + x) < tamTablero) && ((y2 + y) >= 0) && ((y2 + y) < tamTablero) &&
    							(jv->jug[turnoOpuesto].tablero1[y + y2][x + x2] == '~')) {
    							jv->jug[turno].tablero2[y + y2][x + x2] = '*';
							}
						}
					}
                while ((x += dx) >= 0 && x < tamTablero &&
                       (y += dy) >= 0 && y < tamTablero &&
                       jv->jug[turno].tablero2[y][x] == 'X') {
                    jv->jug[turno].tablero2[y][x] = 'H';
                    for(x2 = -1; x2 <= 1; x2++){ // // Cambia las casillas '~' adyascentes de X por O
                    	for(y2 = -1; y2 <= 1; y2++){
                    		if (((x2 + x) >= 0) && ((x2 + x) < tamTablero) && ((y2 + y) >= 0) && ((y2 + y) < tamTablero) &&
    							(jv->jug[turnoOpuesto].tablero1[y + y2][x + x2] == '~')) {
    							jv->jug[turno].tablero2[y + y2][x + x2] = '*';
							}
						}
					}
                }
            }
        }
    }
    barcosRestantes[turno]--;
}

// Cabecera: apuntarJugador(int *, int *, jug_vect *, juego *, bar_vect *, int, int *, int *, int [])
// Precondición: Variable no nulas
// Postcondición: Modifica el tablero del jugador cuándo se cumplen las condiciones
void apuntarJugador(int *cursorX, int *cursorY, jug_vect *jv, juego *j, bar_vect *bv, int tam_vector, int *turno, int *turnoOpuesto, int barcosRestantes[]){
    int valTocado;
    char input;

    imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
    input = getch();

    if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'W' || input == 'A' || input == 'S' || input == 'D' || input == 'e' || input == 'E') {
        if (input == 'e' || input == 'E') { // En caso de pulsar 'E' regresa al menú de inicio
            guardar_datajuego(j, bv, jv);
            system("cls");
            printf("Regresando al menu principal\n");
            system("PAUSE");
            if(menu_principal(j, bv, jv) == -1){
                return -1;
            }
        }
        moverCursor(input, cursorX, cursorY, tam_vector);
    } else if ((input == ' ') && (jv->jug[*turno].tablero2[*cursorY][*cursorX] == '~')) { // Impide progresar si la casilla seleccionada ya ha sido revelada
        char *casilla = &jv->jug[*turnoOpuesto].tablero1[*cursorY][*cursorX];

        if (*casilla == 'X') {
            jv->jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
            valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
            if(valTocado == 0) {
                actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);

                jv->jug[*turno].hundidos++;

                if (j->num_total_bar - jv->jug[*turno].hundidos == 0){ // Finaliza el juego después de que el jugador se quede sin barcos
                    jv->jug[*turno].ganador += 1;
                }
            }
            imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
        } else {
            jv->jug[*turno].tablero2[*cursorY][*cursorX] = '*';
            imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
            *turno = 1 - *turno;
            *turnoOpuesto = 1 - *turnoOpuesto;
        }
        jv->jug[*turno].num_disp++;
    }
}

// Cabecera: desplazarCpu(int *, int *, int *, int *, int, int, Jugador, int)
// Precondición: Variables no nulas
// Postcondición: Modifica la posición de la Cpu paso a paso dada la posición final que deberá tomar dicho valor
void desplazarCpu(int *cursorX, int *cursorY, int *posX, int *posY, int turno, int turnoOpuesto, jug_vect *jv, int tamTablero) {
    // Asegúrate de que las coordenadas se modifican correctamente.
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
        imprimirtablero(*cursorX, *cursorY, turno, turnoOpuesto, jv, tamTablero);
    }
}

// Cabecera: apuntarCPU(int *, int *, int *, int *, int *, int *, jv, j , int, int *, int *, int *, int *, int [])
// Precondición: Variables no nulas
// Postcondición: Modifica el tablero de la Cpu
void apuntarCPU(int *cursorX, int *cursorY, int *posX, int *posY, int *auxX, int *auxY, jug_vect *jv, juego *ju, int tam_vector,
                int *turno, int *turnoOpuesto, int *aciertoPrevioCpu, int *continuarDireccion, int barcosRestantes[]) {
    int valTocado;
    int i, j;
    int intento = 0; // Contador de intentos para evitar bucles infinitos

    // Seleccionar una posición aleatoria válida para disparar si no se ha acertado previamente
    if (*aciertoPrevioCpu == 0) {
        do {
            *posY = numeroAleatorio(tam_vector);
            *posX = numeroAleatorio(tam_vector);
        } while (jv->jug[*turno].tablero2[*posY][*posX] != '~');
        desplazarCpu(cursorX, cursorY, posX, posY, *turno, *turnoOpuesto, jv, tam_vector); // Mueve el cursor a esa posición

        // Evaluar impacto del disparo
        char *casilla = &jv->jug[*turno].tablero1[*cursorY][*cursorX];

        if (*casilla == 'X') { // La CPU ha acertado, entrará en modo búsqueda
            // Guarda las coordenadas originales en caso de fallar en el siguiente intento
            *auxY = *cursorY;
            *auxX = *cursorX;

            jv->jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
            valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
            if (valTocado == 0) {
                actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
                *aciertoPrevioCpu = 0;
                *continuarDireccion = 0;

                jv->jug[*turno].hundidos++;

                if (ju->num_total_bar - jv->jug[*turno].hundidos == 0){ // Finaliza el juego después de que el jugador se quede sin barcos
                    jv->jug[*turno].ganador += 1;
                }
            } else {
                *aciertoPrevioCpu = 1;
                *continuarDireccion = 1;
            }
            imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
            Sleep(100);
        } else {
            jv->jug[*turno].tablero2[*cursorY][*cursorX] = '*';
            imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
            *turno = 1 - *turno;
            *turnoOpuesto = 1 - *turnoOpuesto;
            Sleep(800);
        }
        jv->jug[*turno].num_disp++;
    }
    if (*aciertoPrevioCpu == 1){ // Si la CPU acertó antes
        desplazarCpu(cursorX, cursorY, posX, posY, *turno, *turnoOpuesto, jv, tam_vector);

        // Generar una dirección válida
        intento = 0;
        do {
            i = -1 + numeroAleatorio(3);
            j = -1 + numeroAleatorio(3);
            intento++;
        } while ((*cursorX + i < 0 || *cursorX + i >= tam_vector ||
                  *cursorY + j < 0 || *cursorY + j >= tam_vector ||
                  jv->jug[*turno].tablero2[*cursorY + j][*cursorX + i] != '~') && intento < 50);

        if (intento >= 50) { // En caso de que no tenga casillas libres alrededor seleccionará una aleatoria
            do {
                *posY = numeroAleatorio(tam_vector);
                *posX = numeroAleatorio(tam_vector);
            } while (jv->jug[*turno].tablero2[*posY][*posX] != '~');

            desplazarCpu(cursorX, cursorY, posX, posY, *turno, *turnoOpuesto, jv, tam_vector); // Mueve el cursor a esa posición

            // Evaluar impacto del disparo
            char *casilla = &jv->jug[*turno].tablero1[*cursorY][*cursorX];

            if (*casilla == 'X') { // La CPU ha acertado, entrará en modo búsqueda
                // Guarda las coordenadas originales en caso de fallar en el siguiente intento
                *auxY = *cursorY;
                *auxX = *cursorX;

                jv->jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
                valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
                if (valTocado == 0) {
                    actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
                    *aciertoPrevioCpu = 0;
                    *continuarDireccion = 0;

                    jv->jug[*turno].hundidos++;

                    if (ju->num_total_bar - jv->jug[*turno].hundidos == 0){ // Finaliza el juego después de que el jugador se quede sin barcos
                        jv->jug[*turno].ganador += 1;
                    }

                } else {
                    *aciertoPrevioCpu = 1;
                    *continuarDireccion = 1;
                }
                imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
                Sleep(100);
            } else {
                jv->jug[*turno].tablero2[*cursorY][*cursorX] = '*';
                imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
                *turno = 1 - *turno;
                *turnoOpuesto = 1 - *turnoOpuesto;
                Sleep(800);
            }
            jv->jug[*turno].num_disp++;
        }
        else{
            *posX = *cursorX + i;
            *posY = *cursorY + j;
            desplazarCpu(cursorX, cursorY, posX, posY, *turno, *turnoOpuesto, jv, tam_vector);

            if (jv->jug[*turnoOpuesto].tablero1[*cursorY][*cursorX] == 'X') {
                *continuarDireccion = 1;
                do {
                    jv->jug[*turno].tablero2[*cursorY][*cursorX] = 'X';
                    valTocado = tocadoHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector);
                    if (valTocado == 0) {
                        actualizarHundido(*cursorX, *cursorY, jv, *turno, *turnoOpuesto, tam_vector, barcosRestantes);
                        *aciertoPrevioCpu = 0;
                        *continuarDireccion = 0;

                        jv->jug[*turno].hundidos++;

                        if (ju->num_total_bar - jv->jug[*turno].hundidos == 0){ // Finaliza el juego después de que el jugador se quede sin barcos
                            jv->jug[*turno].ganador += 1;
                        }
                    }
                    // Asegurar que no se sale del tablero
                    if (*cursorX + i >= 0 && *cursorX + i < tam_vector && *cursorY + j >= 0 && *cursorY + j < tam_vector) {
                        *posX = *cursorX + i;
                        *posY = *cursorY + j;
                        desplazarCpu(cursorX, cursorY, posX, posY, *turno, *turnoOpuesto, jv, tam_vector);
                    } else {
                        break; // Si se sale, no continuar
                    }
                    imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
                    Sleep(300);
                    jv->jug[*turno].num_disp++;
                } while (jv->jug[*turnoOpuesto].tablero1[*cursorY][*cursorX] == 'X');
            }
            else {
                jv->jug[*turno].tablero2[*cursorY][*cursorX] = '*';
                imprimirtablero(*cursorX, *cursorY, *turno, *turnoOpuesto, jv, tam_vector);
                *turno = 1 - *turno;
                *turnoOpuesto = 1 - *turnoOpuesto;
                Sleep(800);

                *posX = *auxX; // Vuelve a la posición de acierto original
                *posY = *auxY;
            }
            jv->jug[*turno].num_disp++;
        }
    }
}

// Cabecera: void disparar_jue(jug_vect, bar_vect)
// Precondición: Recibo los registros de jugadores y de barcos
// Postcondición: modifica la información de los jugadores
void disparar_jue(jug_vect *jv, bar_vect *bv, juego *j) {
    clear();
    srand(time(NULL));

    int cursorX[2] = {0, 0}, cursorY[2] = {0, 0}; // Cursores de cada jugador
    int posX[2], posY[2], auxX[2], auxY[2]; //Cursores para el funcionamiento de la Cpu
    int aciertoPrevioCpu[2] = {0,0}, continuarDireccion[2] = {0,0};
    int turno = 0, turnoOpuesto = 1;
    int barcosRestantes[2] = {j->num_total_bar, j->num_total_bar};

    if (jv->jug[0].num_disp == 0){ // Inicializa el número de barcos y de hundidos solo si la partida ha comenzado
        j->num_total_bar = 4;
        jv->jug[0].hundidos = 0;
        jv->jug[1].hundidos = 0;
    }

    while (jv->jug[turno].ganador == 0) {
        if (jv->jug[turno].tipo_disp == 'M') {
            apuntarJugador(&cursorX[turno], &cursorY[turno], jv, j, bv, j->tam_tablero, &turno, &turnoOpuesto, barcosRestantes);
        } else {
            apuntarCPU(&cursorX[turno], &cursorY[turno], &posX[turno], &posY[turno], &auxX[turno], &auxY[turno], jv, j,
                       j->tam_tablero, &turno, &turnoOpuesto, &aciertoPrevioCpu[turno], &continuarDireccion[turno], barcosRestantes);
        }

        guardar_datajuego(j, bv, jv);
    }
}