import numpy as np
import pandas as pd
# import seaborn as sns
import matplotlib.pyplot as plt

# df = pd.read_csv("out.csv")
df = pd.read_csv("out-files/out-no-uniform.csv")
df_2 = pd.read_csv("out-files/out-tmp-iguales-con-b.csv")

x= df['threads']
y_c= df['tiempo-carga']
y2_c= df_2['tiempo-carga']
y_m= df['tiempo-maximo']
y2_m= df_2['tiempo-maximo']

# grafico tiempo carga
ticks = range(1,len(x)+1)
plt.plot(x,y_c) #label=''
# plt.plot(x,y2_c,label='con a y b',color='red')
plt.xlabel("Cantidad de threads")
plt.ylabel("Tiempo en segs")
plt.title('Carga de archivos con una distribución no uniforme de palabras')
plt.xticks(ticks)
plt.legend()
plt.grid()
plt.show()

plt.plot(x,y_m) # label=''
# plt.plot(x,y2_m,label='con a y b',color='red')
plt.xlabel("threads")
plt.ylabel("Tiempo en segs")
plt.title('Encontrar el máximo con una distribución no uniforme de palabras')
plt.xticks(ticks)
plt.grid()
plt.show()