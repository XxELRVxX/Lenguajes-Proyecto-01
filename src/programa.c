/**
 * @file programa.c
 * @brief Definicion de la estructura y funciones principales del programa.
 */

#include "programa.h"
#include "ui.h"
#include "estadisticas.h"
#include <ctype.h>
#include <time.h>

/**
 * @brief Crea una instancia del programa con listas vacias y usuario inicializado.
 * @return Programa inicializado.
 */
Programa crear_programa() {
    Programa programa;
    programa.admin = crear_usuario();
    programa.eventos = crear_lista_eventos();
    programa.sitios = crear_lista_sitios();
    programa.facturas = crear_lista_facturas();
    return programa;
}

/**
 * @brief Libera toda la memoria asociada al programa.
 * @param programa Puntero al programa a liberar.
 */
void liberar_programa(Programa *programa) {
    liberar_lista_eventos(&programa->eventos);
    liberar_lista_sitios(&programa->sitios);
    liberar_lista_facturas(&programa->facturas);
    liberar_usuario(&programa->admin);
}

/**
 * @brief Guarda el estado del programa en archivos.
 * @param programa Puntero constante al programa.
 * @return Codigo de exito o error.
 */
int guardar_programa(const Programa *programa) {
    if (guardar_sitios(&programa->sitios, RUTA_ALMACENAMIENTO_SITIOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (guardar_eventos(&programa->eventos, RUTA_ALMACENAMIENTO_EVENTOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (guardar_facturas(&programa->facturas, RUTA_ALMACENAMIENTO_FACTURAS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    return OPERACION_EXITOSA;
}

/**
 * @brief Carga el estado del programa desde archivos.
 * @param programa Puntero al programa.
 * @return Codigo de exito o error.
 */
int cargar_programa(Programa *programa) {
    cargar_usuario(&programa->admin);

    if (cargar_sitios(&programa->sitios, RUTA_ALMACENAMIENTO_SITIOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (cargar_eventos(&programa->eventos, &programa->sitios, RUTA_ALMACENAMIENTO_EVENTOS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }
    if (cargar_facturas(&programa->facturas, &programa->eventos, RUTA_ALMACENAMIENTO_FACTURAS) != OPERACION_EXITOSA) {
        return OPERACION_FALLIDA;
    }

    return OPERACION_EXITOSA;
}


/**
 * @brief Ejecuta el bucle principal del programa con el menu de navegacion.
 * @param programa Puntero al programa inicializado.
 */
void ejecutar_programa(Programa *programa) {
    limpiar_consola();
    int opcion;
    do {
        limpiar_consola();
        printf("\n==== Gestion de Eventos ====\n");
        printf("1. Opciones Administrativas\n");
        printf("2. Opciones Generales\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        opcion = leer_opcion();
        
        if (opcion == ENTRADA_INVALIDA) {
            printf("Entrada invalida. Intente de nuevo");
        } else {
            
            switch (opcion) {
                case 1:
                    menu_administrativo(programa);
                    break;
                case 2:
                    menu_general(programa);
                    break;
                case 3:
                    guardar_programa(programa);
                    printf("Guardando datos y saliendo...\n");
                    break;
                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
            }
        }
    } while (opcion != 3);
}

/**
 * @brief Selecciona un evento y muestra su estado detallado por sector.
 * @param programa Puntero al programa.
 */
static void estado_evento_menu(Programa *programa) {
    if (programa->eventos.cantidad_eventos == 0) {
        printf("No hay eventos registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    mostrar_lista_eventos(&programa->eventos);
    printf("Seleccione un evento (1-%d): ", programa->eventos.cantidad_eventos);
    int indice = leer_indice_valido(1, programa->eventos.cantidad_eventos);
    Evento *evento = &programa->eventos.eventos[indice - 1];

    limpiar_consola();
    printf("================================================\n");
    printf("  Evento     : %s\n", evento->nombre_evento);
    printf("  Productora : %s\n", evento->productora);
    printf("  Sitio      : %s\n", evento->sitio->nombre);
    printf("  Fecha      : %02d/%02d/%04d\n",
        evento->fecha.dia, evento->fecha.mes, evento->fecha.anio);
    printf("================================================\n");

    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        ListaAsientos *lista = &evento->asientos_por_sector[i];
        int disponibles = contar_asientos_disponibles(lista);
        int vendidos = lista->cantidad_asientos - disponibles;
        float recaudado = vendidos * evento->montos_por_sector[i];

        printf("\n  Sector      : %s\n", sector->nombre);
        printf("  Precio      : $%.2f\n", evento->montos_por_sector[i]);
        printf("  Recaudado   : $%.2f\n", recaudado);
        printf("  Vendidos    : %d\n", vendidos);
        printf("  Disponibles : %d\n", disponibles);
        printf("  Asientos    :\n");
        for (int j = 0; j < lista->cantidad_asientos; j++) {
            Asiento *asiento = &lista->asientos[j];
            printf("    %s : %s\n",
                asiento->numero_asiento,
                asiento->estado == ASIENTO_DISPONIBLE ? "Disponible" : "Vendido");
        }
        printf("  ------------------------------------------------\n");
    }
    printf("================================================\n");
    printf("\nPresione Enter para continuar...");
    getchar();
}

/**
 * @brief Muestra el menu administrativo, solicita autenticacion y gestiona las opciones.
 * @param programa Puntero al programa.
 */
void menu_administrativo(Programa *programa) {
    char usuario[LARGO_MAXIMO_CARACTERES];
    char password[LARGO_MAXIMO_CARACTERES];
    int autenticado = 0;
    
    do {
        limpiar_consola();
        printf("\n-- Acceso Administrativo --\n");
        printf("Usuario (0 para volver): ");
        leer_cadena(usuario, LARGO_MAXIMO_CARACTERES);
        
        if (strcmp(usuario, "0") == 0) {
            limpiar_consola();
            printf("Volviendo...\n");
            return;    
        }
        
        printf("Password: ");
        leer_cadena(password, LARGO_MAXIMO_CARACTERES);
        
        int resultado = validar_acceso(&programa->admin, usuario, password);
        if (resultado == ACCESO_CORRECTO) {
            autenticado = 1;
        } else {
            if (resultado == USUARIO_INCORRECTO) {
                printf("Usuario incorrecto.");
            } else {
                printf("Password incorrecta.");
            }
            printf(" Presione Enter para intentar de nuevo...");
            getchar();
        }
    } while (!autenticado);
    
    int opcion;
    limpiar_consola();
    do {
        limpiar_consola();
        printf("\n==== Menu Administrativo ====\n");
        printf("1. Gestion de Sitios de Eventos\n");
        printf("2. Gestion de Espacios de Sitio de Eventos\n");
        printf("3. Gestion de Eventos\n");
        printf("4. Estado de Evento\n");
        printf("5. Lista de Facturas\n");
        printf("6. Estadisticas\n");
        printf("7. Volver\n");
        printf("Seleccione una opcion: ");
        opcion = leer_opcion();

        if (opcion == ENTRADA_INVALIDA) {
            printf("Entrada invalida. Intente de nuevo");
        } else {
            switch (opcion) {
                case 1:
                    gestion_sitios(programa);
                    break;
                case 2:
                    gestion_sectores(programa);
                    break;
                case 3:
                    gestion_eventos(programa);
                    break;
                case 4:
                    limpiar_consola();
                    estado_evento_menu(programa);
                    break;
                case 5:
                    limpiar_consola();
                    mostrar_lista_facturas(&programa->facturas);
                    printf("\nPresione Enter para continuar...");
                    getchar();
                    break;
                case 6:
                    estadisticas(programa);
                    break;
                case 7:
                    printf("Volviendo al menu principal...\n");
                    break;
                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
                }
            }
        } while (opcion != 7);
    }


/**
 * @brief Solicita fecha inicial y muestra eventos futuros para seleccion.
 * @param programa Puntero al programa.
 * @return Puntero al evento seleccionado, o NULL si no hay eventos futuros.
 */
static Evento *seleccionar_evento_futuro(Programa *programa) {
    int dia, mes, anio;
    do {
        printf("Ingrese fecha inicial:\n");
        printf("  Dia : "); dia  = leer_opcion();
        printf("  Mes : "); mes  = leer_opcion();
        printf("  Anio: "); anio = leer_opcion();
        if (validar_fecha(dia, mes, anio) == FECHA_INVALIDA) {
            printf("Fecha invalida. Intente nuevamente.\n");
        }
    } while (validar_fecha(dia, mes, anio) == FECHA_INVALIDA);
    Fecha fecha_inicial = crear_fecha(dia, mes, anio);

    int cantidad = programa->eventos.cantidad_eventos;
    Evento *futuros[cantidad];
    int cantidad_futuros = 0;
    for (int i = 0; i < cantidad; i++) {
        Evento *evento_actual = &programa->eventos.eventos[i];
        if (comparar_fechas(&evento_actual->fecha, &fecha_inicial) >= 0) {
            futuros[cantidad_futuros++] = evento_actual;
        }
    }

    if (cantidad_futuros == 0) {
        printf("No hay eventos desde esa fecha.\n");
        return NULL;
    }

    printf("\nEventos disponibles:\n");
    for (int i = 0; i < cantidad_futuros; i++) {
        printf("  %d. %-30s %02d/%02d/%04d\n",
            i + 1,
            futuros[i]->nombre_evento,
            futuros[i]->fecha.dia,
            futuros[i]->fecha.mes,
            futuros[i]->fecha.anio);
    }
    printf("Seleccione un evento (1-%d): ", cantidad_futuros);
    int indice = leer_indice_valido(1, cantidad_futuros);
    return futuros[indice - 1];
}

/**
 * @brief Muestra informacion del evento con disponibilidad por sector.
 */
static void consulta_por_evento(Programa *programa) {
    if (programa->eventos.cantidad_eventos == 0) {
        printf("No hay eventos registrados.\n");
        return;
    }

    Evento *evento = seleccionar_evento_futuro(programa);
    if (evento == NULL) return;

    limpiar_consola();
    printf("================================================\n");
    printf("  Evento     : %s\n", evento->nombre_evento);
    printf("  Productora : %s\n", evento->productora);
    printf("  Sitio      : %s\n", evento->sitio->nombre);
    printf("  Fecha      : %02d/%02d/%04d\n",
        evento->fecha.dia, evento->fecha.mes, evento->fecha.anio);
    printf("------------------------------------------------\n");
    printf("  %-15s  %10s  %10s\n", "Sector", "Precio", "Disponibles");
    printf("  %-15s  %10s  %10s\n", "---------------", "----------", "----------");
    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        int disponibles = contar_asientos_disponibles(&evento->asientos_por_sector[i]);
        printf("  %-15s  %9.2f$  %10d\n",
            sector->nombre,
            evento->montos_por_sector[i],
            disponibles);
    }
    printf("================================================\n");
}

/**
 * @brief Permite comprar boletos de un evento, genera y almacena la factura.
 */
static void compra_de_boletos(Programa *programa) {
    if (programa->eventos.cantidad_eventos == 0) {
        printf("No hay eventos registrados.\n");
        return;
    }

    Evento *evento = seleccionar_evento_futuro(programa);
    if (evento == NULL) return;

    limpiar_consola();
    printf("Evento: %s  (%02d/%02d/%04d)\n\n",
        evento->nombre_evento,
        evento->fecha.dia, evento->fecha.mes, evento->fecha.anio);


    int hay_disponibles = 0;
    for (int i = 0; i < evento->cantidad_sectores; i++) {
        Sector *sector = &evento->sitio->lista_sectores.sectores[i];
        int disponibles = contar_asientos_disponibles(&evento->asientos_por_sector[i]);
        if (disponibles > 0) hay_disponibles = 1;
        printf("  Sector %s Precio ($%.2f)  - %d disponible%s\n",
            sector->nombre,
            evento->montos_por_sector[i],
            disponibles,
            disponibles == 1 ? "" : "s");

        for (int j = 0; j < evento->asientos_por_sector[i].cantidad_asientos; j++) {
            Asiento *asiento_actual = &evento->asientos_por_sector[i].asientos[j];
            if (asiento_actual->estado == ASIENTO_DISPONIBLE) {
                printf("    %s", asiento_actual->numero_asiento);
            }
        }
        if (disponibles > 0) printf("\n");
    }
    printf("\n");

    if (!hay_disponibles) {
        printf("No hay asientos disponibles en este evento.\n");
        return;
    }

    Asiento **asientos_comprados = NULL;
    int cantidad_comprados = 0;
    char numero_asiento_buscado[LARGO_MAXIMO_CARACTERES];

    printf("Ingrese el numero de asiento a comprar (Enter para terminar):\n");
    while (1) {
        printf("  Asiento(Enter para finalizar compra): ");
        leer_cadena(numero_asiento_buscado, sizeof(numero_asiento_buscado));
        if (numero_asiento_buscado[0] == '\0') break;

        Asiento *asiento_encontrado = NULL;
        for (int i = 0; i < evento->cantidad_sectores; i++) {
            asiento_encontrado = buscar_asiento(&evento->asientos_por_sector[i], numero_asiento_buscado);
            if (asiento_encontrado != NULL) break;
        }

        if (asiento_encontrado == NULL) {
            printf("  El asiento '%s' no existe en este evento.\n", numero_asiento_buscado);
            continue;
        }
        if (asiento_encontrado->estado == ASIENTO_VENDIDO) {
            printf("  El asiento '%s' ya fue vendido.\n", numero_asiento_buscado);
            continue;
        }

        int ya_seleccionado = 0;
        for (int i = 0; i < cantidad_comprados; i++) {
            if (asientos_comprados[i] == asiento_encontrado) { ya_seleccionado = 1; break; }
        }
        if (ya_seleccionado) {
            printf("  Ya seleccionaste ese asiento.\n");
            continue;
        }

        Asiento **temp = realloc(asientos_comprados, (cantidad_comprados + 1) * sizeof(Asiento *));
        if (temp == NULL) {
            printf("Error de memoria.\n");
            free(asientos_comprados);
            return;
        }
        asientos_comprados = temp;
        asientos_comprados[cantidad_comprados++] = asiento_encontrado;
        printf("  Asiento '%s' agregado.\n", numero_asiento_buscado);
    }

    if (cantidad_comprados == 0) {
        free(asientos_comprados);
        printf("No se seleccionaron asientos. Operacion cancelada.\n");
        return;
    }

    /* Datos del comprador */
    char cedula[LARGO_MAXIMO_CARACTERES];
    char nombre[LARGO_MAXIMO_CARACTERES];
    printf("Cedula del comprador : ");
    leer_cadena(cedula, sizeof(cedula));
    printf("Nombre del comprador : ");
    leer_cadena(nombre, sizeof(nombre));

    /* Marcar asientos como vendidos */
    for (int i = 0; i < cantidad_comprados; i++) {
        vender_asiento(asientos_comprados[i]);
    }

    ListaAsientos lista_asientos_factura = crear_lista_asientos_vacia();
    for (int i = 0; i < cantidad_comprados; i++) {
        Asiento copia_asiento = crear_asiento(asientos_comprados[i]->numero_asiento);
        agregar_asiento_a_lista(&lista_asientos_factura, &copia_asiento);
    }

    time_t tiempo_actual = time(NULL);
    struct tm *fecha_sistema = localtime(&tiempo_actual);
    Fecha fecha_compra = crear_fecha(fecha_sistema->tm_mday, fecha_sistema->tm_mon + 1, fecha_sistema->tm_year + 1900);

    Factura factura = crear_factura(evento, &fecha_compra, cedula, nombre, &lista_asientos_factura);
    liberar_lista_asientos(&lista_asientos_factura);

    limpiar_consola();
    mostrar_factura(&factura);

    free(asientos_comprados);
    agregar_factura(&programa->facturas, &factura);
    printf("\nPresione Enter para continuar...");
    getchar();
}

/**
 * @brief Muestra el menu de opciones generales.
 * @param programa Puntero al programa.
 */
void menu_general(Programa *programa) {
    int opcion;
    do {
        limpiar_consola();
        printf("\n==== Menu General ====\n");
        printf("1. Consulta por Evento\n");
        printf("2. Compra de Boletos\n");
        printf("3. Volver\n");
        printf("Seleccione una opcion: ");
        opcion = leer_opcion();
        
        if (opcion == ENTRADA_INVALIDA) {
            printf("Entrada invalida. Intente de nuevo");
        } else {
            switch (opcion) {
                case 1:
                    consulta_por_evento(programa);
                    printf("\nPresione Enter para continuar...");
                    getchar();
                    break;
                case 2:
                    compra_de_boletos(programa);
                    break;
                case 3:
                    printf("Volviendo al menu principal...\n");
                    break;
                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
            }
        }
    } while (opcion != 3);
}

/**
 * @brief Guarda una copia de los nombres de sitio de cada evento.
 * @param programa Puntero al programa.
 * @return Arreglo de cadenas con los nombres, o NULL si no hay eventos.
 *         El llamador es responsable de liberar la memoria.
 */
static char **guardar_nombres_sitios(const Programa *programa) {
    int cantidad = programa->eventos.cantidad_eventos;
    if (cantidad == 0) return NULL;
    char **nombres = malloc(cantidad * sizeof(char *));
    for (int i = 0; i < cantidad; i++) {
        const char *nombre_sitio_actual = programa->eventos.eventos[i].sitio->nombre;
        nombres[i] = malloc(strlen(nombre_sitio_actual) + 1);
        strcpy(nombres[i], nombre_sitio_actual);
    }
    return nombres;
}

/**
 * @brief Reenlaza los punteros Evento.sitio usando nombres guardados previamente.
 * @param programa Puntero al programa.
 * @param nombres_guardados Arreglo devuelto por guardar_nombres_sitios.
 */
static void reenlazar_sitios(Programa *programa, char **nombres_guardados) {
    int cantidad = programa->eventos.cantidad_eventos;
    for (int i = 0; i < cantidad; i++) {
        programa->eventos.eventos[i].sitio =
            buscar_sitio(&programa->sitios, nombres_guardados[i]);
        free(nombres_guardados[i]);
    }
    free(nombres_guardados);
}

/**
 * @brief Indica si el sitio tiene eventos asociados.
 * @param programa Puntero constante al programa.
 * @param nombre_sitio Nombre del sitio a verificar.
 * @return 1 si existe al menos un evento asociado, 0 si no.
 */
static int sitio_tiene_eventos(const Programa *programa, const char *nombre_sitio) {
    for (int i = 0; i < programa->eventos.cantidad_eventos; i++) {
        if (strcmp(programa->eventos.eventos[i].sitio->nombre, nombre_sitio) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Revalida los punteros Evento.sitio tras un realloc en lista_sitios.
 * @details Guarda los nombres antes de cualquier realloc y los usa para reenlazar.
 * @param programa Puntero al programa.
 */
void revalidar_punteros_sitios(Programa *programa) {
    char **nombres_guardados = guardar_nombres_sitios(programa);
    if (nombres_guardados != NULL)
        reenlazar_sitios(programa, nombres_guardados);
}

static void agregar_sitio_individual(Programa *programa) {
    char nombre[LARGO_MAXIMO_CARACTERES];
    char ubicacion[LARGO_MAXIMO_CARACTERES];
    char sitio_web[LARGO_MAXIMO_CARACTERES];

    printf("Nombre: ");
        leer_cadena(nombre, LARGO_MAXIMO_CARACTERES);
    printf("Ubicacion: ");
    leer_cadena(ubicacion, LARGO_MAXIMO_CARACTERES);
    printf("Sitio web (Enter para omitir): ");
    leer_cadena(sitio_web, LARGO_MAXIMO_CARACTERES);

    char **nombres_guardados = guardar_nombres_sitios(programa);

    Sitio nuevo = crear_sitio(nombre, ubicacion,
                              sitio_web[0] != '\0' ? sitio_web : NULL);
    int resultado = agregar_sitio(&programa->sitios, &nuevo);
    if (resultado == OPERACION_EXITOSA) {
        reenlazar_sitios(programa, nombres_guardados);
        nombres_guardados = NULL;
        printf("Sitio '%s' agregado con exito.\n", nombre);
    } else if (resultado == OPERACION_FALLIDA_DUPLICADO) {
        printf("Ya existe un sitio con el nombre '%s'.\n", nombre);
    } else {
        printf("Error al reservar memoria.\n");
    }
    if (nombres_guardados != NULL) {
        for (int i = 0; i < programa->eventos.cantidad_eventos; i++) free(nombres_guardados[i]);
        free(nombres_guardados);
    }
    printf("Presione Enter para continuar...");
    getchar();
}

static void cargar_sitios_lote(Programa *programa) {
    char ruta[LARGO_MAXIMO_CARACTERES];
    printf("Ruta del archivo: ");
    leer_cadena(ruta, LARGO_MAXIMO_CARACTERES);

    char **nombres_guardados = guardar_nombres_sitios(programa);

    int resultado = cargar_sitios_por_lote(&programa->sitios, ruta);
    if (resultado == OPERACION_FALLIDA) {
        printf("No se pudo abrir el archivo '%s'.\n", ruta);
        if (nombres_guardados != NULL) {
            for (int i = 0; i < programa->eventos.cantidad_eventos; i++) free(nombres_guardados[i]);
            free(nombres_guardados);
        }
    } else {
        if (nombres_guardados != NULL)
            reenlazar_sitios(programa, nombres_guardados);
    }
    printf("Presione Enter para continuar...");
    getchar();
}

static void editar_sitio_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }
    printf("Numero de sitio a editar (1-%d): ", programa->sitios.cantidad);
    int indice = leer_indice_valido(1, programa->sitios.cantidad);
    Sitio *sitio = &programa->sitios.sitios[indice - 1];
    char nuevo_nombre[LARGO_MAXIMO_CARACTERES];
    char nueva_ubicacion[LARGO_MAXIMO_CARACTERES];
    char nuevo_sitio_web[LARGO_MAXIMO_CARACTERES];

    printf("Nombre actual: %s\n", sitio->nombre);
    printf("Nuevo nombre (Enter para mantener): ");
    leer_cadena(nuevo_nombre, LARGO_MAXIMO_CARACTERES);

    printf("Ubicacion actual: %s\n", sitio->ubicacion);
    printf("Nueva ubicacion (Enter para mantener): ");
    leer_cadena(nueva_ubicacion, LARGO_MAXIMO_CARACTERES);

    printf("Sitio web actual: %s\n",
           sitio->sitio_web ? sitio->sitio_web : "(ninguno)");
    printf("Nuevo sitio web (Enter para mantener, '-' para eliminar): ");
    leer_cadena(nuevo_sitio_web, LARGO_MAXIMO_CARACTERES);

    const char *web_param;
    if (nuevo_sitio_web[0] == '\0') {
        web_param = nuevo_sitio_web;       
    } else if (strcmp(nuevo_sitio_web, "-") == 0) {
        web_param = NULL;                   
    } else {
        web_param = nuevo_sitio_web;
    }

    if (nuevo_nombre[0] != '\0' &&
        strcmp(nuevo_nombre, sitio->nombre) != 0 &&
        buscar_sitio(&programa->sitios, nuevo_nombre) != NULL) {
        printf("Ya existe un sitio con el nombre '%s'.\n", nuevo_nombre);
    } else {
        editar_sitio(sitio, nuevo_nombre, nueva_ubicacion, web_param);
        printf("Sitio actualizado con exito.\n");
    }
    printf("Presione Enter para continuar...");
    getchar();
}

static void eliminar_sitio_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }
    printf("Numero de sitio a eliminar (1-%d): ", programa->sitios.cantidad);
    int indice = leer_indice_valido(1, programa->sitios.cantidad);
    const char *nombre = programa->sitios.sitios[indice - 1].nombre;
    if (sitio_tiene_eventos(programa, nombre)) {
        printf("No se puede eliminar '%s': tiene evento(s) asociado(s).\n", nombre);
    } else {
        char **nombres_guardados = guardar_nombres_sitios(programa);
        eliminar_sitio(&programa->sitios, nombre);
        if (nombres_guardados != NULL)
            reenlazar_sitios(programa, nombres_guardados);
        printf("Sitio eliminado con exito.\n");
    }
    printf("Presione Enter para continuar...");
    getchar();
}


static void mostrar_sitios_con_sectores(const Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        return;
    }
    for (int i = 0; i < programa->sitios.cantidad; i++) {
        const Sitio *sitio_actual = &programa->sitios.sitios[i];
        printf("%d. ", i + 1);
        mostrar_sitio(sitio_actual);
        if (sitio_actual->lista_sectores.cantidad_sectores == 0) {
            printf("   (Sin sectores configurados)\n");
        } else {
            mostrar_lista_sectores(&sitio_actual->lista_sectores);
        }
    }
}

/**
 * @brief Solicita datos y edita el nombre de un sector de un sitio seleccionado.
 */
static void editar_sector_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    mostrar_sitios_con_sectores(programa);
    printf("Seleccione un sitio (1-%d): ", programa->sitios.cantidad);
    int indice_sitio = leer_indice_valido(1, programa->sitios.cantidad);

    Sitio *sitio = &programa->sitios.sitios[indice_sitio - 1];
    if (sitio->lista_sectores.cantidad_sectores == 0) {
        printf("El sitio '%s' no tiene sectores configurados.\n", sitio->nombre);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    for (int i = 0; i < sitio->lista_sectores.cantidad_sectores; i++) {
        printf("%d. ", i + 1);
        mostrar_sector(&sitio->lista_sectores.sectores[i]);
    }
    printf("Seleccione un sector (1-%d): ", sitio->lista_sectores.cantidad_sectores);
    int indice_sector = leer_indice_valido(1, sitio->lista_sectores.cantidad_sectores);

    Sector *sector = &sitio->lista_sectores.sectores[indice_sector - 1];
    char nuevo_nombre_sector[LARGO_MAXIMO_CARACTERES];
    printf("Nombre actual: %s\n", sector->nombre);
    printf("Nuevo nombre (Enter para mantener): ");
    leer_cadena(nuevo_nombre_sector, sizeof(nuevo_nombre_sector));

    if (nuevo_nombre_sector[0] != '\0' &&
        strcmp(nuevo_nombre_sector, sector->nombre) != 0 &&
        buscar_sector(&sitio->lista_sectores, nuevo_nombre_sector) != NULL) {
        printf("Ya existe un sector con el nombre '%s' en este sitio.\n", nuevo_nombre_sector);
    } else {
        editar_sector(sector, nuevo_nombre_sector);
        printf("Sector actualizado con exito.\n");
    }
    printf("Presione Enter para continuar...");
    getchar();
}

/**
 * @brief Selecciona un sector de un sitio y lo elimina.
 */
static void eliminar_sector_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    mostrar_sitios_con_sectores(programa);
    printf("Seleccione un sitio (1-%d): ", programa->sitios.cantidad);
    int indice_sitio = leer_indice_valido(1, programa->sitios.cantidad);

    Sitio *sitio = &programa->sitios.sitios[indice_sitio - 1];
    if (sitio_tiene_eventos(programa, sitio->nombre)) {
        printf("No se puede eliminar un sector de '%s': tiene evento(s) asociado(s).\n",
               sitio->nombre);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    if (sitio->lista_sectores.cantidad_sectores == 0) {
        printf("El sitio '%s' no tiene sectores configurados.\n", sitio->nombre);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    for (int i = 0; i < sitio->lista_sectores.cantidad_sectores; i++) {
        printf("%d. ", i + 1);
        mostrar_sector(&sitio->lista_sectores.sectores[i]);
    }
    printf("Seleccione un sector a eliminar (1-%d): ",
           sitio->lista_sectores.cantidad_sectores);
    int indice_sector = leer_indice_valido(1, sitio->lista_sectores.cantidad_sectores);

    const char *nombre_sector = sitio->lista_sectores.sectores[indice_sector - 1].nombre;
    eliminar_sector(&sitio->lista_sectores, nombre_sector);
    printf("Sector eliminado con exito.\n");
    printf("Presione Enter para continuar...");
    getchar();
}

/**
 * @brief Solicita datos y agrega un sector a un sitio seleccionado.
 */
static void agregar_sector_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    mostrar_sitios_con_sectores(programa);
    printf("Seleccione un sitio (1-%d): ", programa->sitios.cantidad);
    int indice_sitio = leer_indice_valido(1, programa->sitios.cantidad);

    Sitio *sitio = &programa->sitios.sitios[indice_sitio - 1];

    char nombre_sector[LARGO_MAXIMO_CARACTERES];
    printf("Nombre del sector: ");
    leer_cadena(nombre_sector, sizeof(nombre_sector));

    int cantidad_asientos;
    do {
        printf("Cantidad de asientos: ");
        cantidad_asientos = leer_opcion();
        if (cantidad_asientos <= 0) {
            printf("Cantidad invalida. Ingrese un numero mayor a 0.\n");
        }
    } while (cantidad_asientos <= 0);

    char buf_inicial[LARGO_MAXIMO_CARACTERES];
    char inicial_sector;
    do {
        printf("Inicial del sector (caracter alfabetico): ");
        leer_cadena(buf_inicial, sizeof(buf_inicial));
        inicial_sector = buf_inicial[0];
        if (!isalpha((unsigned char)inicial_sector)) {
            printf("Inicial invalida. Ingrese un caracter alfabetico.\n");
        }
    } while (!isalpha((unsigned char)inicial_sector));
    inicial_sector = (char)toupper((unsigned char)inicial_sector);

    Sector nuevo_sector = crear_sector(nombre_sector, cantidad_asientos, inicial_sector);
    int resultado = agregar_sector(&sitio->lista_sectores, &nuevo_sector);
    if (resultado == OPERACION_EXITOSA) {
        printf("Sector '%s' agregado con exito (asientos %c1-%c%d).\n",
               nombre_sector, inicial_sector, inicial_sector, cantidad_asientos);
    } else if (resultado == OPERACION_FALLIDA_DUPLICADO) {
        printf("Ya existe un sector con el nombre '%s' en este sitio.\n", nombre_sector);
    } else {
        printf("Error de memoria al agregar el sector.\n");
    }
    printf("Presione Enter para continuar...");
    getchar();
}

/**
 * @brief Selecciona un sitio y resetea el estado de todos sus asientos.
 */
static void reset_sectores_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    mostrar_sitios_con_sectores(programa);
    printf("Seleccione un sitio para resetear sus espacios (1-%d): ",
           programa->sitios.cantidad);
    int indice_sitio = leer_opcion();
    if (indice_sitio < 1 || indice_sitio > programa->sitios.cantidad) {
        printf("Opcion invalida.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    Sitio *sitio = &programa->sitios.sitios[indice_sitio - 1];
    if (sitio_tiene_eventos(programa, sitio->nombre)) {
        printf("No se pueden resetear los sectores de '%s': tiene evento(s) asociado(s).\n",
               sitio->nombre);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    if (sitio->lista_sectores.cantidad_sectores == 0) {
        printf("El sitio '%s' no tiene sectores configurados.\n", sitio->nombre);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    liberar_lista_sectores(&sitio->lista_sectores);
    sitio->lista_sectores = crear_lista_sectores();
    printf("Sectores del sitio '%s' eliminados con exito.\n", sitio->nombre);
    printf("Presione Enter para continuar...");
    getchar();
}

/**
 * @brief Revalida los punteros Factura.evento tras un realloc en lista_eventos.
 * @param programa Puntero al programa.
 */
void revalidar_punteros_eventos(Programa *programa) {
    for (int i = 0; i < programa->facturas.cantidad_facturas; i++) {
        Factura *factura = &programa->facturas.facturas[i];
        factura->evento = buscar_evento(&programa->eventos, factura->evento->nombre_evento);
    }
}

/**
 * @brief Solicita datos y agrega un nuevo evento al sistema.
 */
static void agregar_evento_menu(Programa *programa) {
    if (programa->sitios.cantidad == 0) {
        printf("No hay sitios registrados. Registre un sitio antes de crear un evento.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    char nombre_evento[LARGO_MAXIMO_CARACTERES];
    printf("Nombre del evento: ");
    leer_cadena(nombre_evento, sizeof(nombre_evento));
    if (buscar_evento(&programa->eventos, nombre_evento) != NULL) {
        printf("Ya existe un evento con el nombre '%s'.\n", nombre_evento);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    char nombre_productora[LARGO_MAXIMO_CARACTERES];
    printf("Productora: ");
    leer_cadena(nombre_productora, sizeof(nombre_productora));

    int dia_evento, mes_evento, anio_evento;
    do {
        printf("Fecha del evento\n");
        printf("  Dia: ");
        dia_evento = leer_opcion();
        printf("  Mes (1-12): ");
        mes_evento = leer_opcion();
        printf("  Anio: ");
        anio_evento = leer_opcion();
        if (validar_fecha(dia_evento, mes_evento, anio_evento) == FECHA_INVALIDA) {
            printf("Fecha invalida. Ingrese nuevamente.\n");
        }
    } while (validar_fecha(dia_evento, mes_evento, anio_evento) == FECHA_INVALIDA);
    Fecha fecha_evento = crear_fecha(dia_evento, mes_evento, anio_evento);

    printf("\nSitios disponibles:\n");
    mostrar_lista_sitios(&programa->sitios);
    printf("Seleccione un sitio (1-%d): ", programa->sitios.cantidad);
    int indice_sitio = leer_indice_valido(1, programa->sitios.cantidad);

    Sitio *sitio = &programa->sitios.sitios[indice_sitio - 1];
    if (sitio->lista_sectores.cantidad_sectores == 0) {
        printf("El sitio '%s' no tiene sectores configurados.\n", sitio->nombre);
        printf("Configure los sectores del sitio antes de crear un evento.\n");
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    printf("\nIndique el monto por sector:\n");
    float montos_sectores[sitio->lista_sectores.cantidad_sectores];
    for (int i = 0; i < sitio->lista_sectores.cantidad_sectores; i++) {
        Sector *sector_actual = &sitio->lista_sectores.sectores[i];
        printf("  Sector '%s' - Monto: $ ", sector_actual->nombre);
        float monto_sector;
        do {
            scanf("%f", &monto_sector);
            while (getchar() != '\n');
            if (monto_sector < 0) {
                printf("Monto invalido. Ingrese un valor mayor o igual a 0: ");
            }
        } while (monto_sector < 0);
        montos_sectores[i] = monto_sector;
    }

    Evento nuevo_evento = crear_evento(nombre_evento, nombre_productora, fecha_evento, sitio);
    for (int i = 0; i < sitio->lista_sectores.cantidad_sectores; i++) {
        asignar_monto_sector(&nuevo_evento,
                             &sitio->lista_sectores.sectores[i],
                             montos_sectores[i]);
    }

    int resultado = agregar_evento(&programa->eventos, &nuevo_evento);
    if (resultado == OPERACION_EXITOSA) {
        revalidar_punteros_eventos(programa);
        printf("Evento '%s' creado con exito.\n", nombre_evento);
    } else {
        printf("Error de memoria al crear el evento.\n");
    }
    printf("Presione Enter para continuar...");
    getchar();
}

/**
 * @brief Muestra el submenu de gestion de eventos.
 * @param programa Puntero al programa.
 */
void gestion_eventos(Programa *programa) {
    int opcion;
    do {
        limpiar_consola();
        printf("==== Gestion de Eventos ====\n\n");
        mostrar_lista_eventos(&programa->eventos);
        printf("\n");
        printf("1. Agregar evento\n");
        printf("2. Volver\n");
        printf("\nSeleccione una opcion: ");
        opcion = leer_opcion();
        limpiar_consola();
        switch (opcion) {
            case 1:
                agregar_evento_menu(programa);
                break;
            case 2:
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    } while (opcion != 2);
}

/**
 * @brief Muestra el submenu de gestion de sectores de sitios de eventos.
 * @param programa Puntero al programa.
 */
void gestion_sectores(Programa *programa) {
    int opcion;
    do {
        limpiar_consola();
        printf("==== Gestion de Sectores de Sitio de Eventos ====\n");
        printf("1. Agregar sector a un sitio\n");
        printf("2. Editar sector de un sitio\n");
        printf("3. Eliminar sector de un sitio\n");
        printf("4. Reset de espacios de un sitio\n");
        printf("5. Volver\n");
        printf("\nSeleccione una opcion: ");
        opcion = leer_opcion();
        limpiar_consola();
        switch (opcion) {
            case 1:
                agregar_sector_menu(programa);
                break;
            case 2:
                editar_sector_menu(programa);
                break;
            case 3:
                eliminar_sector_menu(programa);
                break;
            case 4:
                reset_sectores_menu(programa);
                break;
            case 5:
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
    } while (opcion != 5);
}

/**
 * @brief Muestra el submenu de gestion de sitios de eventos.
 * @param programa Puntero al programa.
 */
void gestion_sitios(Programa *programa) {
    int opcion;
    do {
        limpiar_consola();
        printf("\n==== Gestion de Sitios de Eventos ====\n");
        mostrar_lista_sitios(&programa->sitios);
        printf("\n1. Agregar sitio individual\n");
        printf("2. Cargar sitios desde archivo (lote)\n");
        printf("3. Editar sitio\n");
        printf("4. Eliminar sitio\n");
        printf("5. Volver\n");
        printf("Seleccione una opcion: ");
        opcion = leer_opcion();

        if (opcion == ENTRADA_INVALIDA) {
            printf("Entrada invalida. Intente de nuevo.\n");
        } else {
            switch (opcion) {
                case 1: 
                    agregar_sitio_individual(programa); 
                    break;
                case 2: 
                    cargar_sitios_lote(programa);       
                    break;
                case 3: 
                    editar_sitio_menu(programa);        
                    break;
                case 4: 
                    eliminar_sitio_menu(programa);      
                    break;
                case 5: 
                    break;
                default: 
                    printf("Opcion invalida. Intente de nuevo.\n");
            }
        }
    } while (opcion != 5);
}