#!/bin/bash

# Procedemos a buscar el nombre del ejecutable en C++ y archivo de salida...

EJECUTABLE="./producto_punto_mpi"
ARCHIVO_SALIDA="tiempos.txt"

# 1. Verificar si el archivo ejecutable existe
if [ ! -f "$EJECUTABLE" ]; then
    echo "Error: No se encuentra el ejecutable $EJECUTABLE"
    exit 1
fi

# 2. Inicializar el archivo con el encabezado CSV
echo "procesos,tiempo" > "$ARCHIVO_SALIDA"
echo "Creado el archivo $ARCHIVO_SALIDA con encabezados."
echo "-----------------------------------------"

# 3. Bucle para ejecutar con 1, 2, 4 y 8 procesos
for p in 1 2 4 8; do
    echo "Corriendo simulación con $p procesos..."
    
    # 2>&1 mezcla la salida normal y la de errores por si acaso.
    # El nuevo filtro busca cualquier número flotante de forma más agresiva.
    tiempo=$(mpirun -np $p "$EJECUTABLE" 2>&1 | grep -oP '\b[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?\b' | head -n 1)
    
    if [ -z "$tiempo" ]; then
        echo "Advertencia: No se pudo capturar el tiempo para $p procesos."
    else
        # Guardar en formato: procesos,tiempo
        echo "$p,$tiempo" >> "$ARCHIVO_SALIDA"
        echo " -> ¡Completado! Tiempo registrado: $tiempo s"
    fi
done

echo "Proceso finalizado. Datos guardados en '$ARCHIVO_SALIDA'."