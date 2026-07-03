# Instrucciones de ejecución para Tarea 05/Laboratorio 15.

Nombre: Christopher Soto Cabezas.

Instrucciones:

Al ser este un programa en C++, que trabaja en un entorno con OpenMPI, no se compila de la misma forma que un archivo C++ regular, ya que la estructura del mismo, no permite que se ejecute de la misma forma.

Se debe uno de asegurar dos cosas:

1. Tener la biblioteca que usa mpi, <mpi.h>.
2. Asegurarse que dentro del programa se tenga la estructura dada para inicializar el programa con MPI, lo cual viene dado por las funciones:
    * MPI_Init
    * MPI_Finalize

Esto con el objetivo de delimitar las zonas en donde se deben delimitar el alcance de OpenMPI.

### Para compilar...

1. Verificar descarga en la computadora del repositorio, puede ser mediante descarga directa desde el repositorio de GitHub o ejecutarse mediante el comando 'gitclone'.
2. Una vez descargado todos los programas, se debe proceder a llamar el ejecutable mediante:

    mpic++ producto_punto_mpi.cpp -o producto_punto_mpi

3. Una vez compilado y realizado el ejecutable, procedemos a colocar el siguiente comando:

    mpirun -np 4 ./producto_punto_mpi

Esto con el objetivo de poder ejecutar el programa con 4 procesos en el contexto de MPI.

¡IMPORTANTE! El número 4, es solo un ejemplo de muestra de los procesos que se pueden ejecutar, realmente se pueden agregar los procesos que la computadora permita realizar.
