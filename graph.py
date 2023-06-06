import numpy as np
import pandas as pd
# import seaborn as sns
import matplotlib.pyplot as plt

# df = pd.read_csv("out.csv")
df = pd.read_csv("out-palabras-iguales.csv")

x= df['threads']
y_c= df['tiempo-carga']
y_m= df['tiempo-maximo']

# df['log_threads'] = np.log(df['time'])
# df['log_cota'] = np.log(df['size'])
# ax1 = sns.lmplot(x='threads', y='tiempo', height=6, data=df)
ticks = range(1,21)
plt.plot(x,y_c)
plt.xlabel("threads")
plt.ylabel("tiempo")
plt.title('carga')
plt.xticks(ticks)
plt.grid()
plt.show()

plt.plot(x,y_m)
plt.xlabel("threads")
plt.ylabel("tiempo")
plt.title('max')
plt.xticks(ticks)
plt.grid()
plt.show()