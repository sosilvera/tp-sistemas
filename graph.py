import numpy as np
import pandas as pd
# import seaborn as sns
import matplotlib.pyplot as plt

# df = pd.read_csv("out.csv")
df = pd.read_csv("out-files/out-uniform-sorted.csv")
df_2 = pd.read_csv("out-files/out-spin.csv")

x= df['threads']
y_c= df['tiempo-carga']
y2_c= df_2['tiempo-carga']
y_m= df['tiempo-maximo']
y2_m= df_2['tiempo-maximo']

# grafico tiempo carga
ticks = range(1,len(x)+1)
plt.plot(x,y_c)
# plt.plot(x,y2_c,label='spinlock',color='red')
plt.xlabel("Cantidad de threads")
plt.ylabel("Tiempo en segs")
plt.title('Carga de archivos con uniformidad de claves y ordenadas alfabéticamente')
plt.xticks(ticks)
plt.legend()
plt.grid()
plt.show()

plt.plot(x,y_m, label='uniforme')
plt.plot(x,y2_m,label='no uniforme',color='red')
plt.xlabel("Cantidad de threads")
plt.ylabel("Tiempo en segs")
plt.title('Encontrar el máximo con una distribución uniforme y no uniforme de palabras')
plt.xticks(ticks)
plt.grid()
plt.legend()
plt.show()