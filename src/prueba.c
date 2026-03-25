#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "sitio.h"
#include "evento.h"
#include "lista_eventos.h"

int main() {

    Fecha fecha = crear_fecha(28, 3, 2026);


    Sitio sitio = crear_sitio("Estadio Nacional", "San José", "www.estadio.cr");

 
    Sector vip = crear_sector("VIP", 5, 'V');      
    Sector general = crear_sector("General", 10, 'G'); 
    agregar_sector(&sitio.lista_sectores, &vip);
    agregar_sector(&sitio.lista_sectores, &general);

   
    Evento evento = crear_evento("Concierto Rock", "ProductoraX", fecha, &sitio);


    evento.montos_por_sector[0] = 50000.0f; 
    evento.montos_por_sector[1] = 20000.0f; 

  
    sitio.lista_sectores.sectores[0].asientos.asientos[0].estado = ASIENTO_VENDIDO;
    sitio.lista_sectores.sectores[0].asientos.asientos[1].estado = ASIENTO_VENDIDO;

   
    sitio.lista_sectores.sectores[1].asientos.asientos[3].estado = ASIENTO_VENDIDO;
    sitio.lista_sectores.sectores[1].asientos.asientos[4].estado = ASIENTO_VENDIDO;
    sitio.lista_sectores.sectores[1].asientos.asientos[5].estado = ASIENTO_VENDIDO;

   
    ListaEventos lista = crear_lista_eventos();
    agregar_evento(&lista, &evento);

    
    mostrar_lista_eventos(&lista);

    printf("\nEstado del evento:\n");
    estado_evento(&evento);

    liberar_lista_eventos(&lista);
    liberar_sitio(&sitio);

    return 0;
}
