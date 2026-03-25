#ifndef EVENTO_H
#define EVENTO_H

#include "fecha.h"
#include "sitio.h"

typedef struct {
    char *nombre_evento;
    char *productora;
    Fecha fecha;
    Sitio *sitio;
    float *montos_por_sector;
    int cantidad_sectores;
}Evento;

Evento crear_evento(const char *nombre_evento, const char* productora,
     Fecha fecha, Sitio *sitio);

void liberar_evento(Evento *evento);
void estado_evento(const Evento *evento);
void mostrar_evento(const Evento *evento);

#endif //EVENTO_H