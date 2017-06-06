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

def generador_grafo_completo(cant_nodos, porcentaje):
    aristas = int(cant_nodos * (cant_nodos - 1) / 2)
    indice_a_sacar = random.sample(range(aristas), int(aristas*porcentaje/100))
    indice_a_sacar.sort()
    indice_a_sacar.reverse()
    aristas = int((cant_nodos * (cant_nodos - 1)) / 2) - len(indice_a_sacar)
    print(str(cant_nodos) + " " + str(aristas))
    # imprimo la segunda linea c1,c2 elegidas de forma random(es random es sin repetidos)
    res = []
    for i in range(1, cant_nodos + 1):
        for k in range(1, cant_nodos + 1):
            if (k > i):
                res.append(Tupla(i, k))
    for elem in indice_a_sacar:
        res.pop(elem)
    random.shuffle(res)
    for elem in res:
        print(elem)

if __name__ == "__main__":
    porcentaje = 0
    nodos = 3
    generador_grafo_completo(nodos, porcentaje)
    
