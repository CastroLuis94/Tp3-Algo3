#El grafico no se ve bien para algunas configuraciones o muchos vertices.

import sys
import math
import random
import networkx as nx
import matplotlib.pyplot as plt


G=nx.Graph()

linea0 = input().split(' ')
nodos = int(linea0[0])
ejes = int(linea0[1])
G.add_nodes_from([1,nodos])

i = 0
while(i < ejes):
	lineaEje_i = input().split(' ')
	c1 = int(lineaEje_i[0])
	c2 = int(lineaEje_i[1])
	color = 'k'
	G.add_edge(c1, c2,color=color)
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