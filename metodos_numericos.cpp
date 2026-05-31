// Procedemos a agregar las librerías que vamos a utilizar para ejecutar nuestro archivo de C++-
#include <iostream>
#include <cmath>
#include <vector> // Esta librería será necesaria porque trabajaremos con vectores y matrices.

// Procedemos a generar el lado derecho del Sistema de Lorentz.

std::vector<double> lorenz(const std::vector<double>& r, double sigma, double rho, double beta) {
    std::vector<double> F(3);

    // A continuación colocamos las derivadas de la transformación de Lorentz.
}