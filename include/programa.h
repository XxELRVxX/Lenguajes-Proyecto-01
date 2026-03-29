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
#include "ui.h"

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
 * @brief Muestra el submenu de gestion de sitios de eventos.
 * @param programa Puntero al programa.
 */
void gestion_sitios(Programa *programa);

/**
 * @brief Muestra el submenu de gestion de sectores de sitios de eventos.
 * @param programa Puntero al programa.
 */
void gestion_sectores(Programa *programa);

/**
 * @brief Muestra el submenu de gestion de eventos.
 * @param programa Puntero al programa.
 */
void gestion_eventos(Programa *programa);

/**
 * @brief Revalida los punteros Factura.evento tras un realloc en lista_eventos.
 * @details Debe llamarse despues de cualquier agregar_evento exitoso.
 * @param programa Puntero al programa.
 */
void revalidar_punteros_eventos(Programa *programa);

/**
 * @brief Revalida los punteros Evento.sitio tras un realloc en lista_sitios.
 * @details Debe llamarse despues de cualquier agregar_sitio exitoso.
 * @param programa Puntero al programa.
 */
void revalidar_punteros_sitios(Programa *programa);

#endif /* PROGRAMA_H */