#ifndef FACTURA_H
#define FACTURA_H

#include "fecha.h"
#include "evento.h"
#include "lista_asientos.h"

typedef struct {
    char *numero_asiento;
    float costo;
} FacturaDetalleAsiento;

typedef struct {
    int id;
    Fecha fecha_compra;
    char *cliente_cedula;
    char *cliente_nombre;
    Evento *evento;
    FacturaDetalleAsiento *asientos;
    int cantidad_asientos;
    float subtotal;
    float costo_servicio;
    float total;
} Factura;

Factura crear_factura(Evento *evento, const Fecha *fecha_compra,
                      const char *cliente_cedula, const char *cliente_nombre,
                      const ListaAsientos *asientos_comprados);

void mostrar_factura(const Factura *factura);
void liberar_factura(Factura *factura);

#endif // FACTURA_H
