import random


class Tupla:
    def __init__(self, c1, c2):
        self.c1 = c1
        self.c2 = c2
    def __repr__(self):
        representacion = str(self.c1) + " " + str(self.c2)
        return representacion
    def __str__(self):
        representacion = str(self.c1) + " " + str(self.c2)
        return representacion
    def __eq__(self,otro):
        return (self.c1 == otro.c1 and self.c2 == otro.c2) or (self.c1 == otro.c2 and self.c2 == otro.c1)

def generador_bosque(grafo):
    grafo = list(range(1,nodos+1))
    
    nodo1 , nodo2 = random.sample(grafo, 2)
    grafo.remove(nodo1)
    grafo.remove(nodo2)
    res = [Tupla(nodo1,nodo2)]
    usados = [nodo1,nodo2]
    while len(grafo) > 0:
        nodo = random.sample(usados, 1)[0]
        union = random.sample(grafo, 1)[0]
        res.append(Tupla(union,nodo))
        grafo.remove(union)
        usados.append(union)
    elementos_a_eliminar = random.sample(res,random.randrange(1,len(res)-1))
    for elem in elementos_a_eliminar:
        res.remove(elem)
    aristas = len(res)
    print(str(len(grafo)) + " " + str(aristas))
    for elem in res:
        print(elem)


     

if __name__ == "__main__":
    nodos = 10
    generador_bosque(nodos)   
