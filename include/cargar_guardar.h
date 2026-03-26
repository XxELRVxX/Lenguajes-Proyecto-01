#ifndef CARGAR_GUARDAR_H
#define CARGAR_GUARDAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "lista_sitios.h"
#include "lista_eventos.h"
#include "lista_facturas.h"


//guardar datos
int guardar_sitios(const ListaSitios *lista_sitios, const char *ruta);
int guardar_eventos(const ListaEventos *lista_eventos, const char *ruta);
int guardar_facturas(const ListaFacturas *lista_facturas, const char *ruta);

//Cargar datos
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta);
int cargar_eventos(ListaEventos *lista_eventos, const ListaSitios *lista_sitios, const char *ruta);
int cargar_facturas(ListaFacturas *lista_facturas, const ListaEventos *lista_eventos, const char *ruta);
#endif //CARGAR_GUARDAR_H