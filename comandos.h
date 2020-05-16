#include <stdio.h>
#include <string.h>

void imprimir_uso(){
    // Uso / Comandos posibles
    printf("Uso:\n");
    printf("    conway -h\n    conway -V\n    conway i M N inputfile [-o outputprefix]\n");

    // Opciones
    printf("Opciones:\n");
    printf("    -h, --help    Imprime este mensaje.\n");
    printf("    -V, --version    Da la versión del programa.\n");
    printf("    -o Prefijo de los archivos de salida.\n");

    // Ejemplos
    printf("Ejemplos:\n");
    printf("    conway 10 20 20 glider -o estado\n");
    printf("    Representa 10 iteraciones del Juego de la Vida en una matriz de 20x20,\n");
    printf("    con un estado inicial tomado del archivo ‘‘glider’’.\n");
    printf("    Los archivos de salida se llamarán estado_n.pbm.\n");
    printf("    Si no se da un prefijo para los archivos de salida,\n");
    printf("    3el prefijo será el nombre del archivo de entrada.\n");
    
}

void manejar_comandos(char* opt){
    if ((strcmp(opt, "-h") == 0) || (strcmp(opt, "-help") == 0)) {
        imprimir_uso();
    }
    else if ((strcmp(opt, "-V") == 0) || (strcmp(opt, "--version") == 0)){
        printf("Está utilizando la versión 1 del programa\n");
    }
}