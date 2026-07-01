#!/bin/bash

# Colocamos el nombre del ejecutable de C++ y archivo de salida

EJECUTABLE="./producto_punto_mpi"
ARCHIVO_SALIDA="tiempos.txt"

# Verificamos que el archivo ejecutable exista

if [! -f "$EJECUTABLE" ]; then
    echo "Error: No se encuentra el ejecutable $EJECUTABLE"
    echo "Asegúrate de compilar primero en la terminal con:"
    echo "mpic++ producto_punto_mpi.cpp -o producto_punto_mpi"
    exit 1
fi

# Procedemos a inicializar con el encabezado CSV, esto con el objetivo de generar una tabla con los datos

echo "procesos, tiempo" > $ARCHIVO_SALIDA
echo "Creado el archivo