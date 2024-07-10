#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <unistd.h> // Permite la modificacion del termios
#include <termios.h>
#include "RogueVoids.h" //Esta libreria anade nuestras funciones
#include <locale.h>

void desactivarModoCanonico(struct termios *old_tio) {
  struct termios new_tio; //Esta funcion sirve para desactivar el modo canonico
  //Basicamente modifica valores del termios (o terminal) para que el enter se tome automaticamente
  //Una vez terminado lo que queriamos, se usa el "restaurarModoCanonico" para que los atributos del termios
  //Valgan lo mismo de antes

  // Guardar la configuración actual del terminal
  tcgetattr(STDIN_FILENO, old_tio);

  // Desactivar el modo canónico y el eco
  new_tio = *old_tio;
  new_tio.c_lflag &= (~ICANON & ~ECHO);
  new_tio.c_cc[VMIN] = 1;
  new_tio.c_cc[VTIME] = 0;

  // Establecer los nuevos atributos
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restaurarModoCanonico(struct termios *old_tio) {
  //Esta funcion sirve para restaurar la terminal a su estado original
  tcsetattr(STDIN_FILENO, TCSANOW, old_tio); 
}