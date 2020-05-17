#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "comandos.h"
#include "tablero.h"

bool POR_ARCHIVO = true;

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
    int i = atoi(argv[1]);
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);
    char* path = argv[4];

    //tablero inicial
    tablero_t* tablero = tablero_crear(M, N);
    tablero_cargar_tablero(tablero, path);  

    for (int n = 1; n <= i; ++n){
        tablero_imprimir(tablero, n, POR_ARCHIVO); 
        tablero = tablero_modificar(tablero);
    }
    tablero_eliminar(tablero);
    return 0;
}