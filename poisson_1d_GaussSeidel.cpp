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
    return std::sin(M_PI * x); // Esta corresponde a la función 
}