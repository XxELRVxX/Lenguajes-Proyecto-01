
/**
 * @file lista_asientos.c
 * @brief Implementación de las funciones para el manejo de listas de asientos.
 */

#include "lista_asientos.h"

/**
 * @brief Crea una lista de asientos con una cantidad y letra inicial.
 * @param cantidad Número de asientos que hay que crear.
 * @param inicial Letra inicial para los asientos.
 * @return ListaAsientos inicializada.
 */
ListaAsientos crear_lista_asientos(int cantidad, char inicial) {
    ListaAsientos lista_asientos;
    lista_asientos.cantidad_asientos = cantidad;
    lista_asientos.asientos = malloc(cantidad * sizeof(Asiento));

    for (int i = 0; i < cantidad; i++) {
        char numero_asiento[10];
        sprintf(numero_asiento,"%c%d", inicial, i+1);
        lista_asientos.asientos[i] = crear_asiento(numero_asiento);
    }
    return lista_asientos;
}

/**
 * @brief Crea una lista de asientos vacía.
 * @return ListaAsientos vacía.
 */
ListaAsientos crear_lista_asientos_vacia() {
    ListaAsientos lista;
    lista.asientos = NULL;
    lista.cantidad_asientos = 0;
    return lista;
}

/**
 * @brief Agrega un asiento a la lista de forma dinamica.
 * @param lista_asientos Puntero a la lista de asientos.
 * @param asiento Puntero al asiento que se va a agregar.
 * @return Código de exito o error.
 */
int agregar_asiento_a_lista(ListaAsientos *lista_asientos, Asiento *asiento) {
    if (buscar_asiento(lista_asientos, asiento->numero_asiento) != NULL) {
        liberar_asiento(asiento);
        return OPERACION_FALLIDA_DUPLICADO;
    }

    Asiento *temp_lista_asientos = realloc(lista_asientos->asientos, (lista_asientos->cantidad_asientos + 1) * sizeof(Asiento));
    if (temp_lista_asientos == NULL) {
        liberar_asiento(asiento);
        return OPERACION_FALLIDA_MEMORIA;
    }
    lista_asientos->asientos = temp_lista_asientos;
    lista_asientos->asientos[lista_asientos->cantidad_asientos] = *asiento;
    lista_asientos->cantidad_asientos++;
    return OPERACION_EXITOSA;
}

/**
 * @brief Libera la memoria de la lista de asientos.
 * @param lista_asientos Puntero a la lista de asientos por liberar.
 */
void liberar_lista_asientos(ListaAsientos *lista_asientos) {
    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        liberar_asiento(&lista_asientos->asientos[i]);
    }
    free(lista_asientos->asientos);
    lista_asientos->asientos = NULL;
    lista_asientos->cantidad_asientos = 0;

}

/**
 * @brief Resetea la lista de asientos a estado inicial.
 * @param lista_asientos Puntero a la lista de asientos a resetear.
 */
void resetear_lista_asientos(ListaAsientos *lista_asientos) {
    for (int i = 0; i<lista_asientos->cantidad_asientos; i++) {
        desocupar_asiento(&lista_asientos->asientos[i]);
    }
}

/**
 * @brief Muestra la informacion de todos los asientos de la lista.
 * @param lista_asientos Puntero constante a la lista a mostrar.
 */
void mostrar_lista_asientos(const ListaAsientos *lista_asientos) {
    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        informacion_asiento(&lista_asientos->asientos[i]);
    }
}

/**
 * @brief Busca un asiento por su numero en la lista.
 * @param lista_asientos Puntero a la lista de asientos.
 * @param numero_asiento Numero identificador del asiento.
 * @return Puntero al asiento encontrado o NULL.
 */
Asiento *buscar_asiento(ListaAsientos *lista_asientos, const char *numero_asiento) {
    for (int i = 0; i<lista_asientos->cantidad_asientos; i ++) {
        if (strcmp(lista_asientos->asientos[i].numero_asiento,numero_asiento) == 0) {
            return &lista_asientos->asientos[i];
        }
    }
    return NULL; 
}

/**
 * @brief Obtiene un asiento por su indice en la lista.
 * @param lista_asientos Puntero constante a la lista.
 * @param indice Posicion del asiento en la lista.
 * @return Puntero al asiento correspondiente o NULL si el indice no es valido.
 */
Asiento *obtener_asiento(const ListaAsientos *lista_asientos, int indice) {
    if (!lista_asientos || indice < 0 || indice >= lista_asientos->cantidad_asientos) {
        return NULL;
    } else {
        return &lista_asientos->asientos[indice];
    }
}

/**
 * @brief Cuenta la cantidad de asientos disponibles en la lista.
 * @param lista_asientos Puntero constante a la lista.
 * @return Numero de asientos disponibles.
 */
int contar_asientos_disponibles(const ListaAsientos *lista_asientos) {
    int disponibles = 0;

    for (int i = 0; i < lista_asientos->cantidad_asientos; i++) {
        if (lista_asientos->asientos[i].estado == ASIENTO_DISPONIBLE) {
            disponibles++;
        }
    }
    return disponibles;
}

/**
 * @brief Crea una copia de la lista de asientos.
 * @param lista_original Puntero constante a la lista original.
 * @return Copia de la lista de asientos.
 */
ListaAsientos copiar_lista_asientos(const ListaAsientos *lista_original) {
    ListaAsientos copia;
    copia.cantidad_asientos = lista_original->cantidad_asientos;
    copia.asientos = malloc(copia.cantidad_asientos * sizeof(Asiento));

    for (int i = 0; i < copia.cantidad_asientos; i++) {
        copia.asientos[i].numero_asiento = malloc(strlen(lista_original->asientos[i].numero_asiento) + 1);
        strcpy(copia.asientos[i].numero_asiento, lista_original->asientos[i].numero_asiento);
        copia.asientos[i].estado = ASIENTO_DISPONIBLE;
    }
    return copia;
}
