import random

from rosquilla import Tupla


def frontera_clique(g, n, clique):
    clique_aux = generar_clique(clique)
    adyacencia = [set() for i in range(n + 1)]
    ady_clique = [set() for i in range(n + 1)]
    for i in g:
        adyacencia[i.c1].add(i.c2)
        adyacencia[i.c2].add(i.c1)
    for i in clique_aux:
        ady_clique[i.c1].add(i.c2)
        ady_clique[i.c2].add(i.c1)
    res = 0
    for i in clique:
        grado = len(adyacencia[i])
        grado_clique = len(ady_clique[i])
        res += grado - grado_clique
    return res


def generador_tira_de_cliques(n, tam_tira, frontera_maxima, clique=None):
    g = []
    nodos = [i for i in range(1, n + 1)]
    random.shuffle(nodos)

    tam_clique = len(clique) or 4

    if clique:
        clique_aux = clique
        for i in clique_aux:
            nodos.remove(i)
    else:
        clique_aux = [nodos.pop() for _ in range(tam_clique)]

    tira = random.sample(nodos, tam_tira)

    for i in range(tam_tira - 1):
        v = tira[i]
        w = tira[i + 1]
        g.append(Tupla(v, w))

    for i in tira:
        nodos.remove(i)

    random.shuffle(tira)

    clique = generar_clique(clique_aux)  # Deberia ser lista de tuplas
    g += clique
    for i in range(frontera_maxima):
        w = tira.pop()
        v = clique_aux[(i % tam_clique)]
        g.append(Tupla(v, w))
    cliques = []
    while nodos:
        tam = random.randint(1, tam_clique)
        c = nodos[:tam]
        clique.append(c)
        for i in c:
            for j in c:
                if j != i:
                    g.append(Tupla(j, i))
        for i in c:
            nodos.remove(i)
        cliques.append(c)
        frontera = random.randint(1, frontera_maxima - 1)
        for i in range(frontera):
            if not tira:
                break
            v = tira.pop()
            w = c[i % len(c)]
            g.append(Tupla(v, w))
    if nodos:
        v = nodos.pop()
        for i in nodos[:frontera_maxima - 1]:
            g.append(Tupla(v, i))
    for i in cliques:
        assert frontera_maxima > frontera_clique(g, n, i)
    assert frontera_maxima == frontera_clique(g, n, clique_aux)
    print(str(n) + " " + str(len(g)))
    for elem in g:
        print(elem)


def generar_clique(nodos):
    res = []
    for i in nodos:
        for k in nodos:
            if (k > i):
                res.append(Tupla(i, k))
    return res


if __name__ == "__main__":
    n = 300
    tam_tira = 200  # mientras mas cercano sea este valor al n genera mas optimos locales valores puede generar

    clique = [214, 23, 14, 2, 3]

    frontera_maxima = 30
    generador_tira_de_cliques(n, tam_tira, frontera_maxima, clique)
