#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <termios.h>
#include "RogueVoids.h"

//-------------------------------------------------------------------------------------------------------

void cargarImagen(char *nonvre) { //Esta funcion nos permite abrir archivos como los .txt
  FILE *f = fopen(nonvre, "r"); //Abre un archivo dirigido a "r" (osea, read)
  if(f) { //Este if abre el archivo si es que existe
    char CE;
    while((CE = fgetc(f)) != EOF) { //Este while nos permite leer el archivo linea por linea
      putc(CE, stdout); //manda a imprimir el archivo
    }
    fclose(f); //Cierra un archivo
  } else { //Si no hay nombre del archivo, imprime esto 
    printf("No existe un formato para este enemigo\n");
  }
}

//-------------------------------------------------------------------------------------------------------