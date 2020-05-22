# 66.20 Organización de computadoras
# 1C2020
# TP1: Conjunto de instrucciones MIPS.

## Compilación utilizando archivos .c
Posicionarse en el directorio 'src/' y ejecutar:
```
make
```

## Compilación utilizando archivos .S
Si se quiere utilizar los archivos codificados en ASM MIPS32, ejecutar
```
make use_S_files
```

## Ejemplo de generación de imágenes
Las imágenes se guardarán en el directorio 'output'

```
./conway 4 10 10 glider
```

### Modo impresión por terminal
Se puede imprimir por terminal si se utiliza la opción '-o -'.
```
./conway 4 10 10 glider -o -
```
