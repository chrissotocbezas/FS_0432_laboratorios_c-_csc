#include <iostream>
#include <iomanip> // Biblioteca necesaria para poder manipular decimales o valores
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
    double valor_exacto = M_PI; // Este corresponde al valor de pi, que es el valor exacto de la integral.

    // Lo anterior, corresponde al uso de la Biblioteca de C++, conocida como cmath.

    // Donde procedemos a mostrar los resultados finales, obtenidos para cada una de las integrales.

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nIntegral de 4/(1+x²), para el intervalo dado en [0,1]" << std::endl;
    std::cout << "Trapecio Compuesto: " << metodoTrapecio << std::endl;
    std::cout << "Simpson compuesto: " << metodoSimpson << std::endl;
    std::cout << "Valor exacto: " << valor_exacto << std::endl;

    // Procedemos a calcular los erroes absolutos dados para nuestros métodos aplicados, tanto el del trapecio como el de Simpson.

    // En la siguiente sección mencionamos los erroes absolutos...

    std::cout << "Error Método Trapecio: " << std::abs(valor_exacto-metodoTrapecio) << std::endl;
    std::cout << "Error Método Simpson: " << std::abs(valor_exacto - metodoSimpson) << std::endl;

    // Y también procedemos con la liberación de la memoria, donde colocamos ahora que:

    delete[] x;
    delete[] fx;

    return 0;
}