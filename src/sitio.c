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
 * @brief Edita los campos de un sitio existente.
 * @param sitio Puntero al sitio a editar.
 * @param nuevo_nombre Nuevo nombre, o cadena vacia para no cambiar.
 * @param nueva_ubicacion Nueva ubicacion, o cadena vacia para no cambiar.
 * @param nuevo_sitio_web Nuevo sitio web, NULL para eliminar, cadena vacia para no cambiar.
 */
void editar_sitio(Sitio *sitio, const char *nuevo_nombre,
                  const char *nueva_ubicacion, const char *nuevo_sitio_web) {
    if (nuevo_nombre && nuevo_nombre[0] != '\0') {
        free(sitio->nombre);
        sitio->nombre = malloc(strlen(nuevo_nombre) + 1);
        strcpy(sitio->nombre, nuevo_nombre);
    }
    if (nueva_ubicacion && nueva_ubicacion[0] != '\0') {
        free(sitio->ubicacion);
        sitio->ubicacion = malloc(strlen(nueva_ubicacion) + 1);
        strcpy(sitio->ubicacion, nueva_ubicacion);
    }
    if (nuevo_sitio_web == NULL) {
        free(sitio->sitio_web);
        sitio->sitio_web = NULL;
    } else if (nuevo_sitio_web[0] != '\0') {
        free(sitio->sitio_web);
        sitio->sitio_web = malloc(strlen(nuevo_sitio_web) + 1);
        strcpy(sitio->sitio_web, nuevo_sitio_web);
    }
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
    printf("%s | Ubicacion: %s | Web: %s\n",
           sitio->nombre,sitio->ubicacion,sitio->sitio_web ? sitio->sitio_web : "N/A");
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
