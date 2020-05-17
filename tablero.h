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

void tablero_eliminar(tablero_t* self);

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
    printf("\n"); 
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

unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j,
                    unsigned int M, unsigned int N);


int mod(int x, int m) {
    int r = x%m;
    return r<0 ? r+m : r;
}

unsigned int vecinos_c(int** a, unsigned int i, unsigned int j,
                    unsigned int M, unsigned int N){
    int contador = 0;
    for (int c1 = -1; c1 <= 1; ++c1){
        int f = mod( i + c1 , N);
        for (int c2 = -1; c2 <= 1; ++c2){
            if (c1 == 0 && c2 == 0) continue;
            int c = mod( j + c2, M);
            if (a[f][c] == 1) contador++;
        }
    }
    return contador;
}

tablero_t* tablero_modificar(tablero_t* self){
    tablero_t* tablero_nuevo = tablero_crear(self->l, self->h);
    for (int i=0 ; i< self->h ; i++){
        for (int j=0 ; j< self->l ; j++){
            unsigned int vecinos = vecinos_c(self->tabla, i, j, self->l, self->h);
            int viva = self->tabla[i][j];
            if ((vecinos < 2) || (vecinos > 3))
                tablero_nuevo->tabla[i][j] = 0;
            if (viva && (vecinos == 2 || vecinos == 3))
                tablero_nuevo->tabla[i][j] = 1;
            if (!viva && vecinos == 3){
                tablero_nuevo->tabla[i][j] = 1;
            }
        }
    }
    // Ahora lo elimino
    tablero_eliminar(self);
    return tablero_nuevo;
}

// Elimina el talbero creado
void tablero_eliminar(tablero_t* self){
    for (int i=0 ; i< self->h ; i++) free(self->tabla[i]);
    free(self->tabla);
    free(self);
}