#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "matplotlibcpp.h" // Esta librería se descarga desde el repositorio de GitHub.FILE

// Se procederá a cargar el archivo de matplotlibcpp.h del laboratorio 10, con el fin de que este sea ejecutable en el archivo del repositorio.

namespace plt = matplotlibcpp; // Renombramos matplotlibcpp, con el fin de poder utilizar una notación estándar similar a la de Python.

// En el método de Jacobi, tenemos que debemos mencionar la solución analítica del problema.
// Podemos mencionar ahora esto con una función double, también debemos mencionar la función fuente, que se encuentra mencionada como f(x)

// A continuación colocamos la solución analítica del problema.

double solucion_analitica(double x) {
    return -std::sin(M_PI * x) / (M_PI * M_PI); 
}

// Tenemos la solución analítica del problema, se multiplica pi dos veces, ya que se encuentra al cuadrado y en el caso del argumento de x, observamos que se encuentra multiplicando pi a x.

// Recordar que debemos resolver el problema de forma numérica con una malla uniforme.

// Colocamos la función fuente.

double f(double x){
    return std::sin(M_PI*x);
}

// A continuación, procedemos a definir la función principal, en donde procederemos a ejecutar las funciones anteriores y meter el método de Jacobi.
// En esta función main, se encontrarán los parámetros a utilizar.

int main() {
    // Procedemos a colocar los parámetros de la simulación.

    int N = 100; // Número de divisiones solicitadas.
    double h = 1.0 / N; // Este valor corresponde al paso que se tiene en Jacobi. x = ih.
    double tol = 1e-6; // Este valor corresponde a la tolerancia a utilizar para este método.
    int max_iter = 1000000; // Aquí colocamos el número máxima de iteraciones.

    // Procedemos a definir las condiciones de frontera que solicitamos.

    double alpha = 0.0;
    double beta = 0.0;

    /* Recordemos que las condiciones de frontera en este caso, son las condiciones de frontera de Dirichlet, por lo tanto, ambos valores de 
    alpha y beta serán cero.*/

    // Colocamos los vectores necesarios para la malla uniforme y las respectivas soluciones.

    // Esto conforme al algoritmo de Jacobi.

    std::vector<double> x(N+1);
    std::vector<double> u(N+1, 0.0);
    std::vector<double> u_new(N+1, 0.0);
    std::vector<double> u_exacta(N+1);

    /* Con los vectores para la malla y las soluciones, podemos empezar a inicializar la malla, donde colocamos los sistemas matriciales que vamos a resolver
    así como las respectivas estimaciones que vamos a colocar, debemos recordar, que cada iteración se debe guardar hasta cierto límite.
    Para este caso de inicializar, un bucle for nos puede ser realmente útil, ya que las iteraciones de la solución analítica y la malla, se encuentran
    completamente definidas.*/
    
    for (int i = 0; i <= N; ++i) {
        x[i] = i * h; // Corresponde a la iteración para cada valor de x.
        u[i] = 0.0; // Esta corresponde a la estimación inicial para cada solución.
        u_exacta[i] = solucion_analitica(x[i]); // Guardamos la solución analítica en la u exacta para cada iteración de x que tenemos.
    }

    u[0] = u_new[0] = alpha; 
    u[N] = u_new[N] = beta; 

    /* Los anteriores valores corresponden al ajuste que realizamos con las condiciones de frontera.
    En este caso, procederemos a utilizar vectores para almacenar el historial de errores de convergencia que se encuentren.*/

    std::vector<double> historial_error;
    std::vector<double> iteraciones;

    // Procedemos a colocar algunos valores de inicialización.

    int k = 0; // iteraciones iniciales.
    double error_conv = tol + 1.0;

    // Procedemos a realizar el ciclo iterativo de Jacobi.
    // El bucle while realiza su aparición bajo este contexto.

    while (error_conv > tol && k < max_iter) {
        // Aquí había un error que se encontraba generando problemas al iterar, se elimina por completo el error_conv = 0.0.

        // Procedemos a actualizar los puntos anteriores, donde podemos utilizar un bucle for, para poder ejecutar los puntos anteriores.

        for (int i = 1; i < N; ++i) {
            u_new[i] = 0.5 * (u[i+1] + u[i-1] - h*h*f(x[i])); // Esto corresponde a la forma de la ecuación de Poisson mediante diferencias finitas.
        }

        // Calculamos el error máximo de convergencia entre iteraciones.
        // Para esto ocupamos un segundo bucle for.

        double error_actual = 0.0;

        for (int i = 1; i < N; ++i) {
            double diferencia = std::abs(u_new[i] - u[i]);
            if (diferencia > error_actual) {
                error_actual = diferencia;
            }
        }

        // Procedemos a copiar u_new y mantenemos las condiciones de frontera para esto.

        for (int i = 1; i < N; ++i) {
            u[i] = u_new[i];
        }

        // Y colocamos el nombre de la variable para actualizar el error.

        error_conv = error_actual;

        k++;
        historial_error.push_back(error_conv);
        iteraciones.push_back(k);

        /* En este caso, con todos los procesos que hemos realizado anteriormente, procedemos a ejecutar cada una de las iteraciones y guardamos 
        todo esto en la memoria. Procedemos el cálculo del error fuera del bucle for.*/

    }

    // Calculamos error máximo final con respecto a la solución analítica.

    double e_max_analitico = 0.0; // Lo inicializamos en cero, con el fin de poder ejecutar para cada iteración.
    // Utilizamos un bucle for, para ejecutar el error para cada iteración.

    for (int i = 0; i <= N; ++i) {
        double diferencia = std::abs(u[i] - u_exacta[i]);
        if (diferencia > e_max_analitico) {
            e_max_analitico = diferencia;
        }
    }
    // Procedemos ahora a imprimir los resultados obtenidos en el archivo output_jacobi.txt
    // El siguiente código nos ayudará para esta parte.

    std::cout << "Datos Métodos de Jacobi" << std::endl;
    std::cout << "Iteraciones totales: " << k << std::endl;
    std::cout << "Error de convergencia final (E^K): " << error_conv << std::endl;
    std::cout << "Error máximo con respecto a la solución analítica: " << e_max_analitico << std::endl; 

    // Estos resultados, se mostrarán en el archivo que hicimos de output_jacobi.txt

    // Procedemos a realizar los gráficos.

    // El primer gráfico que tenemos es la Solución Numérica vs. la Analítica.

    plt::figure_size(800, 600);
    plt::plot(x, u, {{"label", "Jacobi (Solución Numérica)"}, {"linestyle", "--"}, {"color", "red"}});
    plt::plot(x, u_exacta, {{"label", "Analítica"}, {"color", "green"}});
    plt::title("Ecuación de Poission 1D - Solución por Método de Jacobi");
    plt::xlabel("Posición x");
    plt::ylabel("u(x)");
    plt::legend();
    plt::save("solucion_jacobi.png");
    plt::clf();

    // Procedemos a armar la gráfica del error de convergencia vs. iteración.

    plt::figure_size(800, 600);
    plt::semilogy(iteraciones, historial_error);
    plt::title("Error de convergencia vs Iteración (Método de Jacobi)");
    plt::xlabel("Iteración k");
    plt::ylabel("Error Máximo");
    plt::legend();
    plt::save("error_jacobi.png");

    return 0;
}
