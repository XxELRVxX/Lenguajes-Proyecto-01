#include <stdio.h>
#include "usuario.h"

int main() {

    UsuarioAdministrador admin;
    cargar_usuario(&admin);

    printf("Usuario: %s, Contrasenia: %s", admin.usuario,admin.password);

    return 0;
}