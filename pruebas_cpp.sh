#!/bin/bash

# Colocamos el nombre del ejecutable de C++ y archivo de salida

EJECUTABLE="./producto_punto_mpi"
ARCHIVO_SALIDA="tiempos.txt"

# Verificamos que el archivo ejecutable exista

if [ ! -f "$EJECUTABLE" ]; then
    echo "Error: No se encuentra el ejecutable $EJECUTABLE"
    echo "Asegúrate de compilar primero en la terminal con:"
    echo "mpic++ producto_punto_mpi.cpp -o producto_punto_mpi"
    exit 1
fi

# Procedemos a inicializar con el encabezado CSV, esto con el objetivo de generar una tabla con los datos

echo "procesos, tiempo" > $ARCHIVO_SALIDA
echo "Creado el archivo $ARCHIVO_SALIDA con encabezados."

# Procedemos a usar un bucle para ejecutar 1, 2 y 4 procesos, esto debido a que con ocho no corre por falta de CPU...

for p in 1 2 4; do 
    echo "Corriendo simulación con $p procesos..."

    # Procedemos a ejecutar mpirun y extrae solo el número decimal flotante del tiempo

    tiempos = $(mpirun -np $p $EJECUTABLE | grep -oP '[0-9]+\.[0-9]+')

    if [ -z "$tiempo" ]; then
        echo "Advertencia: No se pudo capturar el tiempo para $p procesos."
    else
        # Procedemos a guardar_ procesos, tiempo

        echo "$p,$tiempo" >> $ARCHIVO_SALIDA
        echo " -> ¡Completado! Tiempo registrado: $tiempo s"
    fi
done

echo "Proceso finalizado. Datos guardados en '$ARCHIVO_SALIDA'."