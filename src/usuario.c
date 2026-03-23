#include <stdio.h>
#include <string.h>
#include "usuario.h"
#include <string.h>

void cargar_usuario(UsuarioAdministrador *admin) {
    FILE *archivo = fopen(ARCHIVO_USUARIO, "r");
    if (!archivo) {
        printf("Error: No se puedo abrir el archivo de usuario \n");
        return;
    }
    fscanf(archivo, "%29[^,],%29s", admin->usuario,admin->password);
    fclose(archivo);
}

void cifrar_decifrar(char *cadena, const char *llave) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] ^= llave[i % strlen(llave)];
    }
}

int validar_acceso(UsuarioAdministrador *admin,const char *usuario_ingresado,
    const char *password_ingresada) {
        
    char password_descifrada[LARGO_MAXIMO_PASSWORD];
    strcpy(password_descifrada,admin->password);

    cifrar_decifrar(password_descifrada, CLAVE_CIFRADO);

    if (strcmp(admin->usuario,usuario_ingresado) != 0){
        return USUARIO_INCORRECTO;

    } else if (strcpm(password_descifrada, password_ingresada) != 0) {
        return PASSWORD_INCORRECTA;

    } else {
        return ACCESO_CORRECTO;
    }
 

}
