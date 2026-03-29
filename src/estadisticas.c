/**
 * @file estadisticas.c
 * @brief Implementacion de funciones de estadisticas del programa.
 */

#include "estadisticas.h"

typedef struct {
    int mes;
    int anio;
    int conteo;
} ParMesAnio;

/**
 * @brief Obtener el nombre del mes segun su numero.
 * @param mes el numero del mes
 * @return el nombre del mes al que corresponde el numero
 */
static const char *nombre_mes(int mes) {
    static const char *nombres[] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    if (mes < 1 || mes > 12) return "?";
    return nombres[mes];
}



static int comparar_par_mes_anio(const void *a, const void *b) {
    const ParMesAnio *par_a = (const ParMesAnio *)a;
    const ParMesAnio *par_b = (const ParMesAnio *)b;
    return par_b->conteo - par_a->conteo; 
}

static int comparar_anio_desc(const void *a, const void *b) {
    return *(const int *)b - *(const int *)a;
}

/**
 * @brief Muestra el top 3 de meses con mas eventos, agrupado por año.
 */
static void top3_mes_anio_con_mas_eventos(const Programa *programa) {
    if (programa->eventos.cantidad_eventos == 0) {
        printf("No hay eventos registrados.\n");
        return;
    }

    int cantidad_eventos = programa->eventos.cantidad_eventos;
    ParMesAnio pares[cantidad_eventos];
    int cantidad_pares = 0;

    for (int i = 0; i < cantidad_eventos; i++) {
        int mes_evento  = programa->eventos.eventos[i].fecha.mes;
        int anio_evento = programa->eventos.eventos[i].fecha.anio;

        int encontrado = 0;
        for (int j = 0; j < cantidad_pares; j++) {
            if (pares[j].mes == mes_evento && pares[j].anio == anio_evento) {
                pares[j].conteo++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            pares[cantidad_pares].mes = mes_evento;
            pares[cantidad_pares].anio = anio_evento;
            pares[cantidad_pares].conteo = 1;
            cantidad_pares++;
        }
    }

    int anios[cantidad_pares];
    int cantidad_anios = 0;
    for (int i = 0; i < cantidad_pares; i++) {
        int encontrado = 0;
        for (int j = 0; j < cantidad_anios; j++) {
            if (anios[j] == pares[i].anio) { encontrado = 1; break; }
        }
        if (!encontrado) anios[cantidad_anios++] = pares[i].anio;
    }

    qsort(anios, cantidad_anios, sizeof(int), comparar_anio_desc);

    printf("Top 3 meses con mas eventos por anio:\n");
    printf("=====================================\n");
    for (int a = 0; a < cantidad_anios; a++) {
        printf("\n  %d:\n", anios[a]);

        ParMesAnio *meses_anio = malloc(cantidad_pares * sizeof(ParMesAnio));
        int cantidad_meses = 0;
        for (int i = 0; i < cantidad_pares; i++) {
            if (pares[i].anio == anios[a]) {
                meses_anio[cantidad_meses++] = pares[i];
            }
        }

        qsort(meses_anio, cantidad_meses, sizeof(ParMesAnio), comparar_par_mes_anio);

        int top = cantidad_meses < 3 ? cantidad_meses : 3;
        for (int i = 0; i < top; i++) {
            printf("    %s : %d evento%s\n",
                nombre_mes(meses_anio[i].mes),
                meses_anio[i].conteo,
                meses_anio[i].conteo == 1 ? "" : "s");
        }
        free(meses_anio);
    }
    printf("\n");
}


typedef struct {
    const char *nombre;
    float recaudacion;
} EntradaProductora;

static int comparar_productora_desc(const void *a, const void *b) {
    const EntradaProductora *pa = (const EntradaProductora *)a;
    const EntradaProductora *pb = (const EntradaProductora *)b;
    if (pb->recaudacion > pa->recaudacion) {
        return  1;
    }
    if (pb->recaudacion < pa->recaudacion) {
        return -1;
    }
    return 0;
}

/**
 * @brief Muestra el top 3 de productoras con mas recaudacion por venta de boletos.
 */
static void top3_productoras_por_recaudacion(const Programa *programa) {
    if (programa->facturas.cantidad_facturas == 0) {
        printf("No hay facturas registradas.\n");
        return;
    }

    int cantidad_facturas = programa->facturas.cantidad_facturas;
    EntradaProductora productoras[cantidad_facturas];
    int cantidad_productoras = 0;

    for (int i = 0; i < cantidad_facturas; i++) {
        const Factura *f = &programa->facturas.facturas[i];
        if (f->evento == NULL) continue;
        const char *nombre = f->evento->productora;

        int encontrado = 0;
        for (int j = 0; j < cantidad_productoras; j++) {
            if (strcmp(productoras[j].nombre, nombre) == 0) {
                productoras[j].recaudacion += f->total;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            productoras[cantidad_productoras].nombre = nombre;
            productoras[cantidad_productoras].recaudacion = f->total;
            cantidad_productoras++;
        }
    }

    qsort(productoras, cantidad_productoras, sizeof(EntradaProductora), comparar_productora_desc);

    int top = cantidad_productoras < 3 ? cantidad_productoras : 3;
    printf("Top %d productoras por recaudacion:\n", top);
    printf("==========================================\n");
    for (int i = 0; i < top; i++) {
        printf("  %d. %s\n", i + 1, productoras[i].nombre);
        printf("     Recaudado : $%.2f\n", productoras[i].recaudacion);
        if (i < top - 1)
            printf("     - - - - - - - - - - - - - - - -\n");
    }
    printf("\n");
}


typedef struct {
    const char *nombre_sitio;
    int cantidad_eventos;
    float recaudacion;
} EntradaSitio;

static int comparar_sitio_desc(const void *a, const void *b) {
    const EntradaSitio *sa = (const EntradaSitio *)a;
    const EntradaSitio *sb = (const EntradaSitio *)b;
    if (sb->recaudacion > sa->recaudacion) return  1;
    if (sb->recaudacion < sa->recaudacion) return -1;
    return 0;
}

/**
 * @brief Lista los sitios con cantidad de eventos y monto total recaudado.
 */
static void listado_sitios_por_recaudacion(const Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        return;
    }

    int cantidad_sitios = programa->sitios.cantidad;
    EntradaSitio entradas[cantidad_sitios];

    for (int i = 0; i < cantidad_sitios; i++) {
        entradas[i].nombre_sitio    = programa->sitios.sitios[i].nombre;
        entradas[i].cantidad_eventos = 0;
        entradas[i].recaudacion     = 0.0f;
    }

    for (int e = 0; e < programa->eventos.cantidad_eventos; e++) {
        const char *nombre = programa->eventos.eventos[e].sitio->nombre;
        for (int i = 0; i < cantidad_sitios; i++) {
            if (strcmp(entradas[i].nombre_sitio, nombre) == 0) {
                entradas[i].cantidad_eventos++;
                break;
            }
        }
    }

    for (int f = 0; f < programa->facturas.cantidad_facturas; f++) {
        const Factura *fac = &programa->facturas.facturas[f];
        if (fac->evento == NULL) continue;
        const char *nombre = fac->evento->sitio->nombre;
        for (int i = 0; i < cantidad_sitios; i++) {
            if (strcmp(entradas[i].nombre_sitio, nombre) == 0) {
                entradas[i].recaudacion += fac->total;
                break;
            }
        }
    }

    qsort(entradas, cantidad_sitios, sizeof(EntradaSitio), comparar_sitio_desc);

    printf("Sitios de eventos (mayor a menor recaudacion):\n");
    printf("==============================================\n");
    for (int i = 0; i < cantidad_sitios; i++) {
        printf("  Sitio: %s - Num de eventos: %d  - Recaudado: $ %.2f\n",
            entradas[i].nombre_sitio,
            entradas[i].cantidad_eventos,
            entradas[i].recaudacion);
    }
    printf("\n");
}

/**
 * @brief Muestra el submenu de estadisticas.
 * @param programa Puntero al programa.
 */
void estadisticas(Programa *programa) {
    int opcion;
    do {
        limpiar_consola();
        printf("==== Estadisticas ====\n\n");
        printf("1. Top 3 mes-anio con mas eventos\n");
        printf("2. Top 3 productoras por recaudacion\n");
        printf("3. Listado de sitios con eventos y recaudacion\n");
        printf("4. Volver\n");
        printf("\nSeleccione una opcion: ");
        opcion = leer_opcion();
        limpiar_consola();
        switch (opcion) {
            case 1:
                top3_mes_anio_con_mas_eventos(programa);
                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            case 2:
                top3_productoras_por_recaudacion(programa);
                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            case 3:
                listado_sitios_por_recaudacion(programa);
                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            case 4:
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    } while (opcion != 4);
}
