/*--------------------------------------------------------------

DESCRIPCION

----------------------------------------------------------- */
#ifndef TABLERO__H
#define TABLERO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "params_t.h"
#include "vecinos.h"

/* Mantener un número múltiplo de 10 */
#define ZOOM_ARCHIVO 30

typedef struct tablero
{
    unsigned char *tabla;
    int l;
    int h;
} tablero_t;

void tablero_eliminar(tablero_t *self);
tablero_t *tablero_crear(int length, int height);
int tablero_cargar_tablero(tablero_t *self, params_t *params);
void tablero_modificar_estado_campo(tablero_t *self, int fila, int col);
void tablero_imprimir(tablero_t *self, int iteracion, params_t *params);
int mod(int x, int m);
unsigned int vecinos_c(unsigned char *a, unsigned int i, unsigned int j,
                       unsigned int M, unsigned int N);
unsigned int vecinos_mips(unsigned char *a, unsigned int i, unsigned int j,
                          unsigned int M, unsigned int N);
tablero_t *tablero_modificar(tablero_t *self);
void tablero_eliminar(tablero_t *self);

#endif