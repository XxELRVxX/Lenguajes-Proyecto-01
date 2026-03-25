#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asiento.h"
#include "config.h"

Asiento crear_asiento(const char *numero_asiento) {
    Asiento asiento;
    asiento.numero_asiento = malloc(strlen(numero_asiento) + 1);
    strcpy(asiento.numero_asiento,numero_asiento);
    asiento.estado = ASIENTO_DISPONIBLE;
    return asiento;
}

void liberar_asiento(Asiento *asiento) {
    if(asiento->numero_asiento) {
        free(asiento->numero_asiento);
        asiento->numero_asiento = NULL;
    }
}

int vender_asiento(Asiento *asiento) {
    if (asiento->estado == ASIENTO_DISPONIBLE) {
        asiento->estado = ASIENTO_VENDIDO;
        return OPERACION_EXITOSA;
    }
    return OPERACION_FALLIDA; 
}

void desocupar_asiento(Asiento *asiento) {
    asiento->estado = ASIENTO_DISPONIBLE;
}

void informacion_asiento(const Asiento *asiento) {
    printf("    %s ",asiento->numero_asiento);
    if (asiento->estado == ASIENTO_DISPONIBLE) {
        printf("[Disponible] \n");
    } else {
        printf("[Vendido] \n");
    }
}