# Tarea 03 - Sistema de Lorenz y Aplicación de Métodos Numéricos...

Nombre: Christopher Soto Cabezas

*En este archivo se presenta algunas instrucciones para compilar el archivo y ejecutarlo.*

## Instrucciones de ejecución:

* **Compilador de C++** Asegurarse que se tiene el compilador de C++ instalado en el sistema.
* **Compilador de Python** Asegurarse que se tiene el compilador de Python instalado en el sistema.
* **Biblioteca Pybind11** Asegurarse que se tiene la biblioteca 'pybind11' en el sistema.

1. Primero, se debe ejecutar el archivo de C++, mediante el siguiente comando desde la terminal: g++ metodos_numericos.cpp -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) -o lorenz_methods$(python3-config --extension-suffix)

2. Después ejecutar el archivo en Python mediante el comando python main.py

3. Para pasar los datos al archivo output.txt, se debe ejecutar el comando de python main.py > output.txt y se trasladarán los resultados obtenidos en el formato obtenido y configurado en el archivo de Python.

4. Observar las gráficas obtenidas en el archivo de resultados.
