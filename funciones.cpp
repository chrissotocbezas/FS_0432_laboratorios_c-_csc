#include <iostream>
#include <cmath>
#include "funciones.hpp"
#include "integracion.hpp"

int main() {
    int n;
    double a = 0.0, b = 1.0; // En este caso, establecemos el intervalo citado de [0, 1], para aplicar métodos de integración numérica

    std::cout << "Ingrese un número de subintervalos (n): ";
    std::cin >> n;

    double h = (b - a) / n; // Corresponde al salto que deberemos utilizar para los métodos de integración.

    // Procedemos a generar nuestros arreglos dinámicos

    double* x = new double[n + 1];
    double* fx = new double[n + 1];

    // Con un bucle for, procedemos con el llenado de los arreglos.

    for (int i = 0; i <= n; i++) {
        x[i] = a + i * h;
        fx[i] = f(x[i]);

    }

    // En la siguiente espacio, procedemos a llamar a cada uno de los métodos de cálculo de integrales.

    double metodoTrapecio = calculo_integral_trapecio(fx, n, h);
    double metodoSimpson = calculo_simpson_compuesto(fx, n, h);
    double valore_exacto = M_PI; // Este corresponde al valor de pi, que es el valor exacto de la integral.

    // Lo anterior, corresponde al uso de la Biblioteca de C++, conocida como cmath.
}