import csv

import matplotlib.pyplot as plt
import pandas as pd


def muestra(i):
    return (int(i) // 10)


def completo(i):
    return (int(i) + 1) * 15


datos1 = open('tests_tiempo_hasta_150_nodos/arbolTiempoAdaptativo.csv')
arbol = csv.reader(datos1, delimiter=';', lineterminator='\n')

datos2 = open('tests_tiempo_hasta_150_nodos/bosqueTiempoAdaptativo.csv')
bosque = csv.reader(datos2, delimiter=';', lineterminator='\n')

datos3 = open('tests_tiempo_hasta_150_nodos/completoTiempoAdaptativo.csv')
csv_completo = csv.reader(datos3, delimiter=';', lineterminator='\n')

datos4 = open('tests_tiempo_hasta_150_nodos/rosquillaTiempoAdaptativo.csv')
rosquilla = csv.reader(datos4, delimiter=';', lineterminator='\n')
df = pd.DataFrame()

datos_bosque = [i for i in bosque]
datos_arbol = [i for i in arbol]
datos_rosquilla = [i for i in rosquilla]
datos_completo = [i for i in csv_completo]

promedio_bosque = {}
promedio_completo = {}
promedio_rosquilla = {}
promedio_arbol = {}

for data in datos_bosque:
    promedio_bosque[muestra(data[0])] = promedio_bosque.get(muestra(data[0]), 0) + (float(data[1]) / 200)

for data in datos_completo:
    promedio_completo[completo(data[0])] = promedio_completo.get(completo(data[0]), 0) + (float(data[1]) / 20)

for data in datos_rosquilla:
    promedio_rosquilla[muestra(data[0])] = promedio_rosquilla.get(muestra(data[0]), 0) + (float(data[1]) / 200)

for data in datos_arbol:
    promedio_arbol[muestra(data[0])] = promedio_arbol.get(muestra(data[0]), 0) + (float(data[1]) / 200)

df['cantidad de nodos'] = [int(i) for i in range(10, 150 + 1, 10)]

df['Bosque'] = [i for i in promedio_bosque.values()]
df['Arbol'] = [i for i in promedio_arbol.values()]
df['Rosquilla'] = [i for i in promedio_rosquilla.values()]
df['Completo'] = [i for i in promedio_completo.values()]

plt.clf()
grafico = df.groupby('cantidad de nodos').mean().plot(title="Constructiva Adaptativa", logy=True)
grafico.set_ylabel("Tiempo en Milisegundos")
# grafico_backtracking_poda = df_backtracking_poda.groupby('cantidad de elementos').mean().plot(title="Implementación de Backtracking con poda")
# grafico_backtracking_poda.set_ylabel("Tiempo en ms")
# grafico_dinamico = df_dinamico.groupby('cantidad de elementos').mean().plot(title='Implementación de programacion dinamica')
# grafico_dinamico.set_ylabel("Tiempo en ms")
#
# sns.jointplot(df_dinamico_2['c*n^3'], df_dinamico['tiempo en ms dinamico'], kind="reg")
# sns.jointplot(df_backtracking['c*3^n'], df_backtracking['tiempo en ms backtracking sin poda'], kind="reg")

plt.show()
