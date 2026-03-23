#ifndef SITIO_H
#define SITIO_H

typedef struct {
    char *nombre;
    char *ubicacion;
    char *sitio_web;
} Sitio;

typedef struct {
    Sitio *lista_sitios;
    int cantidad;
}ListaSitios;


Sitio crear_sitio(const char *nombre, const char* ubicacion, const char *sitio_web);
void liberar_sitio(Sitio *sitio);

ListaSitios crear_lista_sitios();
void agregar_sitio(ListaSitios *lista_sitios, Sitio nuevo_sitio);
void liberar_lista_sitios(ListaSitios *lista_sitios);
int buscar_sitio(ListaSitios *lista_sitios, const char* nombre_sitio);
int cargar_sitios(ListaSitios *lista_sitios, const char *ruta_archivo);
#endif //SITIO_H