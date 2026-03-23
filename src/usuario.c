#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include <string.h>


UsuarioAdministrador crear_usuario() {
    UsuarioAdministrador admin;
    admin.password = NULL;
    admin.usuario = NULL;
    return admin;
}

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

void cifrar(char *cadena, int desplazamiento) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] += desplazamiento;
    }
}

void descifrar(char *cadena, int desplazamiento) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] -= desplazamiento;
    }
}

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
