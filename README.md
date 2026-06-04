# Laboratorio 10.

Nombre del autor: Christopher Soto Cabezas.
Carné: C17745.

Este documento contiene las instrucciones a realizar para ejecutar el laboratorio 10 del curso de Física Computacional. En este caso, se procederá a indicar cómo ejecutar los datos de los documentos para el archivo de poisson_1d_GaussSeidel.cpp y también para el Método de Jacobi (poisson_1d_Jacobi.cpp).

### Instrucciones de Ejecución

Para este laboratorio, usted debe seguir las siguientes instrucciones.

1. Asegurarse que el código se encuentro guardado y actualizado dentro de su computadora.
2. Compilar con la instrucción g++ poisson_1d_Jacobi.cpp -o Jacobi -I$CONDA_PREFIX/include/python3.11 -I$(python -c "import numpy; print(numpy.get_include())") -L$CONDA_PREFIX/lib -lpython3.11 -Wl,-rpath,$CONDA_PREFIX/lib

Es importante asegurarse que se tenga el nombre correcto del archivo de tipo cpp que se va a ejecutar. Este comando es necesasrio para poder enlazar las librerías de numpy y matplotlib usadas en Python, para la versión de C++ utilizada en este código descargado de la librería de GitHub.

¡IMPORTANTE! Donde se coloca el archivo a ejecutar, se debe colocar el nombre del archivo y la forma en la que se va a guardar el ejecutable, de lo contrario, este archivo puede tener errores al momento de su ejecución.

3. Pedir desde la terminal que se actúe el ejecutable con ./nombre_del_archivo, al haber compilado el archivo de C++.

4. Verificar desde la terminal si se cargaron los archivos de las gráficas.