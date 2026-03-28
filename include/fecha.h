/**
 * @file fecha.h
 * @brief Definicion de la estructura y funciones para el manejo de fechas.
 */

#ifndef FECHA_H
#define FECHA_H

#include <stdio.h>
#include "config.h"


/**
 * @enum Mes
 * @brief Enumeracion de los meses del año.
 */
typedef enum {
    ENERO = 1, FEBRERO, MARZO, ABRIL, MAYO, JUNIO,
    JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE
} Mes;


/**
 * @struct Fecha
 * @brief Estructura que representa una fecha.
 */
typedef struct {
    int dia;   /**< Dia del mes */
    int mes;   /**< Mes del anio */
    int anio;  /**< Año */
} Fecha;

/**
 * @brief Crea una fecha a partir de dia, mes y anio.
 * @param dia Dia del mes.
 * @param mes Mes del año.
 * @param anio Anio.
 * @return Fecha inicializada.
 */
Fecha crear_fecha(int dia, int mes, int anio);

/**
 * @brief Valida si una fecha es correcta.
 * @param dia Dia del mes.
 * @param mes Mes del año.
 * @param anio Año.
 * @return FECHA_VALIDA o FECHA_INVALIDA.
 */
int validar_fecha(int dia, int mes, int anio);

/**
 * @brief Muestra la fecha en formato dia/mes/año.
 * @param fecha Puntero constante a la fecha.
 */
void mostrar_fecha(const Fecha *fecha);

/**
 * @brief Compara dos fechas.
 * @param fecha1 Puntero constante a la primera fecha.
 * @param fecha2 Puntero constante a la segunda fecha.
 * @return Diferencia: 0 si son iguales, negativo si fecha1 < fecha2, positivo si fecha1 > fecha2.
 */
int comparar_fechas(const Fecha*fecha1, const Fecha *Fecha2);

#endif //FECHA_H