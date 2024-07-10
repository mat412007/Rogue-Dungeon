#ifndef ROGUEVOIDS_H
#define ROGUEVOIDS_H
#include <stdbool.h>
//En todo este archivo se encuentran las funciones que se usan en el main
//Es necesario declararlas para que se detecten en todos los demas archivos
//Esta es la caracteristica carpeta que tenemos llamada: #include "RogueVoids.h"

struct caracteristicas {
    int vida;
    int resistencia;
    int ataque;
    int experiencia;
    int curaciones;
    bool brujula;
    int experienciaSubirNivel;
int fila;
int columna;
bool enemigoDerrotado;
char guardado;
char nombre[20];
};

void limpiar_consola(); 
int bienvenida(struct caracteristicas jugador);
void inicializarMazmorra(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra]);
void generarHabitaciones(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int habitaciones[10][4]);
void conectarHabitaciones(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int habitaciones[10][4]);
void colocarEnemigos(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra]);
void rellenarMazmorras(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra]);
void imprimirMazmorra(int tamanomazmorra, char dungeon[tamanomazmorra][tamanomazmorra], int fila, int columna, struct caracteristicas jugador);
void actualizar_mazmorra(int n, char mazmorra[n][n], int fila, int columna, int fila_nueva, int columna_nueva, char *original, struct caracteristicas jugador);
void desactivarModoCanonico(struct termios *old_tio);
void restaurarModoCanonico(struct termios *old_tio);
int movimientos(int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char jugador[], struct caracteristicas player);
void opcion2();
void opcion3();
void opcion4();
void opcion5();
void enemigo1();
void enemigo2();
void mostrarMenu();
void pelea(struct caracteristicas jugador, int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char Jugador[]);
void mostrarmapa(int tamanomazmorra, char mazmorra[tamanomazmorra][tamanomazmorra], char jugador, struct caracteristicas player);
void cargarImagen(char *nonvre);
void reproducirMusica(const char *archivo);
void combate();
void menu(struct caracteristicas player);
#endif // ROGUEVOIDS_H 