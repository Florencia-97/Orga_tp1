#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int ZOOM_ARCHIVO = 30; // Mantener un número múltiplo de 10

typedef struct tablero{
   int** tabla;
   int l;
   int h;
}tablero_t;

tablero_t* tablero_crear(int length, int height){
    tablero_t* tablero = (tablero_t*) malloc(sizeof(tablero_t));
    tablero->tabla = (int**) malloc(height * sizeof(int *));
    for (int i=0 ; i<height ; i++) {
        tablero->tabla[i] = (int*) malloc(length*sizeof(int));
        for (int j=0; j<length; j++)
            tablero->tabla[i][j] = 0;
    }
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

void imprimir_terminal(tablero_t* self){
       for (int i=0 ; i< self->h ; i++){
        for (int j=0 ; j< self->l ; j++){
            printf("%i ", self->tabla[i][j]);
        }
        printf("\n");
    } 
}

void imprimir_archivo(tablero_t* self, int i){
    char filename[sizeof "pref100.pbm"];
    sprintf(filename, "pref%03d.pbm", i);
    FILE* fp = fopen(filename, "wb");

    static unsigned char color_vivo[3] = {255,0,0};
    static unsigned char color_muerto[3] = {0,0,255};
    (void) fprintf(fp, "P6\n%d %d\n255\n", self->l*ZOOM_ARCHIVO, self->h*ZOOM_ARCHIVO);
    
    for (int i=0 ; i<(self->h * ZOOM_ARCHIVO) ; i++){
        for (int j=0 ; j< (self->l * ZOOM_ARCHIVO) ; j++){
            int x  = i / ZOOM_ARCHIVO;
            int y = j / ZOOM_ARCHIVO;
            printf("%i %i", x, y);
            int vivo = self->tabla[x][y];
            if (vivo)
                (void) fwrite(color_vivo, 1, 3, fp);
            else
                (void) fwrite(color_muerto, 1, 3, fp);
        }
    }
    fclose(fp);
}

// Si archivo es true se imprime el tablero en un archivo
// Caso contraio, por terminal
void tablero_imprimir(tablero_t* self, int i, bool archivo){
    archivo ? imprimir_archivo(self, i) : imprimir_terminal(self);
}

// Elimina el talbero creado
void tablero_eliminar(tablero_t* self){
    for (int i=0 ; i< self->h ; i++) free(self->tabla[i]);
    free(self->tabla);
    free(self);
}
