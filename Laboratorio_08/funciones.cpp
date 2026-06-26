#include "funciones.hpp"

// Definimos la función que vamos a aplicar cada uno de nuestros métodos de integración.
// Tenemos ahora que la función f(x) es f(x) = 4 / (1 + x²)

double f(double x) {
    return 4.0 / (1.0 + x * x); // Generamos la función que vamos a integrar.
}
