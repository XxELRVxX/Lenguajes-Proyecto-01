#ifndef USUARIO_H
#define USUARIO_H

#include "config.h"

typedef struct {
    char usuario[LARGO_MAXIMO_USUARIO];
    char password[LARGO_MAXIMO_PASSWORD];
} UsuarioAdministrador;

void cargar_usuario(UsuarioAdministrador *admin);
int validar_acceso(UsuarioAdministrador *admin, const char *usuario_ingresado,
     const char *password_ingresada);
void cifrar(char *texto, const char *clave);
     
#endif //USUARIO_H