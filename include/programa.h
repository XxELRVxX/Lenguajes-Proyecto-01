/**
 * @file programa.h
 * @brief Definicion de la estructura y funciones principales del programa.
 */

#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "lista_eventos.h"
#include "lista_sitios.h"
#include "lista_facturas.h"
#include "cargar_guardar.h"
#include "usuario.h"
#include "config.h"

/**
 * @struct Programa
 * @brief Estructura principal que contiene toda la informacion del sistema.
 */
typedef struct {
    UsuarioAdministrador admin; /**< Usuario administrador del sistema */
    ListaEventos eventos;       /**< Lista de eventos */
    ListaSitios sitios;         /**< Lista de sitios */
    ListaFacturas facturas;     /**< Lista de facturas */
} Programa;

/**
 * @brief Crea una instancia del programa con listas vacias y usuario inicializado.
 * @return Programa inicializado.
 */
Programa crear_programa();

/**
 * @brief Libera toda la memoria asociada al programa.
 * @param programa Puntero al programa a liberar.
 */
void liberar_programa(Programa *programa);

/**
 * @brief Guarda el estado del programa en archivos.
 * @param programa Puntero constante al programa.
 * @return Codigo de exito o error.
 */
int guardar_programa(const Programa *programa);

/**
 * @brief Carga el estado del programa desde archivos.
 * @param programa Puntero al programa.
 * @return Codigo de exito o error.
 */
int cargar_programa(Programa *programa);


/**
 * @brief Ejecuta el bucle principal del programa con el menu de navegacion.
 * @param programa Puntero al programa inicializado.
 */
void ejecutar_programa(Programa *programa);

/**
 * @brief Muestra el menu administrativo, solicita autenticacion y gestiona las opciones.
 * @param programa Puntero al programa.
 */
void menu_administrativo(Programa *programa);

/**
 * @brief Muestra el menu de opciones generales.
 * @param programa Puntero al programa.
 */
void menu_general(Programa *programa);

/**
 * @brief Lee una opcion numerica del usuario desde el teclado.
 * @return Opcion leida, o 0 si la entrada no es un numero valido.
 */
int leer_opcion();

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

#endif //PROGRAMA_H