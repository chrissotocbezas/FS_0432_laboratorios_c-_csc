// Procedemos a agregar las librerías que vamos a utilizar para ejecutar nuestro archivo de C++-
#include <iostream>
#include <cmath>
#include <vector> // Esta librería será necesaria porque trabajaremos con vectores y matrices.

// Procedemos a generar el lado derecho del Sistema de Lorentz.

std::vector<double> lorenz(const std::vector<double>& r, double sigma, double rho, double beta) {
    std::vector<double> drdt(3);

    // A continuación colocamos las derivadas de la transformación de Lorentz.
    // Lo anterior corresponde a las ecuaciones diferenciales que debemos colocar.

    drdt[0] = sigma * (r[1] - r[0]); // Esto corresponde a la ecuación diferencial de la posición en x.
    drdt[1] = r[0] * (rho - r[2]) - r[1]; // Esto corresponde a la ecuación diferencial de la posición en y.
    drdt[2] = r[0] * r[1] - beta * r[2]; // Esto corresponde a la ecuación diferencial de la posición en z.
    
    return drdt; // Al final, le pedimos que devuelva la posición en cada una de las variables.

    /* Debemos tomar en cuenta, que para este código, el transformador de Lorentz, tiene la peculiaridad de tener tres ecuaciones diferenciales
     que nos ayudan a observar el comportamiento que tiene cada componente el transformador de Lorenz. El hecho de que devolvamos drdt nada más,
     esto nos ayuda a confirmarlo como un conjunto de arrays por dimensión. Estos arrays los usaremos en la siguiente parte del código.*/
}

// A continuación procedemos a colocar las operaciones vectoriales manuales.

std::vector<double> add_vector(const std::vector<double> & a, const std::vector<double>& b, double factor = 1.0) {
    return {a[0] + factor * b[0], a[1] + factor * b[1], a[2] + factor * b[2]};
}

// Procedemos a colocar el Método RK4.

std::vector<std::vector<double>> rk4(double h, double t0, double tf, double x0, double yo, double z0){
    
}