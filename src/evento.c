/**
 * @file evento.c
 * @brief Implementación de las funciones para el manejo de eventos.
 */

#include "evento.h"


/**
 * @brief Crea un evento.
 * @param nombre_evento Nombre del evento.
 * @param productora Productora del evento.
 * @param fecha Fecha del evento.
 * @param sitio Sitio donde se realiza el evento.
 * @return Evento inicializado.
 */
Evento crear_evento(const char *nombre, const char *productora, Fecha fecha, Sitio *sitio) {
    Evento evento;
    evento.nombre_evento = malloc(strlen(nombre) + 1);
    strcpy(evento.nombre_evento,nombre);
    evento.productora = malloc(strlen(productora) + 1);
    strcpy(evento.productora, productora);
    evento.fecha = fecha;
    evento.sitio = sitio;

    evento.cantidad_sectores = evento.sitio->lista_sectores.cantidad_sectores;
    evento.montos_por_sector = malloc(evento.cantidad_sectores* sizeof(float));
    for (int i = 0; i < evento.cantidad_sectores; i++) {
        evento.montos_por_sector[i] = 0.0f;
    }

    evento.asientos_por_sector = malloc(evento.cantidad_sectores * sizeof(ListaAsientos));
    for (int i = 0; i<evento.cantidad_sectores; i++) {
        evento.asientos_por_sector[i] = copiar_lista_asientos(&sitio->lista_sectores.sectores[i].asientos);
    }
    return evento;
}

/**
 * @brief Libera la memoria asociada a un evento.
 * @param evento Puntero al evento a liberar.
 */
void liberar_evento(Evento *evento) {
    if(evento->nombre_evento) {
        free(evento->nombre_evento);
    }
    if(evento->productora) {
        free(evento->productora);
    }
    if(evento->montos_por_sector) {
        free(evento->montos_por_sector);
    }

    if (evento->asientos_por_sector) {
        for (int i = 0; i < evento->cantidad_sectores; i++) {
            liberar_lista_asientos(&evento->asientos_por_sector[i]);
        }
        free(evento->asientos_por_sector);
    }
    evento->cantidad_sectores = 0;
    evento->sitio = NULL;

}

/**
 * @brief Muestra el estado del evento.
 * @param evento Puntero constante al evento.
 */
void estado_evento(const Evento *evento) {
    printf("Estado del evento '%s':\n", evento->nombre_evento);
    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        ListaAsientos *lista = &evento->asientos_por_sector[i];

        int disponibles = contar_asientos_disponibles(lista);
        int total = lista->cantidad_asientos;
        int vendidos = total - disponibles;
        float recaudado = vendidos * evento->montos_por_sector[i];

        printf("  Sector: %s | Precio: %.2f | Vendidos: %d | Disponibles: %d | Recaudado: %.2f\n",
               sector->nombre,
               evento->montos_por_sector[i],
               vendidos,
               disponibles,
               recaudado);

        mostrar_lista_asientos(lista); 
    }
}

/**
 * @brief Muestra la informacion del evento.
 * @param evento Puntero constante al evento.
 */
void mostrar_evento(const Evento *evento) {                                        
    printf("Evento: %s | Productora: %s | Fecha: ", evento->nombre_evento, evento->productora);
    mostrar_fecha(&evento->fecha);
    printf(" | Sitio: %s\n", evento->sitio->nombre);
    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        printf("  Sector: %s | Precio por asiento: %.2f\n",
               sector->nombre,
               evento->montos_por_sector[i]);
    }
}


/**
 * @brief Obtiene el precio de un asiento segun el sector.
 * @param evento Puntero constante al evento.
 * @param asiento Puntero constante al asiento.
 * @return Precio del asiento.
 */
float obtener_precio_asiento(const Evento *evento, const Asiento *asiento) { 
    char inicial = asiento->numero_asiento[0];
    for (int i = 0; i<evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        if (sector->inicial == inicial) {
            return evento->montos_por_sector[i];
        }
    }
    return 0.0f;
}