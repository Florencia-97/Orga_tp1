#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cmd_line_parser.h"
#include "tablero.h"
#include "params_t.h"

/*
Parámetros recibidos:
i -> cantidad de archivos a escribir
M -> coordenada x
N -> coordenada y
path -> nombre archivo */

int main(int argc, char *argv[])
{
    params_t params;

    if (parse_cmd_line(argc, argv, &params) == outERROR)
    {
        exit(EXIT_FAILURE);
    }

    tablero_t *tablero = tablero_crear(params.M, params.N);
    tablero_cargar_tablero(tablero, &params);

    int n = 0;
    for (n = 1; n <= params.i; ++n)
    {
        tablero_imprimir(tablero, n, &params);
        tablero = tablero_modificar(tablero);
    }

    tablero_eliminar(tablero);
    printf("Listo.\n");

    return EXIT_SUCCESS;
}