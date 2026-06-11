#ifndef INTEGRACION_HPP
#define INTEGRACION_HPP

// En este archivo colocamos los prototipos que reciben el arreglo de valores, el valor de los subintervalos n y el paso h.
// En este caso, colocamos funciones de tipo double.

double calculo_integral_trapecio(double* fx, int n, double h);
double calculo_simpson_compuesto(double* fx, int n, double h);

#endif
