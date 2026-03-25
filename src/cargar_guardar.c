#include "cargar_guardar.h"

//guardar
int guardar_sitios(const ListaSitios *lista_sitios, const char *ruta) {
    FILE *archivo = fopen(ruta,"w");

    if (!archivo) {
        return OPERACION_FALLIDA;
    }

    //guardar sitio
    for (int i = 0; i<lista_sitios->cantidad; i++) {
        Sitio *sitio = &lista_sitios->sitios[i];
        fprintf(archivo, "%s|%s|",sitio->nombre,sitio->ubicacion);
        if (sitio->sitio_web && strlen(sitio->sitio_web) > 0) {
            fprintf(archivo, "%s",sitio->sitio_web);
        }  
        
        //guardar sectores asociados al sitio
        for (int j = 0; j < sitio->lista_sectores.cantidad_sectores; j++) {
            Sector *sector = &sitio->lista_sectores.sectores[j]; 
            fprintf(archivo,",SECTOR|%s|%c|%d",sector->nombre,sector->inicial,sector->cantidad_asientos);


            //guardar asientos asociados al sector
            for (int k = 0; k < sector->cantidad_asientos; k++) {
                Asiento *asiento = &sector->asientos.asientos[k];
                fprintf(archivo, ",ASIENTO|%s|%d", asiento->numero_asiento,asiento->estado);
            }
        }
        fprintf(archivo,"\n");
    }
}