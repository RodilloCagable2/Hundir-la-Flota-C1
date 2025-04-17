#include "MenuP.h"
#include "Complementos.h"
#include "Configuracion.h"
#include "IntDatos.h"
#include "disparar.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
    int resultado;
    juego j;
    bar_vect b;
    jug_vect jv;

    // Inicializar estructuras
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
	
	//disparar_jue(&jv, &b, &j);
	
    // Ejecutar menú principal
    resultado = menu_principal(&j, &b, &jv);

    // Guardar datos antes de salir
    if (guardar_datajuego(&j, &b, &jv) == -1) {
        printf("Error al guardar los datos del juego\n");
    }

    if (guardar_barcos(&b) == -1) {
        printf("Error al guardar los barcos\n");
    }

    // Liberar memoria
    liberar_tableros(&jv, j.tam_tablero);
    liberar_barcos(&b);
    liberar_juego(&j);

    return resultado;
}