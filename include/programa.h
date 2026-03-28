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

#endif //PROGRAMA_H