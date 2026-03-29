#include "../include/programa.h"

int main() {
    Programa programa = crear_programa();
    cargar_programa(&programa);
    ejecutar_programa(&programa);
    liberar_programa(&programa);
    return 0;
}
