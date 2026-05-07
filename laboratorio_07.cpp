#include <iostream> // Inicializamos el código de esta forma.
#include <iomanip> // Librería para ajustar decimales.

// En el caso de iomanip, podemos encontrar que es la librería estándar de C++ para manejar decimales.
// La librería tiene funcionalidades similares, a las que tienen funciones como doubleprecision (dp) en Fortran.
// Esta librería vienen incluida con C++ y es necesaria para manejar decimales o cálculos matemáticos, de lo contrario.
// Esta librería tiene algunas funcionalidades para establecer constantes.
// Un ejemplo de uso es para establecer el número pi, el cual no viene incluido en C++, pero puede colocarse y ajustar la cantidad de decimales con las que se quiere

//Comenzamos a montar algunas funciones que usaremos más adelante.

void mostrarnotas(double* notas, int cantidad); // Con esta función, buscamos enseñar las notas que tenemos
void clasificar_rendimiento(double* notas, int cantidad, int &reprobados, int &aprobados, int &sobresalientes); // Con esta función buscamos clasificar el rendimiento.

// Declaramos nuestra función principal main()

int main() {
// Procedemos a declarar las variables que vamos a utilizar para generar nuestro arreglo.

double notas[10]; // Declaramos el array.
int contador = 0; // El contador de notas se inicia en cero.
double entrada; // Marcamos el punto de entrada.

std::cout << "Administración de notas" << std::endl;
std::cout << "Para este sistema ingrese 10 notas de 0.0 a 100.0" << std::endl;
std::cout << "Recuerde ingresar -1 para finalizar el ingreso de notas." << std::endl;

// Lo que hicimos anteriormente, es para mostrar un encabezado que permita al usuario observar de qué se trata este programa.

// Con un bucle empezamos el ingreso de datos, usaremos la variable contador para que cuente las 10 notas y cuando ésta finalice, se deberá romper el proceso.
// En este caso, podemos usar el do-while, para que el bucle siempre se ejecute al menos una vez, independientemente de las circunstancias.

do {
    if (contador >= 10) break; // Esto nos indica que si ingresamos 10 notas o más, debemos interrumpir el procedimiento.

    std::cout << "Nota- " << (contador + 1) << ": "; //Con esto mostramos la nota que ingresamos y el índice del valor.
    std::cin >> entrada; // Esto nos permite ingresar los datos.

    // Si el usuario ingresa el valor de -1, debe interrumpir el proceso inmediatamente.
    // En este caso, el valor de la variable entrada, tiene que ser el que interrumpa.

    if (entrada == -1) {
        break;
    } // Interrumpimos el proceso...

    // Debemos asegurarnos de que los datos sean válidos. 
    // A continuación, armamos la condición que nos permita indicar que los datos deben ser entre 0.0 y 100.0, y que fuera de eso, no ingrese el dato.

    if (entrada < 0.0 || entrada > 100.0) {
        std::cout << "Nota inválida. Intente de nuevo. " << std::endl;
        continue; // Al agregar la sentencia continue, repetimos de nuevo el proceso desde el inicio.
    }
    
    notas[contador] = entrada; // Agregamos los datos al array.
    contador++; // Los guardamos.
    
    
    

} while(true); //  El do-while debe tener al inicio 

if (contador > 0) {
    // Variables para los resultados de clasificación.
    int reprobados = 0, aprobados = 0, sobresalientes = 0;

    std::cout << "\n ---Reporte del Grupo---" << std::endl;

    //Procedemos a llamar las funciones...
    mostrarnotas(notas, contador);
    clasificar_rendimiento(notas, contador, reprobados, aprobados, sobresalientes); // Con esta función armamos tres clasificaciones.

    // Con esta función clasificamos los aprobados, reprobados y sobresalientes de acuerdo a su nota.
    // A continuación mostramos los resultados de su clasificación.

    std::cout << "Resumen de Rendimiento" << std::endl;
    std::cout << "Reprobados: " << reprobados << std::endl;
    std::cout << "Aprobados: " << aprobados << std::endl;
    std::cout << "Sobresalientes: " << sobresalientes << std::endl;
    
} else {
    std::cout << "No se ingresaron notas válidas." << std::endl;
// Aquí finalizan nuestras condiciones a usar.
}
return 0; // Aquí devolvemos todo en la función main.
}

// Con una función void, mostramos el arreglo...

void mostrarnotas(double* notas, int cantidad) {
    std::cout << "Notas ingresadas: ";
    // Con un bucle for, podemos mostrar cada una de las notas ingresadas y su respectivo índice.
    for (int i = 0; i < cantidad; i++) {
        std::cout << std::fixed << std::setprecision(1) << *(notas + i) << " ";
    }
    std::cout << std::endl;
}

void clasificar_rendimiento(double* notas, int cantidad, int &reprobados, int &aprobados, int &sobresalientes) {
    for (int i = 0; i < cantidad; i++) {
        double notaActual = *(notas + i);
        // A continuación colocamos las condiciones que debemos usar para ejecutar nuestro código.
        if (notaActual < 70.0) {
            reprobados++;
        } else if (notaActual >= 70.0 && notaActual < 90.0) {
            aprobados++;
        } else {
            sobresalientes++;
        }
    }
}