#include <iostream>
#include <cmath>
#include <iomanip>
#include <omp.h>
#include <vector> // Se corrige la librería faltante..
#include <cstdlib>

// Colocamos las librerías a utilizar para la ejecución de este laboratorio.

int main(int argc, char* argv[]){
    // En esta función main, procedemos a ejecutar la multiplicación de matrices.
    // Debemos declarar algunas variables, luego debemos ejecutar la multiplicación de matrices con varios bucles for...

    int num_threads = 32;
    if (argc > 1) {
        num_threads = std::atoi(argv[1]);
    }

    // Indicamos a OpenMp cuántos hilos usar en la región paralela.

    omp_set_num_threads(num_threads);
    
    int N = 12800; // Este tamaño inicial lo procedemos a declarar.

    // Procedemos a inicializar las matrices que las vamos a utilizar.

    std::vector<double> A(N * N, 1.5);
    std::vector<double> B(N * N, 2.0);
    std::vector<double> C(N * N, 0.0);

    // El vector C será el que contendrá toda la suma.

    // Colocamos la variable para ejecutar la medición del tiempo...

    double tiempo_inicio = omp_get_wtime();

    // Procedemos a realizar el bucle for

    #pragma omp parallel for schedule(static) shared(A, B, C, N)
    
    for (int i = 0; i < N; ++i){
        // Cambiamos el orden de los bucles a i-k-j
        for (int k = 0; k < N; ++k) {
            // Procedemos a cambiar las variables
            double a_ik = A[i*N + k];
            for (int j = 0; j < N; ++j) {
                C[i * N + j] += a_ik * B[k*N + j];
            }
        }
    }

    // Procedemos con la medición del tiempo final

    double tiempo_fin = omp_get_wtime();
    double tiempo_ejecucion = tiempo_fin - tiempo_inicio;

    // Procedemos a mostrar los resultados en formato de hilos...

    std::cout << num_threads << " " << tiempo_ejecucion << std::endl;

    return 0;

}