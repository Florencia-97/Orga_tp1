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

#ifdef MEASURE_EXEC_TIMES
size_t times_called;
double mean_time;
#endif

int main(int argc, char *argv[])
{
	params_t params;

	if (parse_cmd_line(argc, argv, &params) == outERROR)
	{
		exit(EXIT_FAILURE);
	}

#ifdef MEASURE_EXEC_TIMES
#include "shared.h"
	times_called = 0;
	mean_time = 0;
	FILE *time_measurements_fp =
	    fopen("time_measurements.txt", "w");
	if (time_measurements_fp == NULL)
	{
		fprintf(stderr, ERROR_OUTPUT_STREAM_WRITING_MSG);
	}
#endif

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

#ifdef MEASURE_EXEC_TIMES
	fprintf(stdout, "Mean time: %.2f [us] for %d iterations.\n", mean_time,times_called);
	fprintf(time_measurements_fp, "Mean time: %.2f [us] for %d iterations.\n", mean_time,times_called);
	if (time_measurements_fp != NULL)
	{
		fclose(time_measurements_fp);
	}
#endif

	return EXIT_SUCCESS;
}
