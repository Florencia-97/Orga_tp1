## 66.20 Organización de computadoras - 1C2020
## TP1: Conjunto de instrucciones MIPS.

### Compilación utilizando archivos .c
Posicionarse en el directorio 'src/' y ejecutar:
```
make
```

### Compilación utilizando archivos .S
Si se quiere utilizar los archivos codificados en ASM MIPS32, ejecutar
```
make use_S_files
```

### Compilación para realizar mediciones de tiempo promedio de ejecución
Para utilizar las funciones en lenguaje C, ejecutar:
```
make measureTimeCFiles
```

Para utilizar las funciones en lenguaje ASM MIPS32, ejecutar:
```
make measureTimeSFiles
```
En todos los casos, se crea un archivo de texto en el directorio de ejecución con el tiempo de medición calculado.

### Ejemplo de generación de imágenes
Las imágenes se guardarán en el directorio 'output'

```
./conway 4 10 10 glider
```

### Modo impresión por terminal
Se puede imprimir por terminal si se utiliza la opción '-o -'.
```
./conway 4 10 10 glider -o -
```
