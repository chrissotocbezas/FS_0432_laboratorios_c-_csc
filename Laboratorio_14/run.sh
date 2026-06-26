# Para este archivo, procederemos a compilar el programa de C++ que ejecuta nuestro archivo de multiplicación matricial.

#!/bin/bash

g++ -O3 -fopenmp matrix_multiplication.cpp -o matrix_multiplication

# Procedemos a limpiar el archivo de tiempos con el encabezado

echo "hilos tiempo" > tiempos.txt

# Procedemos a citar la lista de hilos requeridos

for hilos in 1 2 4 8 16 32
do
    echo "Ejecutando con $hilos hilos..."
    ./matrix_multiplication $hilos >> tiempos.txt
done

echo "Tiempos guardados"
