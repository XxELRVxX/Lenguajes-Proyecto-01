/**
 * @file fecha.c
 * @brief Implementacion de las funciones para el manejo de fechas.
 */


#include "fecha.h"

/**
 * @file fecha.h
 * @brief Definicion de la estructura y funciones para el manejo de fechas.
 */
Fecha crear_fecha(int dia, int mes, int anio) {
    Fecha fecha;
    fecha.dia = dia;
    fecha.mes = mes;
    fecha.anio = anio;
    return fecha;
}

/**
 * @brief Valida si una fecha es correcta.
 * @param dia Dia del mes.
 * @param mes Mes del anio.
 * @param anio Anio.
 * @return FECHA_VALIDA o FECHA_INVALIDA.
 */
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

/**
 * @brief Muestra la fecha en formato dd/mm/aaaa.
 * @param fecha Puntero constante a la fecha.
 */
void mostrar_fecha(const Fecha *fecha) {
    printf("%02d/%02d/%04d", fecha->dia, fecha->mes, fecha->anio);
}

/**
 * @brief Compara dos fechas.
 * @param fecha1 Puntero constante a la primera fecha.
 * @param fecha2 Puntero constante a la segunda fecha.
 * @return Diferencia: 0 si son iguales, negativo si fecha1 < fecha2, positivo si fecha1 > fecha2.
 */
int comparar_fechas(const Fecha *fecha1, const Fecha *fecha2) {
    if (fecha1->anio != fecha2->anio) {
        return fecha1->anio - fecha2->anio;
    }
    if (fecha1->mes != fecha2->mes) {
        return fecha1->mes - fecha2->mes;
    }
    return fecha1->dia - fecha2->dia;
}
