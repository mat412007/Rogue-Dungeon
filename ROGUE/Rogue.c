#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Permite la modificacion del termios
// Todos estos son los colores que agregamos
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

// Este es el main, tiene un swich el cual tiene las llamadas a funciones.
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, ""); // Anade la "funcion" (por asi decirlo) para colocar emojis
  char simbolo[] = "😎";  // una variable para el emoji (Este es el protagonista
  int habitaciones[10][4];
  int fila, columna;
  // declaro la mazmorra y su tamano
  int tamanomazmorra = 40;
  char dungeon[tamanomazmorra][tamanomazmorra];
  struct caracteristicas { // Este es un struct de las caracteristicas del
                           // jugador
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
  struct caracteristicas jugador; // Este struct almacena las caracteristicas
                                  // del jugador (se las asigna)
  jugador.fila = 0;
  jugador.columna = 0;
  jugador.vida = 12;
  jugador.resistencia = 2;
  jugador.ataque = 4;
  jugador.experiencia = 10;
  jugador.curaciones = 0;
  jugador.brujula = false;
  jugador.experienciaSubirNivel = 20;
  jugador.enemigoDerrotado = false;
  jugador.guardado = ' ';
  strcpy(jugador.nombre, " "); // Exportamos el nombre

  int opcion;
  printf(
      YELLOW
      "                    ┌───────────────────────────────────────┐\n" RESET);
  printf(
      YELLOW
      "                    │           R   O   G   U   E           │\n" RESET);
  printf(
      YELLOW
      "                    └───────────────────────────────────────┘\n" RESET);
  bienvenida(jugador);
  limpiar_consola();
  mostrarMenu();
  // Opciones para que el jugador elija
  while (1) {              // Un while para repetir todo en bucle
    setlocale(LC_ALL, ""); // esto es para activar los emojis
    printf(WHITE "Ingrese una opción: " RESET);
    int l = 0;
    if (scanf("%d", &opcion) != 1) {
      // Limpiar el buffer de entrada en caso de entrada no válida
      while ((l = getchar()) != '\n')
        ; // Esto detecta siga s ies diferente a enter
      //\n = enter porque con el enter es como que saltas de linea
      limpiar_consola(); // llamar funciones
      mostrarMenu();
      printf(RED
             "Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
      continue; // Es una foma de decirle que prosiga sin que afecte nada
    }

    getchar(); // Captura el Enter después de ingresar la opción

    switch (opcion) {
    case 1: // Empieza el juego y comienza una pantalla de carga "Animada"
      limpiar_consola();
      for (int cargando = 0; cargando <= 100; cargando += 5) {
        printf("┌──────────────────────────────────┐\n");
        printf("│          Cargando:%3d%%           │\n", cargando);
        printf("│                                  │\n");
        printf("└──────────────────────────────────┘\n");
        usleep(200000); // Pausa de 0.2 segundos
        limpiar_consola();
      }
      // Iniciamos con una mazmorra vacia
      inicializarMazmorra(tamanomazmorra, dungeon);
      // Generamos las habitaciones de la mazmorra
      generarHabitaciones(tamanomazmorra, dungeon, habitaciones);
      // Conectamos las habitaciones con pasillos
      conectarHabitaciones(tamanomazmorra, dungeon, habitaciones);
      // Colocamos enemgis y elementos en la mazmorra
      colocarEnemigos(tamanomazmorra, dungeon);
      for (int i = 0; i < 1;
           i++) { // un for en donde va a hubicar a nuestro jugador en:
        jugador.fila = rand() % tamanomazmorra;    // una fila random
        jugador.columna = rand() % tamanomazmorra; // una columna random
        if (dungeon[jugador.fila][jugador.columna] ==
            '.') { // y si la casilla es un punto
          dungeon[jugador.fila][jugador.columna] = '@'; // se convierte en un @
        } else {
          i--; // esto es para detectar los espacios vacios
        }
      }
      movimientos(tamanomazmorra, dungeon, simbolo, jugador, fila, columna);
      break;
    case 2: // Muestra las reglas del juego
      opcion2();
      limpiar_consola();
      mostrarMenu();
      break;
    case 3: // Muestra los controles del juego
      opcion3();
      limpiar_consola();
      mostrarMenu();
      break;
    case 4: // Muestra los enemigos del juego
      opcion4();
      limpiar_consola();
      mostrarMenu();
      break;
    case 5: // Muestra los Objetos que aparecen en el juego
      opcion5();
      limpiar_consola();
      mostrarMenu();
      break;
    case 6: // Cierra el juego
      limpiar_consola();
      for (int i = 0; i <= 100;
           i += 10) { // esto es una barra de carga de salida
        for (int i = 0; i < 3; i++) {
          printf(WHITE "┌─────────────────────────┐\n" RESET);
          if (i == 0) {
            printf(WHITE "│        Saliendo.        │\n" RESET);
          }
          if (i == 1) {
            printf(WHITE "│        Saliendo..       │\n" RESET);
          }
          if (i == 2) {
            printf(WHITE "│        Saliendo...      │\n" RESET);
          }
          printf(WHITE "└─────────────────────────┘\n" RESET);
          usleep(200000); // 200,000 microsegundos = 0.2 segundos
          limpiar_consola();
        }
        usleep(200000);
        limpiar_consola();
      }
      return 0;
    default:
      limpiar_consola();
      printf(RED
             "Opción inválida. Por favor, ingrese una opción válida.\n" RESET);
      mostrarMenu();
      break;
    }
  }
  return 0;
}