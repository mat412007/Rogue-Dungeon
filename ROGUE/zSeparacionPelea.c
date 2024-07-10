#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h"
#include <locale.h>
#include <sys/wait.h>

#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//-------------------------------------------------------------------------------------------------------
void historiaRogueVictoria() {
    limpiar_consola();
    printf("\nUna vez derrotada"); printf(RED" la maldad pura"RESET); puts(". . .");
    usleep(5000000);
    puts("El jugador pudo salir de sus aposentos oscuros. . .");
    usleep(5000000);
    puts("El jugador se reencuentra con los seres que quiere");
    usleep(4000000);
    puts(GREEN"            Los seres que ama"RESET);
    usleep(4000000);
    puts(RED"Tal vez incluso, hasta a los que odia. . ."RESET);
    usleep(3000000);
    puts("Pero de algo se entera");
    usleep(3000000);
    puts("Ha estado equivocado desperdiciando tanto tiempo en luchar contra los malos");
    usleep(3000000);
    printf("Tal vez debio pasar mas tiempo con su familia, padres, hijos, esposa. ");
    usleep(3500000);
    puts(GREEN"Ahora, por fin tras descubrirlo, tiene tiempo para ello.  .  ."RESET);
    usleep(3000000);
    puts(RED"                                    ! !"RESET);
    usleep(3000000);
    cargarImagen("ROGUE/Txt/VICOTIRA.txt");
    exit(0);
}
//-------------------------------------------------------------------------------------------------------
void pelea(struct caracteristicas jugador, int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char player[]) {
    struct enemigo { //Este struct es el struct base para el enemigo
        int vida;
        int ataque;
        int resistencia;
    };
    //Aca creamos TRES de sus variantes para los enemigos 
    struct enemigo esqueleto; //Asignamos vida, ataque y resistencia a esqueleto
    esqueleto.vida = 3;
    esqueleto.ataque = 2;
    esqueleto.resistencia = 3;

    struct enemigo diablo; //Asignamos vida, ataque y resistencia a guerrero
    diablo.vida = 6;
    diablo.ataque = 3;
    diablo.resistencia = 4;

    struct enemigo devil; //Asignamos vida, ataque y resistencia al jefe final
    devil.vida = 10;
    devil.ataque = 7;
    devil.resistencia = 20;

    struct enemigo* enemigoPelea; //Con esta variable podemos cambiar el enemigo que se enfrenta
    if (jugador.guardado == 'C') { //Aca es donde usamos punteros (* en enemigo de la linea 39)
        enemigoPelea = &esqueleto; //y aca el "&"
    } else if (jugador.guardado == 'W') {
        enemigoPelea = &diablo; //y aca el "&"
    } else if (jugador.guardado == 'D') {
        enemigoPelea = &devil; //y aca el "&"
    } else {
        return;
    }

    int eleccion;
    bool escapar = false; // Variable para manejar la escapada
    while (!escapar) {
    //Si es distinto a escapar (osea, que este en falso) inicia toda la secuencia
        if (enemigoPelea->resistencia <= 0) {  //Si la resistencia es 0
             enemigoPelea->vida += enemigoPelea->resistencia; //Le resta los puntos negativos de res
             enemigoPelea->resistencia = 0; //y la combierte en 0 para que nose bugee
        }
        limpiar_consola();
        if (jugador.guardado == 'C') {
            cargarImagen("ROGUE/Txt/skull.txt"); //Lamamos desde otras carpetas una imagen
            printf("\n 😎                       ⚔️                        ☠️\n"); //decoracion
        }
        if (jugador.guardado == 'W') {
            cargarImagen("ROGUE/Txt/warrior.txt"); //Lamamos desde otras carpetas una imagen
            printf("\n 😎                       ⚔️                        🛡️\n"); //decoracion
        }
        if (jugador.guardado == 'D') {
            cargarImagen("ROGUE/Txt/devil.txt"); //Lamamos desde otras carpetas una imagen
            printf("\n 😎                       ⚔️                        😈\n"); //decoracion
        }
        printf(" ┌───────────────────┐          ┌────────────────────┐\n");
        printf(" │ Vida: %2d          │          │ Vida: %2d           │\n", jugador.vida, enemigoPelea->vida);
        printf(" │ Resistencia: %2d   │          │ Resistencia: %2d    │\n", jugador.resistencia, enemigoPelea->resistencia);
        printf(" └───────────────────┘          └────────────────────┘\n");
        printf("Elija su movimiento:\n"); //decoracion 
        printf(RED"Ataque básico (1)\n"RESET); //El ataque
        printf(CYAN"Defenderse (2)\n"RESET); //El aumento de resistencia
        printf(RED"Curarse (3)\n"RESET); //El aumento de vida
        if (scanf("%d", &eleccion) != 1) {
            // Limpiar el buffer de entrada en caso de entrada no válida
            while (getchar() != '\n'); //Esto detecta siga s ies diferente a enter
            printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
            continue; //Es una foma de decirle que prosiga sin que afecte nada
        } //Presiona para elegir
        
        if (eleccion > 4 || eleccion < 1) { //No pongas un numero mayor al cuatro o menor al 1, ash
            printf(RED"Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
            continue;
        }

        if (eleccion == 1) { // Ataque básico
            if (enemigoPelea->resistencia <= 0) { //Si el golpe es tal que baja la res menos de 0
                enemigoPelea->vida += enemigoPelea->resistencia; //Le resta los puntos correspondientes
                enemigoPelea->resistencia = 0; //y la combierte en 0 para que nose bugee
            }
            if (enemigoPelea->resistencia == 0) { //Si la res es 0
                enemigoPelea->vida -= jugador.ataque; //Directamente es daño a la vida del enemigo
            } else {
                enemigoPelea->resistencia -= jugador.ataque; //Si no, le resta solo a la defensa
            }
        } else if (eleccion == 2) { // Defenderse
            jugador.resistencia += 3; //Aumenta en 3 la ressitencia
        } else if (eleccion == 3 && jugador.curaciones > 0) { // Curarse
            jugador.vida += 7; //Aumenta en 7 la vida
            jugador.curaciones--; //Restamos una jeringa
        } 

        if (enemigoPelea->vida <= 0) { //Si el enemigo tiene 0 de vida
            if(jugador.guardado == 'D') { //SI AL QUE DERROTASTES FUE A D......
                limpiar_consola();
                cargarImagen("ROGUE/Txt/VICOTIRA.txt"); //GANAMOS... Digo, imprime un cartelito bonito de victoria
                printf(CYAN"\n\nAhora eres el rogue %s"RESET,jugador.nombre); //Sos el rogue, que honor :o
                int decision;
                do {
                    printf(CYAN "\n\nIngresa 1 para continuar la historia, o 0 para salir: " RESET);
                    scanf("%d", &decision);
                    while(getchar() != '\n');  // Limpiar el buffer de entrada
                    if (decision == 1) {
                        historiaRogueVictoria();  // Llamar a la función si se ingresa 1
                        break;
                    } else if (decision == 0) {
                        limpiar_consola();
                        cargarImagen("ROGUE/Txt/VICOTIRA.txt"); //GANAMOS... Digo, imprime un cartelito bonito de victoria
                        exit(0);  // Terminar el juego, vayase
                    } else {
                        printf(RED "\nEl rogue solo tiene una historia. . ." RESET);
                    }
                } while (decision != 1 && decision != 0);
            }
            limpiar_consola();
               cargarImagen("ROGUE/Txt/derrotasteAlEnemigo.txt");
                printf(RED"\n\nDerrotaste al enemigo\n"RESET); //:D
            puts(RED"Pulsa enter para volver"RESET);
            while(getchar() != '\n');  // Limpiar el buffer de entrada
            escapar = true; //Se le vence, saliendo de la funcion pelea
            jugador.enemigoDerrotado = true; //Y conviertiendo devuelta esto a true, permitiendo moverse
            while (getchar() != '\n'); //Enter
            limpiar_consola();
            jugador.experiencia += 5; //Ganamos exp
            if(jugador.experiencia >= jugador.experienciaSubirNivel) { //Si subimos de nivel
                jugador.ataque += 2; //Sumamos ataque
                jugador.vida += 2; //sumamos vida
                jugador.experiencia = 0; //Reiniciamos la experiencia
            }
            movimientos(tamanomazmorra, mazmorra, player, jugador); //llamamos de vuelta a los movimientos
            jugador.guardado = ' ';
            return; // Salir de la funcion despues de derrotar al enemigo
        }

        // Animacion de la pelea
        limpiar_consola(); //limpiamos consola
        cargarImagen("ROGUE/Txt/combate.txt"); //Imprime un cartel enorme e inutil para dar decoracion
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(600000); //Esperamos medio segundo
        limpiar_consola(); //limpiamos consola
        cargarImagen("ROGUE/Txt/combateDos.txt"); //Imprime un cartel enorme e inutil para dar decoracion
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(600000); //Esperamos medio segundo
        limpiar_consola(); //limpiamos consola
        cargarImagen("ROGUE/Txt/combate.txt"); //Imprime un cartel enorme e inutil para dar decoracion
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(600000); //Esperamos medio segundo
        limpiar_consola(); //limpiamos consola
        cargarImagen("ROGUE/Txt/combateDos.txt"); //Imprime un cartel enorme e inutil para dar decoracion
        printf(RED"\nEsperando el movimiento del enemigo. . . . .\n"RESET);
        usleep(600000); //Esperamos medio segundo
        limpiar_consola(); //limpiamos consola

        // Movimiento del enemigo
        if (jugador.resistencia >= 1) { //Si la resistencia del jugador es mayor o igual a uno
            jugador.resistencia -= enemigoPelea->ataque; //se le baja la resistencia al jugador
        } 
        if (jugador.resistencia <= 0) {  //Si la resistencia es menor a 0
            jugador.resistencia = 0; //Se convierte en 0 la res del jugador
            if(eleccion == 3){ //Si la eleccion es 3 mientras estamos en 0, tenemos que retomar y:
                 jugador.resistencia += 3; //sumamos defensa
                 jugador.resistencia -= enemigoPelea->ataque; //Restamos a la defensa el ataque del enemigo
            }
        }
        if (jugador.resistencia <= 0) { //Si la resistencia del jugador es menor o igual a 0
            jugador.vida -= enemigoPelea->ataque; //Se le resta la vida correspondiente
        }
        if (jugador.resistencia < 0) { //Esto es inutil, pero venga, que funciona con esto puesto
            jugador.vida += jugador.resistencia; // Restar la resistencia negativa a la vida
            jugador.resistencia = 0;
        }
        if(jugador.vida == 0 || jugador.vida <= 0) { //Perdiste si tu vida llega a 0 o menor a 0
            limpiar_consola();
            cargarImagen("ROGUE/Txt/PERDISTE.txt"); //Imprime el cartel de la miseria
            exit(0); //Vayase
        }
    }
    // Verifica si el jugador escapó y maneja eso fuera del bucle
} //-------------------------------------------------------------------------------------------------------