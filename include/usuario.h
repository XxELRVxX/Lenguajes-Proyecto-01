/**
 * @file usuario.h
 * @brief Definicion de la estructura y funciones para el manejo de usuarios administradores.
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "config.h"

/**
 * @struct UsuarioAdministrador
 * @brief Estructura que representa un usuario administrador.
 */
typedef struct {
    char *usuario; /**< Nombre de usuario */
    char *password; /**< Contraseña cifrada */
} UsuarioAdministrador;


/**
 * @brief Crea un usuario administrador vacio.
 * @return UsuarioAdministrador inicializado.
 */
UsuarioAdministrador crear_usuario();

/**
 * @brief Carga los datos de un usuario administrador.
 * @param admin Puntero al usuario administrador.
 */
void cargar_usuario(UsuarioAdministrador *admin);

/**
 * @brief Valida el acceso de un usuario.
 * @param admin Puntero al usuario administrador.
 * @param usuario_ingresado Nombre de usuario ingresado.
 * @param password_ingresada Contraseña ingresada.
 * @return 1 si es valido, 0 si no.
 */
int validar_acceso(UsuarioAdministrador *admin, const char *usuario_ingresado,
     const char *password_ingresada);

/**
 * @brief Cifra un texto usando desplazamiento.
 * @param texto Texto a cifrar.
 * @param desplazamiento Valor de desplazamiento.
 */
void cifrar(char *texto, int desplazamiento);

/**
 * @brief Descifra un texto usando desplazamiento.
 * @param texto Texto a descifrar.
 * @param desplazamiento Valor de desplazamiento.
 */
void descifrar(char *texto, int desplazamiento);

/**
 * @brief Liberar la memoria asociada a un usuario
 * @param usuario Puntero al usuario a liberar.
 */
void liberar_usuario(UsuarioAdministrador *usuario);
     
#endif //USUARIO_H