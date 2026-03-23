#ifndef USUARIO_H
#define USUARIO_H


typedef struct {
    char *usuario;
    char *password;
} UsuarioAdministrador;

UsuarioAdministrador crear_usuario();
void cargar_usuario(UsuarioAdministrador *admin);
int validar_acceso(UsuarioAdministrador *admin, const char *usuario_ingresado,
     const char *password_ingresada);
void cifrar(char *texto, int desplazamiento);
void descifrar(char *texto, int desplazamiento);
     
#endif //USUARIO_H