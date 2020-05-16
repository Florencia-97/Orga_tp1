#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tablero{
   int** tabla;
   int l;
   int h;
}tablero_t;

tablero_t* tablero_crear(int length, int height){
    tablero_t* tablero = (tablero_t*) malloc(sizeof(tablero_t));
    tablero->tabla = (int**) malloc(height * sizeof(int *));
    for (int i=0 ; i< height ; i++) tablero->tabla[i] = (int*) malloc(length*sizeof(int));
    tablero->l = length;
    tablero->h = height;
    return tablero;
}

// Carga el tablero a partir del nombre de archivo pasado por parámetro
// Devuelve 0 si se cargó correctamente, otro en caso de error.
int tablero_cargar_tablero(tablero_t* self, char* path){
    FILE* fp = fopen(path, "r");
    char buffer[4];
    while (fgets(buffer, 100, fp) != NULL){
        int fila = buffer[0] - '0';
        int columna = buffer[2] - '0';
        self->tabla[fila][columna] = 1;
    }
    fclose(fp);
    return 0;
}

// Llena campo indicado del tablero
// de no ser posible modificar su valor retorna 1,
// 0 en caso de modificarlo correctamente.
void tablero_modificar_estado_campo(tablero_t* self, int fila, int col){
    int actual = self->tabla[fila][col];
    actual == 0 ? (self->tabla[fila][col] = 1) : (self->tabla[fila][col] = 0);
}

// Recive una buffer el cual es completado con la representación
// del tablero, lista para ser impresa.
void tablero_imprimir(tablero_t* self){
    for (int i=0 ; i< self->h ; i++){
        for (int j=0 ; j< self->l ; j++){
            printf("%i ", self->tabla[i][j]);
        }
        printf("\n");
    }
}


// Elimina el talbero creado
void tablero_eliminar(tablero_t* self){
    for (int i=0 ; i< self->h ; i++) free(self->tabla[i]);
    free(self->tabla);
    free(self);
}
