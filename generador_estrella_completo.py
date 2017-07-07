import random


class Tupla:
    def __init__(self, c1, c2):
        self.c1 = c1
        self.c2 = c2
    def __repr__(self):
        print(str(self.c1) + " " + str(self.c2))
    def __str__(self):
        representacion = str(self.c1) + " " + str(self.c2)
        return representacion


def esta(lista,nodo):
    for elem in lista:
        if nodo == elem:
            return False
    return True


def generador_grafo_completo(nodos):
    aristas = int(len(nodos) * (len(nodos) - 1) / 2)
    # imprimo la segunda linea c1,c2 elegidas de forma random(es random es sin repetidos)
    res = []
    for i in nodos:
        for k in nodos:
            if (k > i):
                res.append(Tupla(i, k))
    random.shuffle(res)
    return res

def estrella(nodos):
    indice = random.sample(range(0,len(nodos)), 1)[0]
    nodo_raiz = nodos[indice]
    res = []
    for elem in nodos:
        if elem != nodo_raiz:
            res.append(Tupla(elem,nodo_raiz))
    random.shuffle(res)
    return res

def generador_estrella_completo(nodos):
    particion = int(nodos/2)
    nodos = [x for x in range(1,nodos + 1)]
    particion1 = random.sample(nodos, int(len(nodos)/2) - 1 )
   
    particion2 = []
    for elem in nodos:
        if esta(particion1,elem):
            particion2.append(elem)
    completo = generador_grafo_completo(particion1)
    star = estrella(particion2)
    print(str(len(nodos)) + " " + str(len(completo)+len(star)) )
    res = completo + star
    for elem in res:
        print(elem)


if __name__ == "__main__":
    nodos = 12
    generador_estrella_completo(nodos)   
