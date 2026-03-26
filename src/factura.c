#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factura.h"
#include "config.h"
#include "lista_asientos.h"

static int factura_id_global = 1;

Factura crear_factura(Evento *evento, const Fecha *fecha_compra,
                      const char *cliente_cedula, const char *cliente_nombre,
                      const ListaAsientos *asientos_comprados) {
    Factura factura;
    factura.id = factura_id_global++;
    factura.fecha_compra = *fecha_compra;

    factura.cliente_cedula = strdup(cliente_cedula);
    factura.cliente_nombre = strdup(cliente_nombre);

    factura.evento = evento;
    factura.cantidad_asientos = asientos_comprados->cantidad_asientos;
    factura.asientos = malloc(sizeof(FacturaDetalleAsiento) * factura.cantidad_asientos);

    factura.subtotal = 0.0f;

    for (int i = 0; i < factura.cantidad_asientos; i++) {
        Asiento *asiento = obtener_asiento(asientos_comprados, i);

        factura.asientos[i].numero_asiento = strdup(asiento->numero_asiento);
        factura.asientos[i].costo = obtener_precio_asiento(evento, asiento);

        factura.subtotal += factura.asientos[i].costo;
    }

    factura.costo_servicio = factura.subtotal * COSTO_SERVICIO_PORC;
    factura.total = factura.subtotal + factura.costo_servicio;

    return factura;
}


void mostrar_factura(const Factura *factura) {
    printf("Factura #%d\n", factura->id);
    printf("Fecha de compra: %02d/%02d/%04d\n", factura->fecha_compra.dia, factura->fecha_compra.mes, factura->fecha_compra.anio);
    printf("Cliente: %s (%s)\n", factura->cliente_nombre, factura->cliente_cedula);
    printf("Evento: %s | Productora: %s | Sitio: %s\n", factura->evento->nombre_evento, factura->evento->productora, factura->evento->sitio->nombre);
    printf("Detalle de asientos:\n");
    for (int i = 0; i < factura->cantidad_asientos; i++) {
        printf("  %s -> %.2f\n", factura->asientos[i].numero_asiento, factura->asientos[i].costo);
    }
    printf("Subtotal: %.2f\n", factura->subtotal);
    printf("Costo de servicio (5%%): %.2f\n", factura->costo_servicio);
    printf("Total: %.2f\n", factura->total);
}

void liberar_factura(Factura *factura) {
    if (!factura) return;

    for (int i = 0; i < factura->cantidad_asientos; i++) {
        free(factura->asientos[i].numero_asiento);
    }
    free(factura->asientos);
    factura->asientos = NULL;

    free(factura->cliente_cedula);
    free(factura->cliente_nombre);

    factura->cantidad_asientos = 0;
    factura->subtotal = 0.0f;
    factura->costo_servicio = 0.0f;
    factura->total = 0.0f;
    factura->evento = NULL;
}
