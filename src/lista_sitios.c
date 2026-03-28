/**
 * @file lista_sitios.c
 * @brief Implementacion de las funciones para el manejo de listas de sitios.
 */
#include "lista_sitios.h"



/**
 * @brief Crea una lista de sitios vacia.
 * @return ListaSitios vacia.
 */
ListaSitios crear_lista_sitios() {
    ListaSitios lista;
    lista.cantidad = 0;
    lista.sitios = NULL;

    return lista;
}

/**
 * @brief Agrega un sitio a la lista.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param nuevo_sitio Puntero al sitio a agregar.
 * @return Codigo de exito o error.
 */
int agregar_sitio(ListaSitios *lista_sitios, Sitio *nuevo_sitio) {
    if (buscar_sitio(lista_sitios, nuevo_sitio->nombre) != NULL) {
        liberar_sitio(nuevo_sitio);
        return OPERACION_FALLIDA_DUPLICADO; 
    }

    Sitio *temp_lista_sitios = realloc(lista_sitios->sitios, (lista_sitios->cantidad + 1) * sizeof(Sitio));
    if (temp_lista_sitios == NULL) {
        liberar_sitio(nuevo_sitio);
        return OPERACION_FALLIDA_MEMORIA; 
    }

    lista_sitios->sitios = temp_lista_sitios;
    lista_sitios->sitios[lista_sitios->cantidad] = *nuevo_sitio;
    lista_sitios->cantidad++;

    return OPERACION_EXITOSA;
}


/**
 * @brief Libera la memoria de la lista de sitios.
 * @param lista_sitios Puntero a la lista de sitios a liberar.
 */
void liberar_lista_sitios(ListaSitios *lista_sitios) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        liberar_sitio(&lista_sitios->sitios[i]);
    }

    free(lista_sitios->sitios);
    lista_sitios->sitios = NULL;
    lista_sitios->cantidad = 0;
}


/**
 * @brief Busca un sitio por su nombre en la lista.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param nombre_sitio Nombre del sitio a buscar.
 * @return Puntero al sitio encontrado o NULL.
 */
Sitio *buscar_sitio(ListaSitios *lista_sitios, const char *nombre_sitio) {
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        if (strcmp(lista_sitios->sitios[i].nombre,nombre_sitio) == 0) {
            return &lista_sitios->sitios[i];
        }
    }
    return NULL;
}

/**
 * @brief Carga sitios desde un archivo.
 * @param lista_sitios Puntero a la lista de sitios.
 * @param ruta_archivo Ruta del archivo a cargar.
 * @return Numero de sitios cargados o error.
 */
int cargar_sitios_por_lote(ListaSitios *lista_sitios, const char *ruta_archivo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    char linea[LARGO_MAXIMO_CARACTERES];
    while (fgets(linea,sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';

        char *nombre = strtok(linea, ",");
        char *ubicacion = strtok(NULL,",");
        char *sitio_web = strtok(NULL,",");

        if (nombre && ubicacion) {
            Sitio nuevo_sitio = crear_sitio(nombre,ubicacion,sitio_web);
            int resultado = agregar_sitio(lista_sitios, &nuevo_sitio);
            if (resultado == OPERACION_EXITOSA) {
                printf("Exito: El sitio '%s' se ha agregado con exito.\n", nombre);
            } else if (resultado == OPERACION_FALLIDA_DUPLICADO) {
                printf("Fallo: Ya existe un sitio llamado '%s'.\n", nombre);
            } else if (resultado == OPERACION_FALLIDA_MEMORIA) {
                printf("Fallo: Ocurrio un error al reservar la memoria del sito '%s'.\n", nombre);
            }  
        } 
    }
    fclose(archivo);
    return OPERACION_EXITOSA;
}

/**
 * @brief Muestra la informacion de todos los sitios de la lista.
 * @param lista_sitios Puntero constante a la lista de sitios.
 */
void mostrar_lista_sitios(const ListaSitios *lista_sitios) {
    if (!lista_sitios || lista_sitios->cantidad == 0) {
        printf("No hay sitios registrados.\n");
        return;
    }

    printf("=== Lista de sitios ===\n");
    for (int i = 0; i < lista_sitios->cantidad; i++) {
        Sitio *sitio = &lista_sitios->sitios[i];
        printf("Sitio #%d:\n", i + 1);
        mostrar_sitio(sitio);
    }
}
