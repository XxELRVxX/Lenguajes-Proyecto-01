/**
 * @file programa.c
 * @brief Definicion de la estructura y funciones principales del programa.
 */

#include "programa.h"

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
                printf("gestion de sitios\n");
                break;
                case 2:
                printf("gestion de espacios\n");
                break;
                case 3:
                printf("gestion de eventos\n");
                break;
                case 4:
                printf("estado de evento\n");
                break;
                case 5:
                mostrar_lista_facturas(&programa->facturas);
                break;
                case 6:
                printf("estadisticas\n");
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
                    printf("consulta por evento\n");
                    break;
                case 2:
                    printf("comprar boletos\n");
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
 * @brief Lee una opcion numerica del usuario desde el teclado.
 * @return Opcion leida, o 0 si la entrada no es un numero valido.
 */
int leer_opcion(void) {
    int opcion;
    int leido = scanf("%d", &opcion);
    while (getchar() != '\n');
    
    if (leido == ENTRADA_VALIDA) {
        return opcion;
    } else {
        return ENTRADA_INVALIDA;
    }
}

/**
 * @brief Lee una cadena de caracteres desde stdin.
 * @param buffer Buffer donde se almacenara la cadena leida.
 * @param largo_cadena tamaño maximo del buffer.
 */
void leer_cadena(char *buffer, int largo_cadena) {
    if (fgets(buffer, largo_cadena, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/**
 * @brief Limpia la consola. Compatible con Windows y Linux.
 */
void limpiar_consola() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}