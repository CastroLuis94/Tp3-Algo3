import random

from rosquilla import Tupla


def generador_tira_de_cliques(n, tam_tira, frontera_maxima):
    g = []
    tira = [i for i in range(1, tam_tira + 1)]
    nodos_restantes = [i for i in range(tam_tira + 1, n + 1)]

    random.shuffle(tira)
    for i in range(tam_tira - 1):
        v = tira[i]
        w = tira[i + 1]
        g.append(Tupla(v, w))
        tira.append(i)
    random.shuffle(tira)
    tam_clique = 4

    clique_aux = [nodos_restantes.pop() for _ in range(tam_clique)]

    clique = generar_clique(clique_aux)  # Deberia ser lista de tuplas
    for e in clique:
        g.append(e)
    for _ in range(frontera_maxima):
        w = tira.pop()
        v = random.choice(clique_aux)
        g.append(Tupla(v, w))

    for i in nodos_restantes:
        v = tira.pop()
        g.append(Tupla(v, i))
    while nodos_restantes:
        c = random.sample(nodos_restantes, 3)
        for i in c:
            for j in c:
                if j != i:
                    g.append(Tupla(j, i))
        for i in c:
            nodos_restantes.remove(i)

    print(str(n) + " " + str(len(g)))
    for elem in g:
        print(elem)


def generar_clique(nodos):
    res = []
    for i in nodos:
        for j in nodos:
            if i != j:
                res.append(Tupla(i, j))
    return res


if __name__ == "__main__":
    n = 30
    tam_tira = 15
    cantidad_cliques = 4
    frontera_maxima = 10

    generador_tira_de_cliques(n, tam_tira, frontera_maxima)
