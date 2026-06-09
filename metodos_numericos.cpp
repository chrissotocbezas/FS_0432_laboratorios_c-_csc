// Procedemos a agregar las librerías que vamos a utilizar para ejecutar nuestro archivo de C++-
#include <iostream>
#include <cmath>
#include <vector> // Esta librería será necesaria porque trabajaremos con vectores y matrices.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Procedemos a definir los valores de las constantes

const double constante_sigma = 10.0;
const double constante_rho = 28.0;
const double constante_beta = 8.0/3.0;

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

// Procedemos a colocar el Método de Euler.

std::vector<std::vector<double>> euler(double h, double t0, double tf, double x0, double y0, double z0){
    // Calculamos el número de pasos basándonos en el tamaño del paso h.
    int N = static_cast<int>((tf-t0)/h)+1;
    std::vector<std::vector<double>> trayectoria;
    trayectoria.reserve(N); // Aquí le decimos a C++ que reserve memoria para optimizar el rendimiento.

    // Inicializamos el vector para las condiciones iniciales

    std::vector<double> r = {x0, y0, z0};
    trayectoria.push_back(r);

    // Procedemos a realizar la iteración a lo largo del tiempo aplicando la aproximación lineal de Euler.
    // Esto lo podemos realizar con un bucle for

    for(int i = 1; i < N; ++i) {
        std::vector<double> drdt = lorenz(r, constante_sigma, constante_rho, constante_beta);
        // Esto corresponde a la iteración para r_{n+1}
        r = add_vector(r, drdt, h);
        trayectoria.push_back(r);
    }
    return trayectoria; // Esto nos ayuda a devolver la matriz completa de la trayectoria con el Método de Euler.
}

// Colocamos el método de RK2.

std::vector<std::vector<double>> rk2(double h, double t0, double tf, double x0, double y0, double z0){
    int N = static_cast<int>((tf-t0)/h) + 1;
    std::vector<std::vector<double>> trayectoria;
    trayectoria.reserve(N);

    std::vector<double> r = {x0, y0, z0};
    trayectoria.push_back(r);

    // Realizamos la iteración para cada uno de los puntos en el caso del módulo de Runge-Kutta.

    for (int i = 1; i < N; ++i){
        // k1 corresponde a evaluar la pendiente.
        // En este caso, buscamos una pendiente para evaluar el punto medio.
        // El punto medio lo evaluamos.
        std::vector<double> k1 = lorenz(r, constante_sigma, constante_rho, constante_beta);

        // Procedemos a evaluar el punto medio usando el factor (h/2.0).
        std::vector<double> r_medio = add_vector(r, k1, h /2.0);
        // k2 corresponde a la pendiente evaluada que se encuentra en el punto medio. (De ahí el nombre Runge-Kutta 2)
        std::vector<double> k2 = lorenz(r_medio, constante_sigma, constante_rho, constante_beta);

        // En donde colocamos la fórmula dada por r_{n+1}=r_n + h *k2
        r = add_vector(r, k2, h);
        trayectoria.push_back(r);
    }
    return trayectoria;
}

// Procedemos a colocar el Método RK4.

std::vector<std::vector<double>> rk4(double h, double t0, double tf, double x0, double y0, double z0){
    int N = static_cast<int>((tf-t0)/h)+1;
    std::vector<std::vector<double>> trayectoria;
    trayectoria.reserve(N);

    std::vector<double> r = {x0, y0, z0};
    trayectoria.push_back(r);

    // Procesamos a iterar las constantes para armar la matriz.

    for(int i = 1; i < N; ++i){
        // Procedemos a evaluar el primer paso intermedio (pendiente al inicio del intervalo).
        std::vector<double> k1 = lorenz(r, constante_sigma, constante_rho, constante_beta);

        // Procedemos con la evaluación del segundo paso intermedio, esto debido a que RUnge-Kutta utiliza cuatro evaluaciones de la función f.

        std::vector<double> r_k2 = add_vector(r, k1, h/2.0);
        std::vector<double> k2 = lorenz(r_k2, constante_sigma, constante_rho, constante_sigma);

        // Procedemos a evaluar el tercer paso intermedio...
        std::vector<double> r_k3 = add_vector(r, k2, h/2.0);
        std::vector<double> k3 = lorenz(r_k3, constante_sigma, constante_rho, constante_beta);

        // Procedemos a evaluar el cuarto paso intermedio de nuestro método RK4.
        std::vector<double> r_k4 = add_vector(r, k3, h);
        std::vector<double> k4 = lorenz(r_k4, constante_sigma, constante_rho, constante_beta);

        // Y procedemos a promediar de manera ponderada todas las pendientes calculadas.
        // Esto corresponde al cálculo final del Método de Runge-Kutta (k1 + 2*k2 + 2*k3 + k4).
        std::vector<double> k_combinado = add_vector(k1, k2, 2.0);
        k_combinado = add_vector(k_combinado, k3, 2.0);
        k_combinado = add_vector(k_combinado, k4, 1.0);

        // Realizamos la actualización final del paso temporal aplicando el factor (h / 6.0).
        r = add_vector(r, k_combinado, h / 6.0);
        trayectoria.push_back(r);
    }
    return trayectoria; // Devolvemos la matriz final con la aproximación de Runge-Kutta 4.
}

// Procedemos a agregar el módulo que nos ayude con la vincluación con pybind11

PYBIND11_MODULE(lorenz, m){
    m.doc() = "Módulo para resolver el sistema de LOrenz usando los métodos Euler, RK2 y RK4";
    m.def("euler", &euler, "Método de Euler", py::arg("h"), py::arg("t0"), py::arg("tf"), py::arg("x0"), py::arg("y0"), py::arg("z0"));
    m.def("rk2", &rk2, "Método de Runge-Kutta 2", py::arg("h"), py::arg("t0"), py::arg("tf"), py::arg("x0"), py::arg("y0"), py::arg("z0"));
    m.def("rk4", &rk4, "Método de Runge-Kutta 4", py::arg("h"), py::arg("t0"), py::arg("tf"), py::arg("x0"), py::arg("y0"), py::arg("z0"));

}