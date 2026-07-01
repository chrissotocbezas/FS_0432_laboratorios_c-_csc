/* En este programa, se procederá a realizar el cálculo del producto punto con mpi, además de generar el enlace para poder 
graficar todos los cálculos obtenidos para el producto punto que se va a realizar.

Este producto punot tendrá un total de N = 12800 iteraciones.

Procederemos a calcular esto mediante OpenMPI
*/

#include <iostream> // Librería para usar std::cout.
#include <vector> // Librería necesaria para trabajar con vectores en C++.
#include <cmath> // Como vamos a realizar calculos matemáticos, es necesario colocar esta librería.
#include <mpi.h> // Para usar OpenMPI.
