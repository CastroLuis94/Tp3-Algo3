import csv

import matplotlib.pyplot as plt
import pandas as pd


def muestra(i):
    return (int(i) // 10)


def completo(i):
    return (int(i) + 1) * 15


datos1 = open('tests_tiempo_hasta_150_nodos/completoTiempoAdaptativo.csv')
adaptativa = csv.reader(datos1, delimiter=';', lineterminator='\n')

datos2 = open('tests_tiempo_hasta_150_nodos/completoTiempoConstructiva.csv')
constructiva = csv.reader(datos2, delimiter=';', lineterminator='\n')

datos3 = open('tests_tiempo_hasta_150_nodos/completoTiempoGrasp.csv')
grasp = csv.reader(datos3, delimiter=';', lineterminator='\n')

datos4 = open('tests_tiempo_hasta_150_nodos/completoTiempoLocal.csv')
local = csv.reader(datos4, delimiter=';', lineterminator='\n')
df = pd.DataFrame()

datos_constructiva = [i for i in constructiva]
datos_adaptativa = [i for i in adaptativa]
datos_local = [i for i in local]
datos_grasp = [i for i in grasp]

promedio_constructiva = {}
promedio_grasp = {}
promedio_local = {}
promedio_adaptativa = {}

for data in datos_constructiva:
    promedio_constructiva[completo(data[0])] = promedio_constructiva.get(completo(data[0]), 0) + (float(data[1]) / 20)

for data in datos_grasp:
    promedio_grasp[completo(data[0])] = promedio_grasp.get(completo(data[0]), 0) + (float(data[1]) / 20)

for data in datos_local:
    promedio_local[completo(data[0])] = promedio_local.get(completo(data[0]), 0) + (float(data[1]) / 20)

for data in datos_adaptativa:
    promedio_adaptativa[completo(data[0])] = promedio_adaptativa.get(completo(data[0]), 0) + (float(data[1]) / 20)

df['cantidad de nodos'] = [int(i) for i in range(10, 150 + 1, 10)]

df['Constructiva Greedy'] = [i for i in promedio_constructiva.values()]
df['Constructiva Adapatativa'] = [i for i in promedio_adaptativa.values()]
df['Busqueda Local'] = [i for i in promedio_local.values()]
df['GRASP'] = [i for i in promedio_grasp.values()]

plt.clf()
grafico = df.groupby('cantidad de nodos').mean().plot(title="Completo", logy=True)
grafico.set_ylabel("Tiempo en milisegundos")
# grafico_backtracking_poda = df_backtracking_poda.groupby('cantidad de elementos').mean().plot(title="Implementación de Backtracking con poda")
# grafico_backtracking_poda.set_ylabel("Tiempo en ms")
# grafico_dinamico = df_dinamico.groupby('cantidad de elementos').mean().plot(title='Implementación de programacion dinamica')
# grafico_dinamico.set_ylabel("Tiempo en ms")
#
# sns.jointplot(df_dinamico_2['c*n^3'], df_dinamico['tiempo en ms dinamico'], kind="reg")
# sns.jointplot(df_backtracking['c*3^n'], df_backtracking['tiempo en ms backtracking sin poda'], kind="reg")

plt.show()
