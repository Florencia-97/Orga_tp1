#include <stdio.h>
#include <stdlib.h>

#include "comandos.h"

// Parámetros recibidos:
// i -> cantidad de archivos a escribir
// M -> coordenada x
// N -> coordenada y
// path -> nombre archivo

int main(int argc, char* argv[]){
    if (argc == 2){
        manejar_comandos(argv[1]);
        return 0;
    }
    if (argc != 5) return 1;
    return 0;
}