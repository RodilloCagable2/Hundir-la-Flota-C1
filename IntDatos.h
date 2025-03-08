//Archivo de cabecera del Módulo Introducir Datos

#ifndef INTDATOS_H_INCLUDED
#define INTDATOS_H_INCLUDED

//Registros que usara la configuracion
typedef struct{
    char nombre[20];
    int T_Disparo;
    int Comienza;
}Jugador;

typedef struct{
    Jugador v_jugador[2];
    int Tam_Mapa;
}Config;

typedef struct{
    int id_barco;
    char nombre[20];
    int tam;
    int cantidad;
}Barco;

//Funciones que usara la configuracion

//Precondicion: char nombre[] es el vector de caracteres donde almacenaremos la cadena, su tamaño maximo es 20
//Postcondicion: Introducir una cadena de caracteres a un vector desde el teclado
void int_nombre(char nombre[]);

/*Precondicion: int barcos[] es el vector de enteros donde almacenaremos el numero de barcos de cada tipo, la posicion 0 corresponde a los submarinos,
                la uno a las fragatas, la dos a los destructores, la tres a los cruceros, la cuatro a los acorazados, y la quinta a los portaaviones.
                Por otro lado, tam el valor que determina el tamaño del mapa */
/*Postcondición: Establecer el numero de barcos de cada tipo que se desean colocar, sin que estos sobrepasen el espacio maximo teorico establecido por las
                dimensiones del mapa */
//void num_barco(int barcos[],int tam);

//Precondición: int*valor es un puntero a entero donde se introducirá el valor
//Postcondición: Introducir un 0 o 1 y almacenarlo mediante el puntero, además de asegurarse que solo pueda ser un 1 o un 0.
int comienza(int valor);

//Precondición: int*valor es un puntero a entero donde se introducirá el valor
//Postcondición: Introducir un 0 o 1 y almacenarlo mediante el puntero, además de asegurarse que solo pueda ser un 1 o un 0.
int tipo_disparo(int valor);

//Precondición: int*valor es un puntero a entero donde se introducirá el valor
//Postcondición: Introducir el valor que determinará las dimensiones del tablero
int tam_tab(int valor);

//Precondición: N/A
//Postcondición: Permitir la creación y/o modificación del fichero barcos.txt
void perso_barco();

//Precondición: N/A
//Postcondición: Contar el número de ids distintos en el fichero barcos.txt
int cont_barco();

void ini_regbarco(Barco registro[]);

#endif

