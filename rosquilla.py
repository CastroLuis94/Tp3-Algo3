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

def generador_grafo_completo(lista_de_nodos,porcentaje):
    aristas = int(len(lista_de_nodos) * (len(lista_de_nodos) - 1) / 2)
    indice_a_sacar = random.sample(range(len(lista_de_nodos)), int(aristas*porcentaje/100))
    indice_a_sacar.sort()
    indice_a_sacar.reverse()
    # imprimo la segunda linea c1,c2 elegidas de forma random(es random es sin repetidos)
    res = []
    aristas = int(len(lista_de_nodos) * (len(lista_de_nodos) - 1) / 2)
    for i in lista_de_nodos:
        for k in lista_de_nodos:
            if (k > i):
                res.append(Tupla(i, k))
    for elem in indice_a_sacar:
        res.pop(elem)
    random.shuffle(res)
    return res

def generador_arbol(grafo):
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
        usados.append(nodo)
    return res

def generar_grafo_conexo(grafo,porcentaje):
    nodosCompleto = generador_grafo_completo(grafo[:],0)
    nodosArbol = generador_arbol(grafo[:])
    for elem in nodosArbol:
        nodosCompleto.remove(elem)
    return nodosArbol + random.sample(nodosCompleto,int(len(nodosCompleto)*porcentaje/100))

def generar_grafo_de_pares(lista_de_nodos):
    res = []
    if len(lista_de_nodos) % 2 != 0 :
        lista_de_nodos.pop(len(lista_de_nodos)-1)
        while len(lista_de_nodos):
            nodo1 , nodo2 = random.sample(lista_de_nodos, 2)
            lista_de_nodos.remove(nodo1)
            lista_de_nodos.remove(nodo2)
            res.append(Tupla(nodo1,nodo2))
        return res
    else:
        while len(lista_de_nodos):
            nodo1 , nodo2 = random.sample(lista_de_nodos, 2)
            lista_de_nodos.remove(nodo1)
            lista_de_nodos.remove(nodo2)
            res.append(Tupla(nodo1,nodo2))
        return res

def rosquilla(cant_nodos, porcentaje):
    cant_nodos_grafo_central = max(3,int(cant_nodos*porcentaje/100))
    lista_de_nodos = [x for x in range(1,cant_nodos + 1)]
    elegir_indices = random.sample(range(0,len(lista_de_nodos)), cant_nodos_grafo_central)
    grafo_central = []
    for elem in elegir_indices:
        grafo_central.append(lista_de_nodos[elem])
    grafo_central = generar_grafo_conexo(grafo_central,30)
    elegir_indices.sort()
    elegir_indices.reverse()
    a_eliminar = elegir_indices
    for elem in a_eliminar:
        lista_de_nodos.remove(lista_de_nodos[elem])
    lista_de_nodos = generar_grafo_de_pares(lista_de_nodos)
    grafo = grafo_central + lista_de_nodos
    print(str(cant_nodos) + " " + str(len(grafo)))
    for elem in grafo:
        print(elem)
     

if __name__ == "__main__":
    """NOTA! el porcentaje indica cuando cual es el porcentaje que quiero en mi grafo principal,
     si lo mandan a 0 el grafo central va a tener 3 nodos porque asi lo configure por default
     , si le mandan menos de 3 nodos explota, no se me ocurre otro caso que explote. Los casos
     para mi mas interesantes serian cuando tenemos muchos nodos en el grafo central pero muchos
     mas a su alrededor, para demostrar si nuestros algoritmos llegan a darse cuenta donde esta
     la CMF posta. """
    porcentaje = 25
    nodos = 31
    rosquilla(nodos, porcentaje)   
