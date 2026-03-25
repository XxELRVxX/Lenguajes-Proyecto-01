#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"

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
    return evento;
}

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
    evento->cantidad_sectores = 0;
    evento->sitio = NULL;

}

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

void estado_evento(const Evento *evento) {
    printf("Estado del evento '%s':\n", evento->nombre_evento);
    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        int disponibles = contar_asientos_disponibles(&sector->asientos);
        int total = sector->cantidad_asientos;
        int vendidos = total - disponibles;
        float recaudado = vendidos * evento->montos_por_sector[i];

        printf("  Sector: %s | Precio: %.2f | Vendidos: %d | Disponibles: %d | Recaudado: %.2f\n",
               sector->nombre,
               evento->montos_por_sector[i],
               vendidos,
               disponibles,
               recaudado);
        mostrar_lista_asientos(&sector->asientos);
    }
}

float obtener_precio_asiento(const Evento *evento, const Asiento *asiento) { {
    char inicial = asiento->numero_asiento[0];
    for (int i = 0; i<evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        if (sector->inicial == inicial) {
            return evento->montos_por_sector[i];
        }
    }
    return 0.0f;
}

}