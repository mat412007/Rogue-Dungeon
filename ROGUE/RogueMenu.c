//RogueGame.c 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "RogueVoids.h" 
//#include "miniaudio.h" //Una libreria para un intento de musica, no creo que funcione...

//ESTA PARTE DE LAS FUNCIONES INCLUYEN:
//Las opciones del 2 al 4 (La opcion 1 es un conjunto de llamadas en el main).
//mostrarMenu, una funcion para mostrar el menu el cual aparece despues de ingresar el nombre

#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

//-------------------------------------------------------------------------------------------------------

//Muestra el menu
void mostrarMenu() {
    //char nombreArchivo[] = "ROGUESONGCUBECAVERN.mp3"; // Cambia esto por la ruta de tu archivo de música
    //reproducirMusica(nombreArchivo);

    cargarImagen("ROGUE/Txt/ROGUE.txt"); //Carga una imagen txt de la palabra rogue
    puts("");
    printf(CYAN"                                        ┌───────────────┐\n"RESET);
    printf(CYAN"                                        │ Menú:         │\n"RESET);
    printf(CYAN"                                        │---------------│\n"RESET);
    printf(CYAN"                                        │ 1. Jugar      │\n"RESET);
    printf(CYAN"                                        │ 2. Reglas     │\n"RESET);
    printf(CYAN"                                        │ 3. Controles  │\n"RESET);
    printf(CYAN"                                        │ 4. Enemigos   │\n"RESET);
    printf(CYAN"                                        │ 5. Items      │\n"RESET);
    printf(CYAN"                                        │ 6. Salir      │\n"RESET);
    printf(CYAN"                                        └───────────────┘\n"RESET);   
    //reproducirMusica("ROGUESONGCUBECAVERN.mp3"); //Esto aun esta en proceso, se supone que sirve para
    //Poner musica
}

//-------------------------------------------------------------------------------------------------------

//Limpia la consola y muestra las reglas del juego
void opcion2() {
    limpiar_consola();
    printf(BLUE"┌────────────────────────────────┐\n"RESET);
    printf(BLUE"│    Reglas del juego:           │\n"RESET);
    printf(BLUE"├────────────────────────────────┤\n"RESET);
    printf(BLUE"│- Tienes que llegar hasta       │\n"RESET);
    printf(BLUE"│  al jefe y derrotarlo          │\n"RESET);
    printf(BLUE"│                                │\n"RESET);
    printf(BLUE"│- En la mazmorra                │\n"RESET);
    printf(BLUE"│  habrán enemigos que           │\n"RESET);
    printf(BLUE"│  tratarán de matarte           │\n"RESET);
    printf(BLUE"│  estos tienen sus stats:       │\n"RESET);
    printf(BLUE"│  Fuerza, Vida. Al igual        │\n"RESET);
    printf(BLUE"│  que tu personaje.             │\n"RESET);
    printf(BLUE"│                                │\n"RESET);
    printf(BLUE"│- También habrán objetos        │\n"RESET);
    printf(BLUE"│  que mejorarán tus             │\n"RESET);
    printf(BLUE"│  capacidades, como la vida     │\n"RESET);
    printf(BLUE"│  o la fuerza.                  │\n"RESET);
    printf(BLUE"└────────────────────────────────┘\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
    while (getchar() != '\n');
    limpiar_consola();
}

//-------------------------------------------------------------------------------------------------------

// Muestra los controles del juego
void opcion3() {
    limpiar_consola();
    printf(MAGENTA"         ┌─────┐               w: Moverte hacia arriba\n"RESET);
    printf(MAGENTA"         │  w  │\n"RESET);
    printf(MAGENTA"         └─────┘               a: Moverte hacia la izquierda\n"RESET);
    printf(MAGENTA" ┌─────┐ ┌─────┐  ┌─────┐\n"RESET);
    printf(MAGENTA" │  a  │ │  s  │  │  d  │      s: Moverte hacia abajo\n"RESET);
    printf(MAGENTA" └─────┘ └─────┘  └─────┘\n"RESET);
    printf(MAGENTA"                               d: Moverte hacia la derecha\n"RESET);
    printf("\n");
    printf(MAGENTA" ┌─────┐\n"RESET);
    printf(MAGENTA" │  m  │                       m: Te permite ver el mapa\n"RESET);
    printf(MAGENTA" └─────┘               \n"RESET);
    printf(MAGENTA" ┌─────┐\n"RESET);
    printf(MAGENTA" │  q  │                       q: Te permite ver tus caracteristicas\n"RESET);
    printf(MAGENTA" └─────┘               \n"RESET);
    printf(MAGENTA" ┌─────┐\n"RESET);
    printf(MAGENTA" │  c  │                       c: Te permite curarte\n"RESET);
    printf(MAGENTA" └─────┘               \n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
    while (getchar() != '\n'); // Espera a que el usuario presione Enter (esto funciona ya que el enter se
    //detecta como un salto de linea)
    limpiar_consola();
}

//-------------------------------------------------------------------------------------------------------

//Muestra al enemigo final
void enemigo3(){
    limpiar_consola();
    cargarImagen("ROGUE/Txt/devil.txt"); //Carga la imagen del enemigo final
    puts("");
    printf(RED"Presiona Enter para salir\n"RESET); 
    while (getchar() != '\n');//Espera a que el usuario presione Enter
    limpiar_consola();
    printf("☠️ ");
    printf(WHITE": Tiene 2 de vida y 3 de resistencia. Te quita 2 de vida\n"RESET);
    printf("🤺 ");
    printf(WHITE": Tiene 6 de vida y 4 de resistencia. Te quita 3 de vida\n"RESET);
    printf("😈 ");
    printf(WHITE": Tiene 10 de vida y 20 de resistencia. Te quita 7 de vida\n"RESET);
    printf(WHITE"Presiona 'S' para ver al esqueleto, 'W' para ver a guerrero, y 'D' para ver al enemigo final.\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
}

//-------------------------------------------------------------------------------------------------------

void opcion4() {
    struct termios old_tio;
    desactivarModoCanonico(&old_tio); //Activa la funcion para dejar de presionar enter
    char tecla;
    limpiar_consola();
    printf("☠️ ");
    printf(WHITE": Tiene 2 de vida y 3 de resistencia. Te quita 2 de vida\n"RESET);
    printf("🤺 ");
    printf(WHITE": Tiene 6 de vida y 4 de resistencia. Te quita 3 de vida\n"RESET);
    printf("😈 ");
    printf(WHITE": Tiene 10 de vida y 20 de resistencia. Te quita 7 de vida\n"RESET);
    printf(WHITE"Presiona 'S' para ver al esqueleto, 'W' para ver a guerrero, y 'D' para ver al enemigo final.\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
    while (1) {
        tecla = getchar(); //Pide las teclas s o w, si se ingresan, va hacia enemigo1 o enemigo2 
        //Estos son las funciones para imprimir la imagen
        if (tecla == 'S' || tecla == 's') {
            enemigo1();
        } else if (tecla == 'W' || tecla == 'w') {
            enemigo2();
        } else if (tecla == 'D' || tecla == 'd') {
            enemigo3();
        } else{
            while (tecla != '\n'); //Espera a que el usuario presione Enter
            limpiar_consola();
            break;
        }
    }
     restaurarModoCanonico(&old_tio); //Pone en el valor comun el termios
}

//-------------------------------------------------------------------------------------------------------

//Muestra al enemigo skull
void enemigo1(){
    limpiar_consola();
    cargarImagen("ROGUE/Txt/skull.txt"); //Imprime la imagen mediante la funcion "cargarImagen"
    puts(""); 
    printf(RED"Presiona Enter para salir\n"RESET); 
    while (getchar() != '\n'); //Espera a que el usuario presione Enter
    limpiar_consola();
    printf("☠️ ");
    printf(WHITE": Tiene 2 de vida y 3 de resistencia. Te quita 2 de vida\n"RESET);
    printf("🤺 ");
    printf(WHITE": Tiene 6 de vida y 4 de resistencia. Te quita 3 de vida\n"RESET);
    printf("😈 ");
    printf(WHITE": Tiene 10 de vida y 20 de resistencia. Te quita 7 de vida\n"RESET);
    printf(WHITE"Presiona 'S' para ver al esqueleto, 'W' para ver a guerrero, y 'D' para ver al enemigo final.\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
}

//-------------------------------------------------------------------------------------------------------

//Muestra al enemigo warrior
void enemigo2(){
    limpiar_consola();
    cargarImagen("ROGUE/Txt/warrior.txt"); //Carga la imagen del warrior
    puts("");
    printf(RED"Presiona Enter para salir\n"RESET); 
    while (getchar() != '\n');//Espera a que el usuario presione Enter
    limpiar_consola();
    printf("☠️ ");
    printf(WHITE": Tiene 2 de vida y 3 de resistencia. Te quita 2 de vida\n"RESET);
    printf("🤺 ");
    printf(WHITE": Tiene 6 de vida y 4 de resistencia. Te quita 3 de vida\n"RESET);
    printf("😈 ");
    printf(WHITE": Tiene 10 de vida y 20 de resistencia. Te quita 7 de vida\n"RESET);
    printf(WHITE"Presiona 'S' para ver al esqueleto, 'W' para ver a guerrero, y 'D' para ver al enemigo final.\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
}

//-------------------------------------------------------------------------------------------------------

//Muestra los objetos
void opcion5() {
    limpiar_consola();
    printf(GREEN"🧭: te permite ver tu ubicacion en el mapa\n"RESET);
    printf(GREEN"💉: te recupera x cantidad de vida\n"RESET);
    printf(WHITE"Presiona Enter para salir\n"RESET);
    while (getchar() != '\n'); //Espera a que el usuario presione Enter
    limpiar_consola();
}

//-------------------------------------------------------------------------------------------------------
