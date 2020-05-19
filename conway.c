#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "comandos.h"
#include "tablero.h"

bool IMPRESION_POR_ARCHIVO = true;

// Parámetros recibidos:
// i -> cantidad de archivos a escribir
// M -> coordenada x
// N -> coordenada y
// path -> nombre archivo

int main(int argc, char* argv[]){
    char* prefijo = "pref"; // nombre archivos de salida, pref si no se especifica otro por terminal
    
    if (argc == 2){
        manejar_comandos(argv[1]);
        return 0;
    }

    if (argc < 5) return 1;
    int i = atoi(argv[1]);
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);
    char* path = argv[4];

    if ((argc == 7 ) && (strcmp(argv[5], "-o") == 0)) prefijo = argv[6];

    //tablero inicial
    tablero_t* tablero = tablero_crear(M, N);
    if (!tablero) return 1;
    tablero_cargar_tablero(tablero, path);  

    for (int n = 1; n <= i; ++n){
        tablero_imprimir(tablero, n, IMPRESION_POR_ARCHIVO, prefijo); 
        tablero = tablero_modificar(tablero);
        if (!tablero) return 1;
    }

    tablero_eliminar(tablero);
    return 0;
}