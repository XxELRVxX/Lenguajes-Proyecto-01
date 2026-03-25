#ifndef FECHA_H
#define FECHA_H

#include "config.h"


typedef enum {
    ENERO = 1, FEBRERO, MARZO, ABRIL, MAYO, JUNIO,
    JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE
} Mes;


typedef struct {
    int dia;
    int mes;
    int anio;
}Fecha;

Fecha crear_fecha(int dia, int mes, int anio);
int validar_fecha(int dia, int mes, int anio);
void mostrar_fecha(const Fecha *fecha);
int comparar_fechas(const Fecha*fecha1, const Fecha *Fecha2);

#endif //FECHA_H