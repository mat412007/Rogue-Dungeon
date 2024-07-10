#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h> 
#include "RogueVoids.h"
#include <locale.h> 

// Definiciones de colores usando códigos ANSI
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define MAGENTA "\033[1;35m" 
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

// Inicializa la mazmorra con espacios vacíos
void inicializarMazmorra(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra]) {
    for (int i = 0; i < tamanomazmorra; i++) {
        for (int j = 0; j < tamanomazmorra; j++) {
            dungeon[i][j] = ' ';
        }
    }
}

// Genera habitaciones en la mazmorra
void generarHabitaciones(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int habitaciones[10][4]) {
    srand(time(NULL));
    int numHabitaciones = 10; // Número de habitaciones a generar
    int maxTamHabitacion = 10; // Tamano máximo de una habitación
    int habitacionActual = 0;

    while (habitacionActual < numHabitaciones) {
        int ancho = rand() % maxTamHabitacion + 3; // Ancho de la habitación
        int alto = rand() % maxTamHabitacion + 3;  // Alto de la habitación
        int x = rand() % (tamanomazmorra - ancho); // Posición x de la habitación
        int y = rand() % (tamanomazmorra - alto);  // Posición y de la habitación

        int solapa = 0; // Variable para verificar solapamiento
        // Verificar si la habitación se solapa con otra habitacion ya creada
        for (int i = x - 1; i <= x + ancho; i++) {
            for (int j = y - 1; j <= y + alto; j++) {
                if (i >= 0 && i < tamanomazmorra && j >= 0 && j < tamanomazmorra) {
                    if (dungeon[i][j] == '.') {
                        solapa = 1;
                    }
                }
            }
        }
        // Si no hay solapamiento, se genera la habitación
        if (!solapa) {
            for (int j = x; j < x + ancho; j++) {
                for (int k = y; k < y + alto; k++) {
                    dungeon[j][k] = '.';
                }
            }
            habitaciones[habitacionActual][0] = x;      // Posición x de la habitación
            habitaciones[habitacionActual][1] = y;      // Posición y de la habitación
            habitaciones[habitacionActual][2] = ancho;  // Ancho de la habitación
            habitaciones[habitacionActual][3] = alto;   // Alto de la habitación
            habitacionActual++;
        }
    }
}

// Conecta las habitaciones de la mazmorra con pasillos
void conectarHabitaciones(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int habitaciones[10][4]) {
    for (int h = 0; h < 9; h++) {
        int x1 = habitaciones[h][0] + habitaciones[h][2] / 2;      // Centro x de la habitación h
        int y1 = habitaciones[h][1] + habitaciones[h][3] / 2;      // Centro y de la habitación h
        int x2 = habitaciones[h + 1][0] + habitaciones[h + 1][2] / 2;  // Centro x de la siguiente habitación
        int y2 = habitaciones[h + 1][1] + habitaciones[h + 1][3] / 2;  // Centro y de la siguiente habitación

        // Conectar las habitaciones con pasillos
        while (x1 != x2 || y1 != y2) {
            if (x1 < x2) x1++;
            else if (x1 > x2) x1--;
            else if (y1 < y2) y1++;
            else if (y1 > y2) y1--;

            if (dungeon[x1][y1] == ' ') {
                dungeon[x1][y1] = '#';
            }
        }
    }
}

// Coloca enemigos en la mazmorra
void colocarEnemigos(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra]) {
    srand(time(NULL));
    int numEnemigos = 25; // Número de enemigos
    // Colocamos los enemigos
    for (int i = 0; i < numEnemigos; i++) {
        int x = rand() % tamanomazmorra;
        int y = rand() % tamanomazmorra;
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = (rand() % 2 == 0) ? 'C' : 'W';
        } else {
            i--;
        }
    }
    // Colocamos la brujula
    for (int i = 0; i < 1; i++) {
        int x = rand() % tamanomazmorra;
        int y = rand() % tamanomazmorra;
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = 'B';
        } else {
            i--;
        }
    }
    // Colocamos al enemigo final
    for (int i = 0; i < 1; i++) {
        int x = rand() % tamanomazmorra;
        int y = rand() % tamanomazmorra;
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = 'D';
        } else {
            i--;
        }
    }
    // Colocamos las pociones de vida
    for (int i = 0; i < 10; i++) {
        int x = rand() % tamanomazmorra;
        int y = rand() % tamanomazmorra;
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = 'V';
        } else {
            i--;
        }
    }
}

// Imprime la mazmorra en la consola
void imprimirMazmorra(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int fila, int columna, struct caracteristicas jugador) {
    // Opciones para imprimir en la mazmorra
    char esqueleto[] = "☠️";
    char asterisco[] = "✳️";
    char diablo[] = "🤺";
    char asterisc[] = "✴️";
    char devil[] = "😈";
    for (int i = fila - 2; i < fila + 3; i++) {
        for (int j = columna - 2; j < columna + 3; j++) {
            if (jugador.enemigoDerrotado == true && (dungeon[i][j] ==  jugador.guardado )) {
                dungeon[i][j] = '.';
            }
            if (dungeon[i][j] == 'W') {
                printf("%-4s", diablo); // Imprime el enemigo warrior
            } else if (dungeon[i][j] == 'C') {
                printf("%s ", esqueleto); // Imprime el enemigo skull
            } else if (dungeon[i][j] == '@') {
                printf("%-4s", "😎");  // Imprimir emoji del jugador
            } else if (dungeon[i][j] == '.') { // El "piso" (asterisco verde)
                printf("%s ", asterisco);
            } else if (dungeon[i][j] == '#') { // Imprime el pasillo (asterisco naranja)
                printf("%s ", asterisc);
            } else if (dungeon[i][j] == 'V') { // Imprime la pocion de vida
                printf("%-4s", "💉");
            } else if (dungeon[i][j] == 'B') { // Imprime la brujula
                printf("%-4s", "🧭");
            } else if (dungeon[i][j] == 'D') {
                printf("%-4s", devil); // Imprime el enemigo skull
            } else {
                printf("%c ", dungeon[i][j]);
            }
        }
        printf("\n");
    }
    jugador.guardado = ' ';
    jugador.enemigoDerrotado = false;
}

// Actualiza la mazmorra mientras el jugador se mueve
void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original, struct caracteristicas jugador) {
    mazmorra[fila][columna] = *original; // Restaurar el valor original
    *original = mazmorra[fila_nueva][columna_nueva]; // Guardar el valor de la nueva casilla
    mazmorra[fila_nueva][columna_nueva] = '@'; // Mover al jugador
    if (*original == 'W' || *original == 'C' || *original == 'D') {
        jugador.enemigoDerrotado = true;
        jugador.guardado = *original;
        *original = '.';
    }
    if (*original == 'V' || *original == 'B') {
        *original = '.'; // Restaurar la casilla a '.'
    }

}