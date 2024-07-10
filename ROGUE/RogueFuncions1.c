#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"
//ESTA PARTE DE LAS FUNCIONES INCLUYEN:
//1. Limpiar consola: Para limpiar la consola como si fuese un system("clear");
//2. Bienvenida: Para imprimir el menu donde ubicamos nuestro nombre para el jugador.
//3. Rellenar mazmorras: Para rellenar las mazmorras con los enemigos y los * respectivos.

//Colores
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m" 
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//Este era un intento de emoji, ya encontramos otra manera de tenerlos pero por ahora vamos a dejarla, a lo mejor nos sirev en el futuro
#define CRAW "\U0001f980"

//-------------------------------------------------------------------------------------------------------

void limpiar_consola() {
    printf("\033[H\033[J"); //Esto limpia la consola, como un system("clear") pero mas efectivo
}
// \033[H lleva el cursor de la consola a la posición superior izquierda y \033[J borra desde la posición actual del cursor hasta el final de la pantalla.

//-------------------------------------------------------------------------------------------------------

int bienvenida(struct caracteristicas jugador) { //Esta funcion es la primera que aparece en el juego, pide un nombre de no mas de 20 caracteres
    while (1) {
        printf(WHITE"                    Bienvenido jugador. Ingrese su nombre: "RESET); //Asi se pone colores 
        //Con "WHITE" o cualquier color definido, y siempre al final "RESET" (Para que se vuelva a su color original) 
        scanf("%s", jugador.nombre);
        limpiar_consola();
        break;
    }
}
//-------------------------------------------------------------------------------------------------------