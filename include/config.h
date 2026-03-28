#ifndef CONFIG_H
#define CONFIG_H

//constanes 


#define LARGO_MAXIMO_CARACTERES 256
#define BUFFER_LECTURA_LINEA 1000


//Usuario
#define ARCHIVO_USUARIO "data/usuario.txt"
#define DESPLAZAMIENTO_CIFRADO 4
#define ACCESO_CORRECTO 0
#define PASSWORD_INCORRECTA 1
#define USUARIO_INCORRECTO 2
#define USUARIO_Y_PASSWORD_LEIDOS 2


//General
#define OPERACION_FALLIDA -1
#define OPERACION_EXITOSA 0
#define OPERACION_FALLIDA_DUPLICADO 1
#define OPERACION_FALLIDA_MEMORIA 2

//Asiento
#define ASIENTO_DISPONIBLE 0
#define ASIENTO_VENDIDO 1

//Factura
#define COSTO_SERVICIO_PORC 0.05f

//fecha
#define ANIO_MINIMO 2026
#define FECHA_INVALIDA -1
#define FECHA_VALIDA 0

//programa
#define RUTA_ALMACENAMIENTO_EVENTOS "data/eventos.txt"
#define RUTA_ALMACENAMIENTO_SITIOS  "data/sitios.txt"
#define RUTA_ALMACENAMIENTO_FACTURAS "data/facturas.txt"

//leer numero
#define ENTRADA_INVALIDA -1
#define ENTRADA_VALIDA 1


#endif //CONFIG_H