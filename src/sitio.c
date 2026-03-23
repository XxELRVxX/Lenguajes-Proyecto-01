#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sitio.h"
#include "config.h"

Sitio crear_sitio(const char *nombre, const char *ubicacion, const char *sitio_web) {
    Sitio sitio;

    sitio.nombre = malloc(strlen(nombre) + 1);
    strcpy(sitio.nombre, nombre);

    sitio.ubicacion = malloc(strlen(ubicacion) + 1);
    strcpy(sitio.ubicacion,ubicacion);

    if (sitio_web != NULL) {
        sitio.sitio_web = malloc(strlen(sitio_web) + 1);
        strcpy(sitio.sitio_web, sitio_web);
    } else {
        sitio.sitio_web = NULL;
    }

    return sitio;  
}
void liberar_sitio(Sitio *sitio) {
    if (sitio->nombre) {
        free(sitio->nombre);
    }
    if (sitio->ubicacion) {
        free(sitio->ubicacion);
    }
    if (sitio->sitio_web) {
        free(sitio->sitio_web);
    }
}


ListaSitios crear_lista_sitios() {
    ListaSitios lista;
    lista.cantidad = 0;
    lista.lista_sitios = NULL;

    return lista;
}

void agregar_sitio(ListaSitios *lista_sitios, Sitio nuevo_sitio) {
    if (buscar_sitio(lista_sitios, nuevo_sitio.nombre) != -1) {
        liberar_sitio(&nuevo_sitio);
        return;
    }
    lista_sitios->cantidad++;
    lista_sitios->lista_sitios = realloc(lista_sitios->lista_sitios, lista_sitios->cantidad * sizeof(Sitio));
    lista_sitios->lista_sitios[lista_sitios->cantidad - 1] = nuevo_sitio;

}

void liberar_lista_sitios(ListaSitios *lista_sitios) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        liberar_sitio(&lista_sitios->lista_sitios[i]);
    }

    free(lista_sitios->lista_sitios);
    lista_sitios->lista_sitios = NULL;
    lista_sitios->cantidad = 0;
}


//Discutir si tilde y mayusculas diferencian una palabra. Ej: "Conexión","conexion","conexión"
int buscar_sitio(ListaSitios *lista_sitios, const char *nombre_sitio) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        if (strcmp(lista_sitios->lista_sitios[i].nombre,nombre_sitio) == 0) {
            return OPERACION_EXITOSA;
        }
    }
    return OPERACION_FALLIDA;
}

int cargar_sitios(ListaSitios *lista_sitios, const char *ruta_archivo) {
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
            agregar_sitio(lista_sitios, nuevo_sitio);

        } 
    }
    fclose(archivo);
    return OPERACION_EXITOSA;
}