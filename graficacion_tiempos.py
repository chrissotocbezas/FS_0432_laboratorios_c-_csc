# Procedemos en este archivo a generar las gráficas necesarias para gráficar.
import pandas as pd # Importar para tabular los datos de tiempo en el archivo .txt
import matplotlib.pyplot as plt # Librería para generar gráficas.

# Procedemos a leer los datos del archivo tiempos.txt

try:
    datos = pd.read_csv('tiempos.txt')
except:
    print("Error: No se encontró el archivo tiempos.txt")

# Procedemos con la configuración del diseño de la gráfica

plt.figure(figsize=(8,5))
plt.plot(datos['procesos'], datos['Tiempo'], marker='o', linestyle='-', color='b', linewidth=2, label='Tiempo observado')

# Procedemos a colocar los títulos y etiquetas...

plt.title('Tiempo de Ejecución vs. Número de Procesos (MPI)', fontsize=14, fontweight='bold')
plt.xlabel('Número de Procesos($P$)', fontsize=12)
plt.ylabel('Tiempo de Ejecución (segundos)', fontsize=12)

# Procedemos a configurar el eje X para mostrar procesos evaluados

plt.xticks(datos['procesos'])

plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.savefig('tiempo_vs_procesos.png', dpi=300, bbox_inches='tight')
print('Gráfica guardada exitosamente')
