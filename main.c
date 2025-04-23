#include <windows.h> // Importante para SetConsoleOutputCP
#include "MenuP.h" 
#include "Complementos.h"
#include "Configuracion.h"
#include "IntDatos.h"
#include "disparar.h"

int main() {
    int resultado;
    juego j;
    bar_vect b;
    jug_vect jv;

    // Configurar la consola para que acepte caracteres especiales (UTF-8)
    SetConsoleOutputCP(CP_UTF8);

    // Inicializar estructuras a 0
    memset(&j, 0, sizeof(juego));
    memset(&b, 0, sizeof(bar_vect));
    memset(&jv, 0, sizeof(jug_vect));

    // Cargar datos iniciales
    if (cargar_barcos(&b) == -1) {
        printf("Error al cargar los barcos\n");
        return -1;
    }

    if (cargar_datajuego(&j, &b, &jv) == -1) {
        printf("Error al cargar los datos del juego\n");
        liberar_barcos(&b);
        return -1;
    }

    // Ejecutar menú principal
    resultado = menu_principal(&j, &b, &jv);

    // Guardar datos antes de salir
    if (guardar_datajuego(&j, &b, &jv) == -1) {
        printf("Error al guardar los datos del juego\n");
    }

    if (guardar_barcos(&b) == -1) {
        printf("Error al guardar los barcos\n");
    }

    // Liberar memoria usada
    liberar_tableros(&jv, j.tam_tablero);
    liberar_barcos(&b);
    liberar_juego(&j);

    return resultado;
}