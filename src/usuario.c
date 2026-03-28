/**
 * @file usuario.c
 * @brief Implementacion funciones para el manejo de usuarios administradores.
 */

#include "usuario.h"


/**
 * @brief Crea un usuario administrador vacio.
 * @return UsuarioAdministrador inicializado.
 */
UsuarioAdministrador crear_usuario() {
    UsuarioAdministrador admin;
    admin.password = NULL;
    admin.usuario = NULL;
    return admin;
}

/**
 * @brief Carga los datos de un usuario administrador.
 * @param admin Puntero al usuario administrador.
 */
void cargar_usuario(UsuarioAdministrador *admin) {
    FILE *archivo = fopen(ARCHIVO_USUARIO, "r");
    if (!archivo) {
        printf("Error: No se puedo abrir el archivo de usuario \n");
        return;
    }

    char usuario_tmp[LARGO_MAXIMO_CARACTERES];
    char password_tmp[LARGO_MAXIMO_CARACTERES];
    
    if (fscanf(archivo, "%255[^,],%255s",usuario_tmp, 
        password_tmp) == USUARIO_Y_PASSWORD_LEIDOS) {

        admin->usuario = realloc(admin->usuario, strlen(usuario_tmp ) + 1);
        admin->password = realloc(admin->password, strlen(password_tmp) + 1);

        strcpy(admin->usuario,usuario_tmp);
        strcpy(admin->password, password_tmp);
    }   
    fclose(archivo);
}

/**
 * @brief Valida el acceso de un usuario.
 * @param admin Puntero al usuario administrador.
 * @param usuario_ingresado Nombre de usuario ingresado.
 * @param password_ingresada Contraseña ingresada.
 * @return 1 si es valido, 0 si no.
 */
int validar_acceso(UsuarioAdministrador *admin,const char *usuario_ingresado,
    const char *password_ingresada) {
        
    char *password_descifrada = malloc(strlen(admin->password) + 1);
    strcpy(password_descifrada,admin->password);
    descifrar(password_descifrada, DESPLAZAMIENTO_CIFRADO);


    int resultado; 
    if (strcmp(admin->usuario,usuario_ingresado) != 0) {
        resultado = USUARIO_INCORRECTO;

    } else if (strcmp(password_descifrada, password_ingresada) != 0) {
        resultado = PASSWORD_INCORRECTA;

    } else {
        resultado = ACCESO_CORRECTO;
    }

    free(password_descifrada);
    return resultado;
}

/**
 * @brief Cifra un texto usando desplazamiento.
 * @param texto Texto a cifrar.
 * @param desplazamiento Valor de desplazamiento.
 */
void cifrar(char *cadena, int desplazamiento) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] += desplazamiento;
    }
}

/**
 * @brief Descifra un texto usando desplazamiento.
 * @param texto Texto a descifrar.
 * @param desplazamiento Valor de desplazamiento.
 */
void descifrar(char *cadena, int desplazamiento) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] -= desplazamiento;
    }
}

/**
 * @brief Liberar la memoria asociada a un usuario
 * @param usuario Puntero al usuario a liberar.
 */
void liberar_usuario(UsuarioAdministrador *usuario) {
    if (usuario->password) {
        free(usuario->password);
    }
    if (usuario->usuario) {
        free(usuario->usuario);
    }
}

