/**
 * @file ui.h
 * @brief Funciones de entrada/salida por consola.
 */

#ifndef UI_H
#define UI_H

#include "config.h"

/**
 * @brief Lee una opcion numerica del usuario desde el teclado.
 * @return Opcion leida, o 0 si la entrada no es un numero valido.
 */
int leer_opcion();

/**
 * @brief Lee un indice numerico y repite hasta que sea valido.
 * @param min Valor minimo aceptado (inclusive).
 * @param max Valor maximo aceptado (inclusive).
 * @return Indice valido entre min y max.
 */
int leer_indice_valido(int min, int max);

/**
 * @brief Lee una cadena de caracteres desde stdin.
 * @param buffer Buffer donde se almacenara la cadena leida.
 * @param largo_cadena tamaño maximo del buffer.
 */
void leer_cadena(char *buffer, int largo_cadena);

/**
 * @brief Limpia la consola. Compatible con Windows y Linux.
 */
void limpiar_consola();

#endif /* UI_H */
