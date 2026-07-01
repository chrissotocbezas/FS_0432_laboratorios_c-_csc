/* En este programa, se procederá a realizar el cálculo del producto punto con mpi, además de generar el enlace para poder 
graficar todos los cálculos obtenidos para el producto punto que se va a realizar.

Este producto punot tendrá un total de N = 12800 iteraciones.

Procederemos a calcular esto mediante OpenMPI
*/

#include <iostream> // Librería para usar std::cout.
#include <vector> // Librería necesaria para trabajar con vectores en C++.
#include <cmath> // Como vamos a realizar calculos matemáticos, es necesario colocar esta librería.
#include <mpi.h> // Para usar OpenMPI.

// Procedemos a colocar la función que se nos había indicado en el enunciado.

double f(double x) {
    return std::sin(x); // Función que se nos pedía inicializar los vectores en el proceso.
}

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, size; // Procedemos a declarar estos valores que se utilizarán para identificar procesos.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 128000; // Este corresponde al tamaño total del vector.

    // Procedemos a realizar la verificación de división exacta para este procedimiento.

    if (N % size 1= 0) {
        if (rank == 0) {
            std::cerr << "Error: El tamaño N (" << N << ") debe ser divisible por el número de procesos (" << size << "). " << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int local_N = N / size; // Declaramos tamaño local de N.
}