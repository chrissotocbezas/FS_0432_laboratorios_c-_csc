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

    // Colocamos vectores locales para cada proceso.
    // Estos vectores locales, los utilizaremos para realizar el producto punto de forma local.

    std::vector<double> A_local(local_N);
    std::vector<double> B_local(local_N);

    // Procedemos con una definición de etiquetas (tags) distintas para el envío de A y B

    const int TAG_A = 0;
    const int TAG_B = 1;

    // Volvemos a colocar la condición para cuando tengamos rank == 0

    if (rank == 0) {
        // Inicialización para el caso en el proceso 0

        std::vector<double> A(N);
        std::vector<double> B(N);

        // Con este bucle for, generamos una condición para guardar espacios en memoria, para que los vectores sean uniformes.

        for (int i = 0; i < N; ++i){
            A[i] = f((double)i);
            B[i] = 2.0 * f((double)i);
        }

        // El proceso 0 toma su propia porción local

        for (int i = 0; i < local_N; ++i){
            A_local[i] = A[i];
            B_local[i] = B[i];
        }

        /* Este bucle for sirve para que el proces 0 se asigne a sí mismo la primera porción de los datos.
        Lo anterior se da porque en programación paralela con MPI, el proceso 0 no lo tenemos como alguien que solo reparte el trabajo
        simo, que es un trabajador que debe calcular también su propia parte del producto final*/

        // Procedemos con envío de bloques al resto de los procesos.
        // Para lo anterior utilizamos tags distintos.

        for(int p = 1; p < size; ++p){
            MPI_Send(&A[p * local_N], local_N, MPI_DOUBLE, p, TAG_A, MPI_COMM_WORLD);
            MPI_Send(&B[p * local_N], local_N, MPI_DOUBLE, p, TAG_B, MPI_COMM_WORLD);
        }

        // Finalizamos la condición para el proceso rank == 0.
    }
    else {
        // Procesos esclavos reciben sus respectivos bloques
        MPI_Recv(A_local.data(), local_N, MPI_DOUBLE, 0, TAG_A, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B_local.data(), local_N, MPI_DOUBLE, 0, TAG_B, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }

    /* Este bloque es la contraparte del envío de datos, donde el bloque ejecuta única y exclusivamente
    los procesos esclavos que tienen un rank mayor a 0.
    La función de estos es recibir y almacenar los paquetes de datos que el proceso 0 envío por la red.
    En este caso se utilizan dos llamadas consecutivas a la función MPI_Recv, ya que una parte para el fragmento del 
    vector A y otra parte del vector B.*/

    // Colocamos una sincronización previa a la medición de tiempo...

    MPI_Barrier(MPI_COMM_WORLD);
    double tiempo_inicial = MPI_Wtime();

    // Procedemos con el cálculo del producto punto local...
    double producto_punto_local = 0.0;

    /* Con un bucle for, procedemos a ejecutar el producto punto local, debemos notar que en este caso,
    la operación, se termina convirtiendo en una forma de suma local, por lo que su forma de guardar cada iteración,
    será mediante +=.*/

    for (int i = 0; i < local_N; ++i) {
        producto_punto_local += A_local[i] * B_local[i];
    }

    // Procedemos a realizar la reducción global para consolidar la suma en el proceso 0

    double producto_punto_global = 0.0;
    MPI_Reduce(&producto_punto_local, &producto_punto_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Procedemos con la finalización del tiempo de cálculo y comunicación de reducción

    double tiempo_final = MPI_Wtime();
    double paso_tiempo = tiempo_final - tiempo_inicial;

    // Procedemos a obtener el tiempo máximo total entre todos los procesos

    double t_max_total = 0.0;
    MPI_Reduce(&paso_tiempo, &t_max_total, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Procedemos a imprimir el resultado final únicamente desde el proceso 0.

    if (rank == 0) {
        std::cout << "Resultado final del producto punto: " << producto_punto_global << std::endl;
        std::cout << "Tiempo de ejecución del bucle (" << size << " procesos): " << t_max_total << "s." << std::endl;

    }

    MPI_Finalize(); // Finalizamos el proceso con MPI
    return 0;
}