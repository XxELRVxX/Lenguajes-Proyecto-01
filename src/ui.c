/**
 * @file ui.c
 * @brief Implementacion de funciones de entrada/salida por consola.
 */

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Lee una opcion numerica del usuario desde el teclado.
 * @return Opcion leida, o 0 si la entrada no es un numero valido.
 */
int leer_opcion(void) {
    int opcion;
    int leido = scanf("%d", &opcion);
    while (getchar() != '\n');

    if (leido == ENTRADA_VALIDA) {
        return opcion;
    } else {
        return ENTRADA_INVALIDA;
    }
}

/**
 * @brief Lee un indice numerico y repite hasta que sea valido.
 * @param min Valor minimo aceptado (inclusive).
 * @param max Valor maximo aceptado (inclusive).
 * @return Indice valido entre min y max.
 */
int leer_indice_valido(int min, int max) {
    int indice;
    do {
        indice = leer_opcion();
        if (indice < min || indice > max) {
            printf("Opcion invalida. Ingrese un numero entre %d y %d: ", min, max);
        }
    } while (indice < min || indice > max);
    return indice;
}

/**
 * @brief Lee una cadena de caracteres desde stdin.
 * @param buffer Buffer donde se almacenara la cadena leida.
 * @param largo_cadena tamaño maximo del buffer.
 */
void leer_cadena(char *buffer, int largo_cadena) {
    if (fgets(buffer, largo_cadena, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/**
 * @brief Limpia la consola. Compatible con Windows y Linux.
 */
void limpiar_consola() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
