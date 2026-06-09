# En este archivo se van a utilizar las herramientas de los métodos numéricos implementados en la tarea 03.
# Se debe enlazar este archivo con métodos_numericos.cpp

# Lo que hacemos ahora es importar las librerías de Python que debemos utilizar

import numpy as np
import matplotlib.pyplot as plt
import lorenz_methods

# Procedemos a ejecutar los 3 métodos numéricos que hemos armado y los colocamos en forma de arrays gracias a Numpy.abs

sol_euler = np.array(metodos_numericos.euler(h, t0, tf, x0, y0, z0))
sol_rk2 = np.array(metodos_numericos.rk2(h, t0, tf, x0, y0, z0))
sol_rk4 = np.array(metodos_numericos.rk4(h, t0, tf, x0, y0, z0))

# Procedemos a generar el vector de tiempo y marcamos el número de pasos que vamos a llamar
N = int((tf-t0)/h) + 1
t = np.linspace(t0, tf, N)

# Con una función, procedemos agenerar la graficación tridimensional del sistema, donde colocamos diferente variables para generarlo 

def grafica_3d(solucion, titulo, nombre_archivo, color):
    fig = plt.figure(figsize(8,6))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(solucion[:, 0], solucion[:, 1], solucion[:, 2], label=titulo, color=color, lw=0.7)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax_set_zlabel('Z')
    ax.set_title(f'Trayectoria 3D de Lorenz - {titulo}')
    ax.legend()
    plt.savefig(nombre_archivo, dpi=300)
    plt.close()

# Procedemos a generar las 3 figuras de trayectorias

grafica_3d(sol_euler, 'Euler', 'trayectoria_3d_euler.png', 'crimson')
graficar_3d(sol_rk2, 'RK2', 'trayectoria_3d_rk2.png', 'darkorange')
graficar_3d(sol_rk4, 'RK4', 'trayectoria_3d_rk4.png', 'navy')

# Colocamos una sensibilidad para las condiciones iniciales

epsilon = 1e-8
x0_prime = x0 + epsilon

# Ejecutar RK4 con la condición inicial perturbada

sol_rk4_perturbada = np.array(metodos_numericos.rk4(h, t0, tf, x0_prime, y0, z0))

# Procedemos a calcular la distancia euclidiana para cada paso del tiempo

diff = sol_rk4 - sol_rk4_perturbada
distancias = np.linalg.norm(diff, axis=1)

# Procedemos a imprimir la salida requerida por la tarea

separacion_inicial = distancias[0]
separacion_final = distancias[1]

# Entonces, podemos mostrar los datos obtenidos para separación inicial y la separación final

print(f"Separación inicial: {separacion_inicial:.6e}")
print(f"Separación final: {separacion_final:.6e}")

# Y procedemos a graficar en función del tiempo, para esto, es ampliamente recomendado usar una escala semilogarítimica (semilogy)

plt.figure(figsize=(8,5))
plt.semilogy(t, distancias, color='purple', label=r'$d(t)= ||r(t)-r\'(t)||$')
plt.xlabel('Tiempo(t)')
plt.ylabel('Separación (Escala Logarítmica)')
plt.title('Sensibilidad a Condiciones Iniciales para (Lorenz RK4)')
plt.grid(True, which="both", ls='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('Grafica_Sensibilidad.png', dpi=300)
plt.close()
