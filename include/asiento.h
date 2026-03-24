#ifndef ASIENTO_H
#define ASIENTO_H

typedef struct {
    char *numero_asiento;
    int estado; 
}Asiento;


Asiento crear_asiento(const char *numero_asiento);
void liberar_asiento(Asiento *asiento);
int vender_asiento(Asiento *asiento);
void desocupar_asiento(Asiento *asiento);
void informacion_asiento(const Asiento *asiento);

#endif // ASIENTO_H
