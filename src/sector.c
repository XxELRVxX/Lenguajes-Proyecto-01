/**
 * @file sector.c
 * @brief Implementacion de las funciones para el manejo de sectores.
 */

#include "sector.h"

/**
 * @brief Crea un sector con los datos proporcionados.
 * @param nombre_sector Nombre del sector.
 * @param cantidad Cantidad de asientos.
 * @param inicial Inicial del sector.
 * @return Sector inicializado.
 */
Sector crear_sector(const char *nombre_sector, int cantidad_asientos, char inicial) {
    Sector sector;
    sector.nombre = malloc(strlen(nombre_sector) + 1);
    strcpy(sector.nombre,nombre_sector);
    sector.inicial = inicial;
    sector.cantidad_asientos = cantidad_asientos;
    sector.asientos = crear_lista_asientos(cantidad_asientos,inicial);

    return sector;
}


/**
 * @brief Libera la memoria asociada a un sector.
 * @param sector Puntero al sector a liberar.
 */
void liberar_sector(Sector *sector) {
    if (sector->nombre) {
        free(sector->nombre);
        sector->nombre = NULL;
    }
    liberar_lista_asientos(&sector->asientos);
    sector->cantidad_asientos = 0;
    sector->inicial = '\0';
}


/**
 * @brief Resetea el sector a su estado inicial.
 * @param sector Puntero al sector a resetear.
 */
void resetear_sector(Sector *sector) {
    resetear_lista_asientos(&sector->asientos);
}

/**
 * @brief Muestra la informacion del sector.
 * @param sector Puntero constante al sector.
 */
void mostrar_sector(const Sector *sector) {
    printf("Sector: %s | Inicial: %c | Cantidad de asientos: %d\n",
    sector->nombre, sector->inicial, sector->cantidad_asientos);
    mostrar_lista_asientos(&sector->asientos);    
}