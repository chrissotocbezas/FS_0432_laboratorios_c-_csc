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

        k++;
        historial_error.push_back(error_convergencia);
        iteraciones.push_back(k);
    }

    double e_max_analitico = 0.0;
    // Volvemos a inicializar las iteraciones para el error máximo analítico.
    // Lo volvemos a registrar mediante un bucle for.
    // En esta ocasión, usamos u[i] y u_exacta[i].

    for (int i = 0; i <= N; ++i) {
        double diferencia = std::abs(u[i] - u_exacta[i]);
        if (diferencia > e_max_analitico) {
            e_max_analitico = diferencia;
        }
    }

    // Procedemos a mostrar los resultados en el archivo output_gauss_seidel.txt
    // Utilizamos los siguientes comandos para llevar esto a cabo.

    std::cout << "Método de Gauss-Seidel" << std::endl;
    std::cout << "Iteraciones totales: " << k << std::endl;
    std::cout << "Error de convergencia final (E k): " << error_convergencia << std::endl;
    std:: cout << "Error Máximo con respecto a la solución analítica: " << e_max_analitico << std::endl;

    // Procedemos a realizar los diferentes gráficos.
    // Comparamos la solución de Gauss-Seidel numérica con la solución analítica.

    plt::figure_size(800, 600);
    plt::plot(x, u, {{"label", "Gauss-Seidel (Solución Numérica)"}, {"linestyle", "--"}, {"color", "red"}});
    plt::plot(x, u_exacta, {{"label", "Solución Analítica"}, {"color", "blue"}});
    plt::title("Ecuación de Poisson 1D - Método de Gauss-Seidel");
    plt::xlabel("Posición x");
    plt::ylabel("u(x)");
    plt::legend();
    plt::save("solucion_gauss_seidel.png");
    plt::clf();

    // Continuamos con la gráfica del error númerico.

    plt::figure_size(800, 600);
    plt::semilogy(iteraciones, historial_error);
    plt::title("Error de Convergencia vs Iteración (Gauss-Seidel)");
    plt::xlabel("Iteracion k");
    plt::ylabel("Error Máximo");
    plt::legend();
    plt::legend();
    plt::save("error_gauss_seidel.png");
    
    return 0; // Finalizamos la función main de nuestro código de C++.
}