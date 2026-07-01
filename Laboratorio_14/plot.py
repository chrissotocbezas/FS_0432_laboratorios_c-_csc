import matplotlib.pyplot as plt 
import pandas as pd 

# Procedemos a cargar los datos omitiendo el encabezado, obtenido...

df = pd.read_csv('tiempos.txt', sep=' ')

plt.figure(figsize=(8,5))
plt.plot(df['hilos'], df['tiempo'], marker='o', linestyle='-', color='b', label='Tiempo de ejecución')

plt.title('Rendimiento de Multiplicación Matricial con OpenMP')
plt.xlabel('Número de Hilos')
plt.ylabel('Tiempo de ejecución (segundos)')
plt.xscale('log', base=2)
plt.xticks(df['hilos'], df['hilos'])
plt.grid(True, which="both", linestyle = "--", alpha=0.5)
plt.legend()
plt.savefig('tiempo_vs_hilos.png', dpi=300)
plt.show()
