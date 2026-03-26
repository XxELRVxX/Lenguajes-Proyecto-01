#include "programa.h"

Programa crear_programa() {
    Programa programa;
    programa.eventos = crear_lista_eventos();
    programa.sitios = crear_lista_sitios();
    programa.facturas = crear_lista_facturas();
    return programa;
}

void liberar_programa(Programa *programa) {
    liberar_lista_eventos(&programa->eventos);
    liberar_lista_sitios(&programa->sitios);
    liberar_lista_facturas(&programa->facturas);
}

int guardar_programa(const Programa *programa) {
    if (guardar_sitios(&programa->sitios, RUTA_ALMACENAMIENTO_SITIOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (guardar_eventos(&programa->eventos, RUTA_ALMACENAMIENTO_EVENTOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (guardar_facturas(&programa->facturas, RUTA_ALMACENAMIENTO_FACTURAS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    return OPERACION_EXITOSA;
}

int cargar_programa(Programa *programa) {
    if (cargar_sitios(&programa->sitios, RUTA_ALMACENAMIENTO_SITIOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (cargar_eventos(&programa->eventos, &programa->sitios, RUTA_ALMACENAMIENTO_EVENTOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (cargar_facturas(&programa->facturas, &programa->eventos, RUTA_ALMACENAMIENTO_FACTURAS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    return OPERACION_EXITOSA;
}
