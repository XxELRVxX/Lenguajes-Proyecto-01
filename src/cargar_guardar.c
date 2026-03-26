#include "cargar_guardar.h"

//guardar
int guardar_sitios(const ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta,"w");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    for (int i = 0; i < lista_sitios->cantidad; i++) {
        Sitio *sitio = &lista_sitios->sitios[i];
        fprintf(archivo, "%s|%s|", sitio->nombre, sitio->ubicacion);

        if (sitio->sitio_web && strlen(sitio->sitio_web) > 0) {
            fprintf(archivo, "%s", sitio->sitio_web);
        }

        for (int j = 0; j < sitio->lista_sectores.cantidad_sectores; j++) {
            Sector *sector = &sitio->lista_sectores.sectores[j];
            fprintf(archivo, ",SECTOR|%s|%c|%d",
                    sector->nombre,
                    sector->inicial,
                    sector->cantidad_asientos);
        }

        fprintf(archivo, "\n");
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

int guardar_eventos(const ListaEventos *lista_eventos, const char *ruta) {
    FILE *archivo = fopen(ruta, "w");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    for (int i = 0; i < lista_eventos->cantidad_eventos; i++) {
        Evento *evento = &lista_eventos->eventos[i];

        fprintf(archivo, "%s|%s|%02d/%02d/%04d|%s",
                evento->nombre_evento,
                evento->productora,
                evento->fecha.dia,
                evento->fecha.mes,
                evento->fecha.anio,
                evento->sitio->nombre);

        for (int j = 0; j < evento->cantidad_sectores; j++) {
            Sector *sector = &evento->sitio->lista_sectores.sectores[j];
            fprintf(archivo, ",SECTOR|%s|%c|%d|%.2f",
                    sector->nombre,
                    sector->inicial,
                    sector->cantidad_asientos,
                    evento->montos_por_sector[j]);
            
            ListaAsientos *lista = &evento->asientos_por_sector[j];
            for (int k = 0; k < lista->cantidad_asientos; k++) {
                Asiento *asiento = &lista->asientos[k];
                fprintf(archivo, ",ASIENTO|%s|%d",
                        asiento->numero_asiento,
                        asiento->estado);
            }
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}


int guardar_facturas(const ListaFacturas *lista_facturas, const char *ruta) {
    FILE *archivo = fopen(ruta, "w");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    for (int i = 0; i < lista_facturas->cantidad_facturas; i++) {
        Factura *factura = &lista_facturas->facturas[i];


        fprintf(archivo, "%d|%02d/%02d/%04d|%s|%s|%s",
                factura->id,
                factura->fecha_compra.dia,
                factura->fecha_compra.mes,
                factura->fecha_compra.anio,
                factura->cliente_cedula,
                factura->cliente_nombre,
                factura->evento->nombre_evento);

       
        for (int j = 0; j < factura->cantidad_asientos; j++) {
            fprintf(archivo, ",ASIENTO|%s|%.2f",
                    factura->asientos[j].numero_asiento,
                    factura->asientos[j].costo);
        }

        fprintf(archivo, ",SUBTOTAL|%.2f,COSTO_SERVICIO|%.2f,TOTAL|%.2f",
                factura->subtotal,
                factura->costo_servicio,
                factura->total);

        fprintf(archivo, "\n");
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

#include "cargar_guardar.h"

int cargar_sitios(ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';

        char *token = strtok(linea, ",");
        if (!token) continue;

        char *nombre = strtok(token, "|");
        char *ubicacion = strtok(NULL, "|");
        char *sitio_web = strtok(NULL, "|");

        Sitio nuevo_sitio = crear_sitio(nombre, ubicacion, sitio_web);

        while ((token = strtok(NULL, ",")) != NULL) {
            if (strncmp(token, "SECTOR", 6) == 0) {
                strtok(token, "|"); 
                char *nombre_sector = strtok(NULL, "|");
                char inicial = *strtok(NULL, "|");
                int cantidad_asientos = atoi(strtok(NULL, "|"));

                Sector nuevo_sector = crear_sector(nombre_sector, cantidad_asientos, inicial);
                nuevo_sector.asientos = crear_lista_asientos(cantidad_asientos, inicial);
                agregar_sector(&nuevo_sitio.lista_sectores, &nuevo_sector);
            }
        }
        agregar_sitio(lista_sitios, &nuevo_sitio);
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

#include "cargar_guardar.h"

int cargar_eventos(ListaEventos *lista_eventos, const ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';

        char *token = strtok(linea, ",");
        if (!token) continue;

        char *nombre_evento = strtok(token, "|");
        char *productora = strtok(NULL, "|");
        char *fecha_str = strtok(NULL, "|");
        char *nombre_sitio = strtok(NULL, "|");

        Fecha fecha;
        sscanf(fecha_str, "%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

        Sitio *sitio = buscar_sitio((ListaSitios *)lista_sitios, nombre_sitio);
        if (!sitio) continue;

        Evento nuevo_evento = crear_evento(nombre_evento, productora, fecha, sitio);

        int indice_sector = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            if (strncmp(token, "SECTOR", 6) == 0) {
                strtok(token, "|");
                char *nombre_sector = strtok(NULL, "|");
                char inicial = *strtok(NULL, "|");
                int cantidad_asientos = atoi(strtok(NULL, "|"));
                float monto = atof(strtok(NULL, "|"));

                nuevo_evento.montos_por_sector[indice_sector] = monto;
                ListaAsientos lista_asientos = crear_lista_asientos(cantidad_asientos, inicial);

                for (int i = 0; i < cantidad_asientos; i++) {
                    token = strtok(NULL, ",");
                    if (!token || strncmp(token, "ASIENTO", 7) != 0) break;

                    strtok(token, "|");
                    char *numero_asiento = strtok(NULL, "|");
                    int estado = atoi(strtok(NULL, "|"));

                    Asiento *asiento = buscar_asiento(&lista_asientos, numero_asiento);
                    if (asiento) {
                        asiento->estado = estado;
                    }
                }

                nuevo_evento.asientos_por_sector[indice_sector] = lista_asientos;
                indice_sector++;
            }
        }

        agregar_evento(lista_eventos, &nuevo_evento);
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

int cargar_facturas(ListaFacturas *lista_facturas, const ListaEventos *lista_eventos, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';

        char *token = strtok(linea, ",");
        if (!token) continue;

        char *id_str = strtok(token, "|");
        char *fecha_str = strtok(NULL, "|");
        char *cedula = strtok(NULL, "|");
        char *nombre_cliente = strtok(NULL, "|");
        char *nombre_evento = strtok(NULL, "|");

        int id = atoi(id_str);
        Fecha fecha;
        sscanf(fecha_str, "%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

        Evento *evento = buscar_evento((ListaEventos *)lista_eventos, nombre_evento);
        if (!evento) continue;

        Factura nueva_factura;
        nueva_factura.id = id;
        nueva_factura.fecha_compra = fecha;

        nueva_factura.cliente_cedula = malloc(strlen(cedula) + 1);
        if (nueva_factura.cliente_cedula) {
            strcpy(nueva_factura.cliente_cedula, cedula);
        }

        nueva_factura.cliente_nombre = malloc(strlen(nombre_cliente) + 1);
        if (nueva_factura.cliente_nombre) {
            strcpy(nueva_factura.cliente_nombre, nombre_cliente);
        }

        nueva_factura.evento = evento;
        nueva_factura.asientos = NULL;
        nueva_factura.cantidad_asientos = 0;

        while ((token = strtok(NULL, ",")) != NULL) {
            if (strncmp(token, "ASIENTO", 7) == 0) {
                strtok(token, "|");
                char *numero_asiento = strtok(NULL, "|");
                float costo = atof(strtok(NULL, "|"));

                FacturaDetalleAsiento detalle;

                detalle.numero_asiento = malloc(strlen(numero_asiento) + 1);
                if (detalle.numero_asiento) {
                    strcpy(detalle.numero_asiento, numero_asiento);
                }
                detalle.costo = costo;

                FacturaDetalleAsiento *temp = realloc(nueva_factura.asientos,
                    (nueva_factura.cantidad_asientos + 1) * sizeof(FacturaDetalleAsiento));
                if (!temp) break;

                nueva_factura.asientos = temp;
                nueva_factura.asientos[nueva_factura.cantidad_asientos] = detalle;
                nueva_factura.cantidad_asientos++;
            }
            else if (strncmp(token, "SUBTOTAL", 8) == 0) {
                strtok(token, "|");
                nueva_factura.subtotal = atof(strtok(NULL, "|"));
            }
            else if (strncmp(token, "COSTO_SERVICIO", 14) == 0) {
                strtok(token, "|");
                nueva_factura.costo_servicio = atof(strtok(NULL, "|"));
            }
            else if (strncmp(token, "TOTAL", 5) == 0) {
                strtok(token, "|");
                nueva_factura.total = atof(strtok(NULL, "|"));
            }
        }

        agregar_factura(lista_facturas, &nueva_factura);
    }
    fclose(archivo);
    return OPERACION_EXITOSA;
}




