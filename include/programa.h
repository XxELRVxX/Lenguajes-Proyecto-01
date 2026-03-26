#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "lista_eventos.h"
#include "lista_sitios.h"
#include "lista_facturas.h"
#include "cargar_guardar.h"
#include "config.h"

typedef struct {
    ListaEventos eventos;
    ListaSitios sitios;
    ListaFacturas facturas;
}Programa;

Programa crear_programa();
void liberar_programa(Programa *programa);
int guardar_programa(const Programa *programa);
int cargar_programa(Programa *programa);

#endif //PROGRAMA_H