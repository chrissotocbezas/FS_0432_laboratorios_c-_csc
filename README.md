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

1. 