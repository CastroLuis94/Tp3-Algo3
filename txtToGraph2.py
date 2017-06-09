#El grafico no se ve bien para algunas configuraciones o muchos vertices.

import sys
import math
import random
import networkx as nx
import matplotlib.pyplot as plt


def levanta_cantidad_nodos(nombre):
    archivo = open(nombre, "r") 
    contenido = archivo.read()
    contenido = contenido.split()
    res = []
    for string in contenido:
        res.append(int(string))
    return res[0]

def levanta_nodos(nombre):
    archivo = open(nombre, "r") 
    contenido = archivo.read()
    contenido = contenido.split()
    res = []
    for string in contenido:
        res.append(int(string))
    return res[2:]
nodos = levanta_cantidad_nodos('grafo1.txt')
nodos_usados = levanta_nodos('salida.txt')
G=nx.Graph()



G.add_nodes_from([1,nodos])

i = 0
while i < len(nodos_usados):
	k = i + 1
	while k < len(nodos_usados):
		if i < k:
			c1 = nodos_usados[i]
			c2 = nodos_usados[k]
			color = 'k'
			G.add_edge(c1, c2,color=color)
		k += 1
	i+=1

j = 1
while j <= nodos:
    G.add_node(j)
    j+=1

edges = G.edges()

# Elegir el layout
pos=nx.circular_layout(G)
nx.draw_circular(G,with_labels=True )
nx.draw(G, pos, edges=edges)
# Elegir donde guardar la imagen
plt.show()



