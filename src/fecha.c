#include <stdio.h>
#include "fecha.h"

Fecha crear_fecha(int dia, int mes, int anio) {
    Fecha fecha;
    fecha.dia = dia;
    fecha.mes = mes;
    fecha.anio = anio;
    return fecha;
}

int validar_fecha(int dia, int mes, int anio) {
    if (anio < ANIO_MINIMO) {
        return FECHA_INVALIDA;
    }
    if (mes < 1 || mes > 12) {
        return FECHA_INVALIDA;
    }

    int dias_en_mes;
    switch(mes) {
        case ENERO: case MARZO: case MAYO: case JULIO:
        case AGOSTO: case OCTUBRE: case DICIEMBRE:
            dias_en_mes = 31;
            break;
        case ABRIL: case JUNIO: case SEPTIEMBRE: case NOVIEMBRE:
            dias_en_mes = 30;
            break;
        case FEBRERO:
            if (anio % 400 == 0 || (anio % 4 == 0 && anio % 100 != 0)) {
                dias_en_mes = 29;
            } else {
                dias_en_mes = 28;
            }
            break;
    }

    if (dia < 1 || dia > dias_en_mes) {
        return FECHA_INVALIDA;
    }
    return FECHA_VALIDA;
}
