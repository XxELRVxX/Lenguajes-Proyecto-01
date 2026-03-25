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

void mostrar_fecha(const Fecha *fecha) {
    printf("%02d/%02d/%04d", fecha->dia, fecha->mes, fecha->anio);
}

int comparar_fechas(const Fecha *fecha1, const Fecha *fecha2) {
    if (fecha1->anio != fecha2->anio) {
        return fecha1->anio - fecha2->anio;
    }
    if (fecha1->mes != fecha2->mes) {
        return fecha1->mes - fecha2->mes;
    }
    return fecha1->dia - fecha2->dia;
}
