#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmd_line_parser.h"
#include "messages.h"
#include "params_t.h"
#include "tablero.h"

/*
For memory leaks checking, precede the program call with the
following commands:

valgrind  --tool=memcheck --leak-check=full
--show-leak-kinds=all -v ./conway 10 20 20 glider -o estado

*/

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
	fprintf(stdout, MSG_READY);

	return EXIT_SUCCESS;
}