#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "programa.h"
#include "sitio.h"
#include "sector.h"
#include "lista_sectores.h"
#include "lista_sitios.h"
#include "evento.h"
#include "lista_eventos.h"
#include "lista_asientos.h"
#include "factura.h"
#include "lista_facturas.h"
#include "cargar_guardar.h"
#include "config.h"
#include "asiento.h"

int main(void) {
    Programa programa = crear_programa();

    Sitio sitio = crear_sitio("Estadio Nacional", "San José", "www.estadionacional.example");

    Sector sector_vip = crear_sector("VIP", 5, 'V');
    sector_vip.asientos = crear_lista_asientos(5, 'V');
    agregar_sector(&sitio.lista_sectores, &sector_vip);

    Sector sector_general = crear_sector("General", 10, 'G');
    sector_general.asientos = crear_lista_asientos(10, 'G');
    agregar_sector(&sitio.lista_sectores, &sector_general);

    agregar_sitio(&programa.sitios, &sitio);


    Fecha fecha_evento = crear_fecha(25, 3, 2026);
    Evento evento = crear_evento("Concierto Rock", "LiveNation", fecha_evento, &programa.sitios.sitios[0]);

    evento.montos_por_sector[0] = 150.0f; 
    evento.montos_por_sector[1] = 50.0f;  

  
    Asiento *a = buscar_asiento(&evento.asientos_por_sector[0], "V1");
    if (a) vender_asiento(a);
    a = buscar_asiento(&evento.asientos_por_sector[1], "G3");
    if (a) vender_asiento(a);
    a = buscar_asiento(&evento.asientos_por_sector[1], "G5");
    if (a) vender_asiento(a);

    agregar_evento(&programa.eventos, &evento);

    
    ListaAsientos asientos_comprados = crear_lista_asientos_vacia();
    Asiento *asiento_v1 = buscar_asiento(&programa.eventos.eventos[0].asientos_por_sector[0], "V1");
    if (asiento_v1) {
        Asiento copia = crear_asiento(asiento_v1->numero_asiento);
        copia.estado = asiento_v1->estado;
        agregar_asiento_a_lista(&asientos_comprados, &copia);
    }
    Asiento *asiento_g3 = buscar_asiento(&programa.eventos.eventos[0].asientos_por_sector[1], "G3");
    if (asiento_g3) {
        Asiento copia = crear_asiento(asiento_g3->numero_asiento);
        copia.estado = asiento_g3->estado;
        agregar_asiento_a_lista(&asientos_comprados, &copia);
    }

    Fecha fecha_compra = crear_fecha(25, 3, 2026);
    Factura factura = crear_factura(&programa.eventos.eventos[0], &fecha_compra,
                                    "123456789", "Juan Perez", &asientos_comprados);
    agregar_factura(&programa.facturas, &factura);
    liberar_lista_asientos(&asientos_comprados);

    
    printf("=== Estado en memoria antes de guardar ===\n");
    mostrar_lista_sitios(&programa.sitios);
    mostrar_lista_eventos(&programa.eventos);
    estado_evento(&programa.eventos.eventos[0]); // para ver los asientos vendidos hay que acceder a los de eventos, no desde sitio.
    mostrar_lista_facturas(&programa.facturas);

    
    guardar_sitios(&programa.sitios, RUTA_ALMACENAMIENTO_SITIOS);
    guardar_eventos(&programa.eventos, RUTA_ALMACENAMIENTO_EVENTOS);
    guardar_facturas(&programa.facturas, RUTA_ALMACENAMIENTO_FACTURAS);

    
    liberar_programa(&programa);
    Programa cargado = crear_programa();
    
    cargar_programa(&cargado);

    // 8) Mostrar estado recargado
    printf("\n=== Estado recargado desde archivos ===\n");
    mostrar_lista_sitios(&cargado.sitios);
    mostrar_lista_eventos(&cargado.eventos);
    estado_evento(&cargado.eventos.eventos[0]); 
    mostrar_lista_facturas(&cargado.facturas);


    printf("=== Estado en memoria despues de recargar ===\n");
    mostrar_lista_sitios(&cargado.sitios);
    mostrar_lista_eventos(&cargado.eventos);
    estado_evento(&cargado.eventos.eventos[0]); // para ver los asientos vendidos hay que acceder a los de eventos, no desde sitio.
    mostrar_lista_facturas(&cargado.facturas);

    liberar_programa(&cargado);
    printf("\nPruebas finalizadas.\n");
    return 0;
}
