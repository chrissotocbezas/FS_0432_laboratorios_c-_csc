#include "integracion.hpp"
#include <iostream>

// Procedemos a integrar el método del trapecio compuesto.
// Para esto integramos una función double...

double calculo_integral_trapecio(double* fx, int n, double h) {
    double suma = fx[0] + fx[n]; // Con esto calculamos el primer y último término de la integral.
    // Mediante un bucle for, calculamos término a término.
    for (int i = 1; i < n; i++) {
        suma += 2.0 * fx[i]; // Se realiza que cada término intermedio sea multiplicado por 2.
    }
    return (h/2.0) * suma;
}

double calculo_simpson_compuesto(double* fx, int n, double h) {
    // Primero debemos colocar la condición para validar n par para Simpson.
    // Recordamos que si Simpson no es par, entonces, el resultado no procede.

    if (n % 2 != 0) {
        std::cerr << "Error: n debe ser par para el método de Simpson. " << std::endl;
        return -1.0;
        // Con esta restricción ya aplicada, procedemos a aplicar el método de Simpson.
        // Nos ayudamos de un bucle for para esta tarea.
    }

    double suma = fx[0] + fx[n];
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            suma += 2.0 * fx[i]; // Esto es para los índices pares.
        } else {
            suma += 4.0 * fx[i]; // Colocamos la suma para los índices impares.
        }

    }
    return (h / 3.0) * suma; // Aquí colocamos nuestro valor final de aplicar Simpson.
}