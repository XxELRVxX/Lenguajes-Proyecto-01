#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asiento.h"
#include "cargar_guardar.h"
#include "config.h"
#include "evento.h"
#include "factura.h"
#include "fecha.h"
#include "lista_asientos.h"
#include "lista_eventos.h"
#include "lista_sectores.h"
#include "lista_facturas.h"
#include "lista_sitios.h"
#include "programa.h"
#include "sector.h"
#include "sitio.h"
#include "usuario.h"

void inicioSesion();
void menu();
void menuGSE();
void menuGESE();
void menuGE();
void menuEE();
void menuLF();

int main() {
    inicioSesion();
    return 0;
}

void menu() {
    printf("¡Gestion de eventos!\n");
    printf("Ingrese una opcion: \n");
    printf("1. Gestión de Sitios de Eventos\n");
    printf("2. Gestión de Espacios Sitio de Eventos\n");
    printf("3. Gestión de Eventos\n");
    printf("4. Estado de evento\n");
    printf("5. Lista de facturas\n");
    printf("6. General\n");
    printf("Volver\n");
    int opc;
    scanf("%d", &opc);
    switch(opc) {
        case 1:
            menuGSE();
            break;
        case 2:
            menuGESE();
            break;
        case 3:
            menuGE();
            break;
        case 4:
            menuEE();
            break;
        case 5:
            menuLF();
            break;
        case 6:
            inicioSesion();
            break;
    }
}

void inicioSesion() {
    FILE *arch;
    arch = fopen("Usuarios.txt", "w");
    //if (arch == NULL) {
    //    return 1;
    //}
    char* usuario = (char*) malloc(50 * sizeof(char));
    char* contrasena = (char*) malloc(50 * sizeof(char));
    
    printf("Ingrese su usuario:\n");
    scanf("%49s", usuario);
    printf("Ingrese una contraseña:\n");
    scanf("%49s", contrasena);
    char *linea = (char*) malloc(strlen(usuario)+strlen(contrasena) + 2);
    strcpy(linea ,usuario);
    strcat(linea, ";");
    strcat(linea, contrasena);
    fputs(linea, arch);

    if (strlen(usuario) > 0 && strlen(contrasena) > 0) {
        menu();

    } else {
        printf("Contraseña o Usuario vacio, ingrese denuevo");
        inicioSesion();

    }
    free(usuario);
    free(contrasena);
    free(linea);
    fclose(arch);
}

void menuGSE() {
    printf("Carga en lote\n");
    printf("Indique la ruta del archivo:\n");
    
    char *ruta = (char*) malloc(256 * sizeof(char));
    if (ruta == NULL) return;
    char **array = (char**) malloc(10 * sizeof(char*));
    if (array == NULL) { free(ruta); return;}
    char *linea = (char*) malloc(50 * sizeof(char));
    if (linea == NULL) { free(ruta); free(array); return;}
    
    FILE *arch = NULL; 

    while (!arch) {
        printf("Ruta no encontrada, intente denuevo...\n");
        scanf("%255s", ruta);
        arch = fopen(ruta, "r");
        if (!arch) printf ("No trunca");
        printf("[%s]\n", ruta);
    }

    printf("Ruta hallada, extrayendo informacion...\n");
    int i = 0;
    while (fgets(linea, 50, arch) && i < 10) {
        linea[strcspn(linea, "\n")] = '\0';
        char *cursor = strtok(linea, ",");
        
        while (cursor != NULL && i < 10) {
            array[i] = strdup(cursor);
            cursor = strtok(NULL, ",");
            i++;
        }
    }

    fclose(arch);
    
    Sitio sitio;
    sitio.nombre = array[0];
    sitio.ubicacion = array[1];
    sitio.sitio_web = array[2];

    for (int fila = 0; fila < 10; fila++) {
        free(array[fila]);
    }

    free(ruta);
    free(array);
    free(linea);
    menu();
}

void menuGESE() {
    printf("Gestion de Espacios de Sitios de Eventos\n");
    
}

void menuGE() {
    printf("Gestion de eventos\n");
    printf("Indique el nombre del evento:\n");
    char *nombre = (char*) malloc(50 * sizeof(char));
    char *productora = (char*) malloc(100 * sizeof(char));
    char *fecha = (char*) malloc(11 * sizeof(char));
    if (nombre == NULL || productora == NULL || fecha == NULL) return;
    scanf("%99s", nombre);
    if (strlen(nombre) > 0) {
        printf("Indique el productora del evento:\n");
        
        scanf("%99s", productora);
        if (strlen(productora) > 0) { 
 
            printf("Indique la fecha del evento (formato: d\\m\\a):\n");
            
            scanf("%10s", fecha);
            
            //if (fecha != "") {
            //}
        } else {
            free(nombre); free(productora); free(fecha);
            menuGE();
            return;
        }      
    } else {
        free(nombre); free(productora); free(fecha);
        menuGE();
        return;
    }
    free(nombre); free(productora); free(fecha);
    
}

void menuEE() {
    printf("Estado de eventos\n");
    printf("Elija el evento a consultar:\n");
}

void menuLF() {
    printf("Lista de facturas");
}