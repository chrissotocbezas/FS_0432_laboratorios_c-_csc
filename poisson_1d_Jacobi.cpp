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
    
}