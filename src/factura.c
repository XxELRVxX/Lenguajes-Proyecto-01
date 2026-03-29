/**
 * @file factura.c
 * @brief Implementacion de las funciones para el manejo de facturas.
 */
#include "factura.h"

static int factura_id_global = 1;

/**
 * @brief Crea una factura a partir de los datos proporcionados.
 * @param evento Puntero al evento.
 * @param fecha_compra Puntero a la fecha de compra.
 * @param cliente_cedula Cedula del cliente.
 * @param cliente_nombre Nombre del cliente.
 * @param asientos_comprados Puntero a la lista de asientos comprados.
 * @return Factura inicializada.
 */
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

/**
 * @brief Muestra la informacion de la factura.
 * @param factura Puntero constante a la factura.
 */
void mostrar_factura(const Factura *factura) {
    printf("+-------------------------------------------------+\n");
    printf("  Factura #%d\n", factura->id);
    printf("  Fecha de compra : %02d/%02d/%04d\n",
           factura->fecha_compra.dia, factura->fecha_compra.mes, factura->fecha_compra.anio);
    printf("  Cliente         : %s (%s)\n",
           factura->cliente_nombre, factura->cliente_cedula);
    printf("  Evento          : %s\n", factura->evento->nombre_evento);
    printf("  Productora      : %s\n", factura->evento->productora);
    printf("  Sitio           : %s\n", factura->evento->sitio->nombre);
    printf("  Asientos:\n");
    for (int i = 0; i < factura->cantidad_asientos; i++) {
        printf("    Asiento : %s  $%.2f\n",
               factura->asientos[i].numero_asiento, factura->asientos[i].costo);
    }
    printf("  -----------------------------------------------\n");
    printf("  Subtotal        : $%.2f\n", factura->subtotal);
    printf("  Costo servicio  : $%.2f (5%%)\n", factura->costo_servicio);
    printf("  Total           : $%.2f\n", factura->total);
    printf("+-------------------------------------------------+\n");
}

/**
 * @brief Libera la memoria asociada a una factura.
 * @param factura Puntero a la factura a liberar.
 */
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

/**
 * @brief Sincroniza el contador global de ids con el valor correcto.
 * @param max_id El ID mas alto conocido.
 */
void sincronizar_factura_id(int max_id) {
    if (max_id >= factura_id_global) {
        factura_id_global = max_id + 1;
    }
}
