#include "tablero.h"

/* Para facilitar la tarea de mips, la grilla es realmente
una lista que es luego tratada como un grilla */
tablero_t *tablero_crear(int length, int height)
{
	/* TODO: check malloc and calloc errors. */
	tablero_t *tablero =
	    (tablero_t *)malloc(sizeof(tablero_t));
	if (tablero == NULL)
	{
		fprintf(stderr, ERROR_MEMORY_REQUEST);
		return NULL;
	}
	tablero->tabla = (unsigned char *)calloc(
	    height * length, sizeof(unsigned char));

	if (tablero->tabla == NULL)
	{
		fprintf(stderr, ERROR_MEMORY_REQUEST);
		return NULL;
	}
	tablero->l = length;
	tablero->h = height;
	return tablero;
}

/* Carga el tablero a partir del nombre de archivo pasado
por parámetro. Devuelve 0 si se cargó correctamente, otro en
caso de error.
*/
int tablero_cargar_tablero(tablero_t *self,
                           params_t *params)
{
	if (params->inputStream == NULL)
	{
		fprintf(stderr, ERROR_INVALID_INPUT_STREAM);
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,MSG_READING_INIT_STATE);
	char buffer[4];
	while (fgets(buffer, 100, params->inputStream) != NULL)
	{
		int fila = buffer[0] - '0';
		int col = buffer[2] - '0';
		self->tabla[fila * self->l + col] = 1;
	}
	fclose(params->inputStream);

	return 0;
}

/* Llena campo indicado del tablero
de no ser posible modificar su valor retorna 1,
0 en caso de modificarlo correctamente. */
void tablero_modificar_estado_campo(tablero_t *self,
                                    int fila, int col)
{
	int actual = self->tabla[fila * self->l + col];
	actual == 0 ? (self->tabla[fila * self->l + col] = 1)
	            : (self->tabla[fila * self->l + col] = 0);
}

void tablero_imprimir(tablero_t *self, int iteracion,
                      params_t *params)
{
	if (params->outputStream == stdout)
	{
		int i = 0;
		for (i = 0; i < self->h; i++)
		{
			int j = 0;
			for (j = 0; j < self->l; j++)
			{
				printf("%i ", self->tabla[i * self->l + j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		char filename[sizeof("pref100.pbm") + MAX_SIZE_PREFIX];
		sprintf(filename, "../output/%s%03d.pbm",
		        params->prefix, iteracion);
		FILE *fp = fopen(filename, "wb");
		if (fp == NULL)
		{
			fprintf(stderr,ERROR_OUTPUT_STREAM_WRITING_MSG);
		}
		fprintf(stdout,MSG_RECORDING);
		printf(" %s\n", filename);

		/* Negro */
		static unsigned char color_vivo[3] = {0, 0, 0};
		/* Blanco */
		static unsigned char color_muerto[3] = {255, 255, 255};
		(void)fprintf(fp, "P6\n%d %d\n255\n",
		              self->l * ZOOM_ARCHIVO,
		              self->h * ZOOM_ARCHIVO);

		int i = 0;
		for (i = 0; i < (self->h * ZOOM_ARCHIVO); i++)
		{
			int j = 0;
			for (j = 0; j < (self->l * ZOOM_ARCHIVO); j++)
			{
				int x = i / ZOOM_ARCHIVO;
				int y = j / ZOOM_ARCHIVO;
				int vivo = self->tabla[x * self->l + y];
				if (vivo)
				{
					(void)fwrite(color_vivo, 1, 3, fp);
				}
				else
				{
					(void)fwrite(color_muerto, 1, 3, fp);
				}
			}
		}
		fclose(fp);
	}
}

tablero_t *tablero_modificar(tablero_t *self)
{
	tablero_t *tablero_nuevo =
	    tablero_crear(self->l, self->h);
	if (!tablero_nuevo) return NULL;
	int i = 0;
	for (i = 0; i < self->h; i++)
	{
		int j = 0;
		for (j = 0; j < self->l; j++)
		{
			unsigned int v =
			    vecinos(&self->tabla[0], i, j, self->l, self->h);
			int viva = self->tabla[i * self->l + j];
			if ((v < 2) || (v > 3))
			{
				tablero_nuevo->tabla[i * self->l + j] = 0;
			}
			if (viva && (v == 2 || v == 3))
			{
				tablero_nuevo->tabla[i * self->l + j] = 1;
			}
			if (!viva && v == 3)
			{
				tablero_nuevo->tabla[i * self->l + j] = 1;
			}
		}
	}
	/* Ahora lo elimino */
	tablero_eliminar(self);
	return tablero_nuevo;
}

/* Elimina el talbero creado */
void tablero_eliminar(tablero_t *self)
{
	free(self->tabla);
	free(self);
}