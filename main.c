#include "MenuP.h"
#include "Complementos.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main () {
    srand(time(NULL));

    bar_vect bv = cargar_barcos ();
    jug_vect jv;
    juego ju = cargar_datajuego (bv, jv);

    menu_principal (jv, bv, ju);

    //Liberar memoria
    liberar_tableros (&jv, ju.tam_tablero);
    liberar_barcos (&bv);
    liberar_juego (&ju);

    return 0;
}
