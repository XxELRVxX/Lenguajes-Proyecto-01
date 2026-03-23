#include <stdio.h>
#include "usuario.h"

int main() {

    UsuarioAdministrador admin = crear_usuario();
    cargar_usuario(&admin);

    printf("Usuario: %s, Contrasenia: %s\n", admin.usuario,admin.password);
    char password[] = "Proyecto1Lenguajes";
    printf("resultado validar acceso: %d", validar_acceso(&admin,"admin",password));
    return 0;
}