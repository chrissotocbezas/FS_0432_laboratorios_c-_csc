// En este código continuamos con el método de Gauss Seidel, primero colocamos las bibliotecas que vamos a utilizar.

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "matplotlibcpp.h" // Esta librería es importante de utilizar para poder realizar los gráficos.

// Procedemos a usar el comando especial, que vamos a utilizar ahora...

namespace plt = matplotlibcpp;

double solucion_analitica(double x) {
    return -std::sin(M_PI * x) / (M_PI * M_PI);
}

// Procedimos a colocar la solución analítica al igual que en el Método de Jacobi.
// Procedemos a colocar la función f(x).

double f(double x) {
    return std::sin(M_PI * x); // Esta corresponde a la función f(x).
}

// Colocamos la función principal.

int main() {
    int N = 100;
    double h = 1.0 / N;
    double tol = 1e-6;
    int max_iter = 10000000;
    
    // Colocamos los valores para las condiciones de frontera.

    double alpha = 0.0;
    double beta = 0.0;

    // Volvemos a utilizar vectores para guardar la información necesaria.

    std::vector<double> x(N+1);
    std::vector<double> u(N+1, 0.0);
    std::vector<double> u_exacta(N+1);

    for (int i = 0; i <= N; ++i) {
        x[i] = i*h;
        u[i] = 0.0;
        u_exacta[i] = solucion_analitica(x[i]);
    }
    // Finalizando el bucle for, procedemos a actualizar las condiciones de frontera.

    u[0] = alpha;
    u[N] = beta;

    // Guardamos los datos del error, con vectores.

    std::vector<double> historial_error;
    std::vector<double> iteraciones;

    // Colocamos el inicializador de iteraciones.
    // También colocamos el error de convergencia.
    // En el error de convergencia entra la tolerancia.

    int k = 0;
    double error_convergencia = tol + 1.0;

    // Procedemos a realizar el ciclo iterativo para Gauss-Seidel...
    // En este caso, lo ejecutamos mediante un bucle while.
    // Lo debemos inicializar con el valor del error de convergencia, la tolerancia y el número máximo de iteraciones.

    while (error_convergencia > tol && k < max_iter) {
        error_convergencia = 0.0;

        // Procedemos a realizar el mismo proceso que para el método de Jacobi, con el detalle, que usamos ahora el valor u_viejo.
        // Lo usamos con bucles for.

        for (int i = 1; i < N; ++i) {
            double u_viejo = u[i];

            // Recordemos que Gauss-Seidel usa u[i-1] ya actualizado en esta misma iteración k

            u[i] = 0.5 * (u[i+1] + u[i-1] - h * h * f(x[i]));

            double diferencia = std::abs(u[i] - u_viejo);
            if (diferencia > error_convergencia) {
                error_convergencia = diferencia;
            }
        }
    }
}