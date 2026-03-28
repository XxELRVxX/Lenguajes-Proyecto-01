/**
 * @file cargar_guardar.c
 * @brief Implementacion de funciones para cargar y guardar datos del sistema.
 */

#include "cargar_guardar.h"

/**
 * @brief Elimina espacios en blanco al inicio y final de una cadena.
 * @param str Cadena a limpiar.
 */
void trim(char *str) {
    char *final;
    while (*str == ' ' || *str == '\t') {
        str++;
    }
    if (*str == 0) {
        return;
    }

    final = str + strlen(str) - 1;
    while (final > str && (*final == ' ' || *final == '\t')) final--;
    *(final+1) = '\0';
}


/**
 * @brief Guarda la lista de sitios en un archivo.
 * @param lista_sitios Puntero constante a la lista de sitios.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
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

/**
 * @brief Guarda la lista de eventos en un archivo.
 * @param lista_eventos Puntero constante a la lista de eventos.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
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

/**
 * @brief Guarda la lista de facturas en un archivo.
 * @param lista_facturas Puntero constante a la lista de facturas.
 * @param ruta Ruta del archivo donde guardar.
 * @return Codigo de exito o error.
 */
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

/**
 * @brief Carga la lista de sitios desde un archivo.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';
        trim(linea);
        char *pos_cadena = linea;
        
        char nombre[BUFFER_LECTURA_LINEA];
        int i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            nombre[i++] = *pos_cadena++;
        }
        nombre[i] = '\0';
        if (*pos_cadena == '|')  {
            pos_cadena++;
        }

        char ubicacion[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            ubicacion[i++] = *pos_cadena++;
        }
        ubicacion[i] = '\0';
        if (*pos_cadena == '|')  {
            pos_cadena++;
        }

        char sitio_web[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != ',') {
            sitio_web[i++] = *pos_cadena++;
        }
        sitio_web[i] = '\0';
        if (*pos_cadena == ',')  {
            pos_cadena++;
        }

        Sitio nuevo_sitio = crear_sitio(nombre, ubicacion, sitio_web);

        while (*pos_cadena) {
            if (strncmp(pos_cadena, "SECTOR|", 7) == 0) {
                char token_sector[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_cadena && *pos_cadena != ',' && i < BUFFER_LECTURA_LINEA - 1) {
                    token_sector[i++] = *pos_cadena++;
                }
                token_sector[i] = '\0';
                if (*pos_cadena == ',')  {
                    pos_cadena++;
                }

                char *pos_token = token_sector;
                pos_token += 7;

                
                char nombre_sector[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_token && *pos_token != '|') {
                    nombre_sector[i++] = *pos_token++;
                }
                nombre_sector[i] = '\0';
                if (*pos_token == '|')  {
                    pos_token++;
                }

                char inicial = *pos_token++;
                if (*pos_token == '|')  {
                    pos_token++;
                }

                char cantidad_str[10];
                i = 0;
                while (*pos_token && *pos_token != '|' && *pos_token != '\0') {
                    cantidad_str[i++] = *pos_token++;
                }
                cantidad_str[i] = '\0';

                int cantidad = atoi(cantidad_str);
                Sector nuevo_sector = crear_sector(nombre_sector, cantidad, inicial);
                nuevo_sector.asientos = crear_lista_asientos(cantidad, inicial);
                agregar_sector(&nuevo_sitio.lista_sectores, &nuevo_sector);
            }
            else {
                break;
            }
        }

        agregar_sitio(lista_sitios, &nuevo_sitio);
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

/**
 * @brief Carga la lista de eventos desde un archivo.
 * @param lista_eventos Puntero a la lista de eventos.
 * @param lista_sitios Puntero constante a la lista de sitios.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_eventos(ListaEventos *lista_eventos, const ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';
        trim(linea);

        
        char *pos_cadena = linea;
        
        char nombre_evento[BUFFER_LECTURA_LINEA];
        int i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            nombre_evento[i++] = *pos_cadena++;
        }
        nombre_evento[i] = '\0';
        if (*pos_cadena == '|')  {
            pos_cadena++;
        }


        char productora[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            productora[i++] = *pos_cadena++;
        }
        productora[i] = '\0';
        if (*pos_cadena == '|')  {
            pos_cadena++;
        }

      
        char fecha_str[50];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            fecha_str[i++] = *pos_cadena++;
        }
        fecha_str[i] = '\0';
        if (*pos_cadena == '|')  {
            pos_cadena++;
        }

        
        char nombre_sitio[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != ',') {
            nombre_sitio[i++] = *pos_cadena++;
        }
        nombre_sitio[i] = '\0';
        if (*pos_cadena == ',') {
            pos_cadena++;
        }

        Fecha fecha;
        sscanf(fecha_str, "%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

        Sitio *sitio = buscar_sitio((ListaSitios *)lista_sitios, nombre_sitio);
        if (!sitio) {
            continue;
        }

        Evento nuevo_evento = crear_evento(nombre_evento, productora, fecha, sitio);

       
        int indice_sector = -1;
        while (*pos_cadena) {
            if (strncmp(pos_cadena, "SECTOR|", 7) == 0) {
                indice_sector++;
                
                char token_sector[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_cadena && *pos_cadena != ',' && i < BUFFER_LECTURA_LINEA - 1) {
                    token_sector[i++] = *pos_cadena++;
                }
                token_sector[i] = '\0';
                if (*pos_cadena == ',') {
                    pos_cadena++;
                }

                
                char *pos_token = token_sector;
                pos_token += 7; 

                i = 0;
                while (*pos_token && *pos_token != '|') {
                    i++, pos_token++;
                }
                if (*pos_token == '|') {
                    pos_token++;
                }

                
                char inicial = *pos_token++;
                if (*pos_token == '|') {
                    pos_token++;
                }

            
                char cantidad_str[10];
                i = 0;
                while (*pos_token && *pos_token != '|') {
                    cantidad_str[i++] = *pos_token++;
                }
                cantidad_str[i] = '\0';
                if (*pos_token == '|') {
                    pos_token++;
                }

                
                char monto_str[10];
                i = 0;
                while (*pos_token && *pos_token != '|' && *pos_token != '\0') {
                    monto_str[i++] = *pos_token++;
                }
                monto_str[i] = '\0';

                int cantidad = atoi(cantidad_str);
                float monto = atof(monto_str);

                asignar_monto_sector(&nuevo_evento,&nuevo_evento.sitio->lista_sectores.sectores[indice_sector],monto);
                nuevo_evento.asientos_por_sector[indice_sector] = crear_lista_asientos(cantidad, inicial);
            }
            else if (strncmp(pos_cadena, "ASIENTO|", 8) == 0 && indice_sector >= 0) {
                char token_asiento[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_cadena && *pos_cadena != ',' && i < BUFFER_LECTURA_LINEA - 1) {
                    token_asiento[i++] = *pos_cadena++;
                }
                token_asiento[i] = '\0';
                if (*pos_cadena == ',') {
                    pos_cadena++;
                }

                char *pos_token = token_asiento;
                pos_token += 8; 

                char numero_asiento[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_token && *pos_token != '|') {
                    numero_asiento[i++] = *pos_token++;
                }
                numero_asiento[i] = '\0';
                if (*pos_token == '|') {
                    pos_token++;
                }

                int estado = atoi(pos_token);

                Asiento *asiento = buscar_asiento(&nuevo_evento.asientos_por_sector[indice_sector], numero_asiento);
                if (asiento) {
                    asiento->estado = estado;
                }
            }
            else {
                break;
            }
        }

        agregar_evento(lista_eventos, &nuevo_evento);
    }

    fclose(archivo);
    return OPERACION_EXITOSA;
}

/**
 * @brief Carga la lista de facturas desde un archivo.
 * @param lista_facturas Puntero a la lista de facturas.
 * @param lista_eventos Puntero constante a la lista de eventos.
 * @param ruta Ruta del archivo a cargar.
 * @return Codigo de exito o error.
 */
int cargar_facturas(ListaFacturas *lista_facturas, const ListaEventos *lista_eventos, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[BUFFER_LECTURA_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';
        trim(linea);

        char *pos_cadena = linea;

        char id_str[20];
        int i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            id_str[i++] = *pos_cadena++;
        }
        id_str[i] = '\0';
        if (*pos_cadena == '|') pos_cadena++;

        char fecha_str[20];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            fecha_str[i++] = *pos_cadena++;
        }
        fecha_str[i] = '\0';
        if (*pos_cadena == '|') {
            pos_cadena++;
        }

        char cedula[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            cedula[i++] = *pos_cadena++;
        }
        cedula[i] = '\0';
        if (*pos_cadena == '|') {
            pos_cadena++;
        }

        char nombre_cliente[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != '|') {
            nombre_cliente[i++] = *pos_cadena++;
        }
        nombre_cliente[i] = '\0';
        if (*pos_cadena == '|') {
            pos_cadena++;
        }

        char nombre_evento[BUFFER_LECTURA_LINEA];
        i = 0;
        while (*pos_cadena && *pos_cadena != ',') {
            nombre_evento[i++] = *pos_cadena++;
        }
        nombre_evento[i] = '\0';
        if (*pos_cadena == ',') {
            pos_cadena++;
        }

        Fecha fecha;
        sscanf(fecha_str, "%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

        Evento *evento = buscar_evento((ListaEventos *)lista_eventos, nombre_evento);
        if (!evento) continue;

        int id = atoi(id_str);
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
        nueva_factura.subtotal = 0.0f;
        nueva_factura.costo_servicio = 0.0f;
        nueva_factura.total = 0.0f;

        while (*pos_cadena) {
            if (strncmp(pos_cadena, "ASIENTO|", 8) == 0) {
                
                char token_asiento[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_cadena && *pos_cadena != ',' && i < BUFFER_LECTURA_LINEA - 1) {
                    token_asiento[i++] = *pos_cadena++;
                }
                token_asiento[i] = '\0';
                if (*pos_cadena == ',') {
                    pos_cadena++;
                }

                char *pos_token = token_asiento;
                pos_token += 8; 

                char numero_asiento[BUFFER_LECTURA_LINEA];
                i = 0;
                while (*pos_token && *pos_token != '|') {
                    numero_asiento[i++] = *pos_token++;
                }
                numero_asiento[i] = '\0';
                if (*pos_token == '|') {
                    pos_token++;
                }

                char costo_str[20];
                i = 0;
                while (*pos_token && *pos_token != '|' && *pos_token != '\0') {
                    costo_str[i++] = *pos_token++;
                }
                costo_str[i] = '\0';

                float costo = strtof(costo_str, NULL);

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
            else if (strncmp(pos_cadena, "SUBTOTAL|", 9) == 0) {
                char *pos_valor = pos_cadena + 9;
                char valor_str[20];
                i = 0;
                while (*pos_valor && *pos_valor != ',' && i < 19) {
                    valor_str[i++] = *pos_valor++;
                }
                valor_str[i] = '\0';
                nueva_factura.subtotal = strtof(valor_str, NULL);

                while (*pos_valor && *pos_valor != ',') {
                    pos_valor++;
                }
                if (*pos_valor == ',') {
                    pos_valor++;
                }
                pos_cadena = pos_valor;
            }
            else if (strncmp(pos_cadena, "COSTO_SERVICIO|", 15) == 0) {
                char *pos_valor = pos_cadena + 15;
                char valor_str[20];
                i = 0;
                while (*pos_valor && *pos_valor != ',' && i < 19) {
                    valor_str[i++] = *pos_valor++;
                }
                valor_str[i] = '\0';
                nueva_factura.costo_servicio = strtof(valor_str, NULL);

                
                while (*pos_valor && *pos_valor != ',') {
                    pos_valor++;
                }
                if (*pos_valor == ',') {
                    pos_valor++;
                }
                pos_cadena = pos_valor;
            }
            else if (strncmp(pos_cadena, "TOTAL|", 6) == 0) {
                char *pos_valor = pos_cadena + 6;
                char valor_str[20];
                i = 0;
                while (*pos_valor && *pos_valor != ',' && *pos_valor != '\0' && i < 19) {
                    valor_str[i++] = *pos_valor++;
                }
                valor_str[i] = '\0';
                nueva_factura.total = strtof(valor_str, NULL);

                while (*pos_valor && *pos_valor != ',') {
                    pos_valor++;
                }
                if (*pos_valor == ',') {
                    pos_valor++;
                }
                pos_cadena = pos_valor;
            }
            else {
                break;
            }
        }

        agregar_factura(lista_facturas, &nueva_factura);
    }
    fclose(archivo);
    return OPERACION_EXITOSA;
}
