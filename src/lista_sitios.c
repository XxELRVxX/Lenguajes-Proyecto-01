#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_sitios.h"
#include "config.h"


ListaSitios crear_lista_sitios() {
    ListaSitios lista;
    lista.cantidad = 0;
    lista.sitios = NULL;

    return lista;
}

int agregar_sitio(ListaSitios *lista_sitios, Sitio *nuevo_sitio) {
    if (buscar_sitio(lista_sitios, nuevo_sitio->nombre) != NULL) {
        liberar_sitio(nuevo_sitio);
        return OPERACION_FALLIDA_DUPLICADO; 
    }

    Sitio *temp_lista_sitios = realloc(lista_sitios->sitios, (lista_sitios->cantidad + 1) * sizeof(Sitio));
    if (temp_lista_sitios == NULL) {
        liberar_sitio(nuevo_sitio);
        return OPERACION_FALLIDA_MEMORIA; 
    }

    lista_sitios->sitios = temp_lista_sitios;
    lista_sitios->sitios[lista_sitios->cantidad] = *nuevo_sitio;
    lista_sitios->cantidad++;

    return OPERACION_EXITOSA;
}



void liberar_lista_sitios(ListaSitios *lista_sitios) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        liberar_sitio(&lista_sitios->sitios[i]);
    }

    free(lista_sitios->sitios);
    lista_sitios->sitios = NULL;
    lista_sitios->cantidad = 0;
}


Sitio *buscar_sitio(ListaSitios *lista_sitios, const char *nombre_sitio) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        if (strcmp(lista_sitios->sitios[i].nombre,nombre_sitio) == 0) {
            return &lista_sitios->sitios[i];
        }
    }
    return NULL;
}

int cargar_sitios_por_lote(ListaSitios *lista_sitios, const char *ruta_archivo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[LARGO_MAXIMO_CARACTERES];
    while (fgets(linea,sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';

        char *nombre = strtok(linea, ",");
        char *ubicacion = strtok(NULL,",");
        char *sitio_web = strtok(NULL,",");

        if (nombre && ubicacion) {
            Sitio nuevo_sitio = crear_sitio(nombre,ubicacion,sitio_web);
            int resultado = agregar_sitio(lista_sitios, &nuevo_sitio);
            if (resultado == OPERACION_EXITOSA) {
                printf("Exito: El sitio '%s' se ha agregado con exito.\n", nombre);
            } else if (resultado == OPERACION_FALLIDA_DUPLICADO) {
                printf("Fallo: Ya existe un sitio llamado '%s'.\n", nombre);
            } else if (resultado == OPERACION_FALLIDA_MEMORIA) {
                printf("Fallo: Ocurrio un error al reservar la memoria del sito '%s'.\n", nombre);
            }  
        } 
    }
    fclose(archivo);
    return OPERACION_EXITOSA;
}