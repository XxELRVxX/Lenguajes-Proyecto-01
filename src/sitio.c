/**
 * @file sitio.c
 * @brief Implementacion de las funciones para el manejo de sitios.
 */

#include "sitio.h"


/**
 * @brief Crea un sitio con los datos proporcionados.
 * @param nombre Nombre del sitio.
 * @param ubicacion Ubicacion del sitio.
 * @param sitio_web Sitio web del lugar.
 * @return Sitio inicializado.
 */
Sitio crear_sitio(const char *nombre, const char *ubicacion, const char *sitio_web) {
    Sitio sitio;

    sitio.nombre = malloc(strlen(nombre) + 1);
    strcpy(sitio.nombre, nombre);

    sitio.ubicacion = malloc(strlen(ubicacion) + 1);
    strcpy(sitio.ubicacion,ubicacion);

    if (sitio_web != NULL) {
        sitio.sitio_web = malloc(strlen(sitio_web) + 1);
        strcpy(sitio.sitio_web, sitio_web);
    } else {
        sitio.sitio_web = NULL;
    }
    
    sitio.lista_sectores = crear_lista_sectores();
    return sitio;  
}

/**
 * @brief Libera la memoria asociada a un sitio.
 * @param sitio Puntero al sitio a liberar.
 */
void liberar_sitio(Sitio *sitio) {
    if (sitio->nombre) {
        free(sitio->nombre);
        sitio->nombre = NULL;
    }
    if (sitio->ubicacion) {
        free(sitio->ubicacion);
        sitio->ubicacion = NULL;
    }
    if (sitio->sitio_web) {
        free(sitio->sitio_web);
        sitio->sitio_web = NULL;
    }

    liberar_lista_sectores(&sitio->lista_sectores);
}

/**
 * @brief Muestra la informacion del sitio.
 * @param sitio Puntero constante al sitio.
 */
void mostrar_sitio(const Sitio *sitio) {
    printf("Sitio: %s | Ubicación: %s | Web: %s\n",
           sitio->nombre,sitio->ubicacion,sitio->sitio_web ? sitio->sitio_web : "N/A");
    mostrar_lista_sectores(&sitio->lista_sectores);
}

/**
 * @brief Cuenta la cantidad total de asientos en el sitio.
 * @param sitio Puntero constante al sitio.
 * @return Cantidad total de asientos.
 */
int contar_asientos_sitio(const Sitio *sitio) {
    int total = 0;
    for (int i = 0; i < sitio->lista_sectores.cantidad_sectores; i++) {
        total += sitio->lista_sectores.sectores[i].asientos.cantidad_asientos;
    }
    return total;
}
