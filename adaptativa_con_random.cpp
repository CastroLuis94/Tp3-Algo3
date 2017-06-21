#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>
#include <tuple>
#include "coloreo.h"



bool esta1(vector<int> nodos,int v){    
    for(int i = 0; i < nodos.size(); i++){
        if(nodos[i] == v){
            return true;
        }
    }
    return false;
}


int frontera(grafo& clique, grafo& g){
   int res = 0;
   vector <int> nodos = clique.ejes();
   int i = 0;
   while(i < nodos.size()){
       res += g.degree(nodos[i]) - clique.degree(nodos[i]);
       i++;
   }
   return res;
}

vector<int> interseccion(vector<int>& nodosDisponibles, vector<int> vecinos){
    vector<int> res;
    int i = 0;
    while(i < vecinos.size()){
        if (esta1(nodosDisponibles,vecinos[i])){
            res.push_back(vecinos[i]);
        }
        i++;
    }
    return res;
}










void mostrar(vector<int> vs){
    int i = 0;
    while(i < vs.size()){
        cout << vs[i] << " ";
        i++;
    }
     cout << "" << endl;
}
void mostrar(vector<vector<int> > vs){
    cout << "[";
    int i = 0;
    while(i < vs.size()){
        mostrar(vs[i]);
        i++;
        if(i < vs.size()){
            cout << ",";
        }
    }
    cout << "]"<<endl;
}

vector< vector < int > > levantarAristas(int vertices,int cantAristas){
    int i = 0;
    vector < vector <int> > res;
    res.resize(vertices + 1);
    while(i < cantAristas){
        int nodo1;
        cin >> nodo1;
        int nodo2;
        cin >> nodo2;
        res[nodo1].push_back(nodo2);
        res[nodo2].push_back(nodo1);
        i++;
    }
    return res;
}

/*grafo constructiva(grafo g, int& maxfrontera){
    vector <int> nodoPorGrado = g.nodes_by_degree();
    int maximoNodo = nodoPorGrado[nodoPorGrado.size() - 1] + 1 ;
    maxfrontera = g.degree(maximoNodo);
    vector <int> nodosDisponibles = g.get_neigh(maximoNodo);
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(maximoNodo);
    aux.resize(maximoNodo + 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    vector<int> nodosDisponiblesAux;
    grafo grafoActualAux = grafoActual;
    while (nodosDisponibles.size() > 0 ){
        int i = 0;
        int maximoGrado = 0;
        grafo copia = grafoActual;
        while(i < nodosDisponibles.size()){
            int nodoAAgregar = nodosDisponibles[i];
            grafoActualAux = grafoActual;
            copia.add_to_clique(nodoAAgregar);
            int fronteraDeLaCopia = frontera(copia,g);
            if (fronteraDeLaCopia >= maxfrontera){
                nodosDisponiblesAux = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));
                maxfrontera = fronteraDeLaCopia;
                grafoActualAux = copia;
            }
            i++;
            copia.del_special();
        }
        if(nodosDisponibles.size() == nodosDisponiblesAux.size()){
            break;
        }
        grafoActual = grafoActualAux;
        nodosDisponibles = nodosDisponiblesAux;
    }
    return grafoActual;
}*/




/*
grafo constructiva_con_random(grafo g, int& maxfrontera){
    vector <int> nodoPorGrado = g.nodes_by_degree();
    int maximoNodo = nodoPorGrado[nodoPorGrado.size() - 1] + 1 ;
    maxfrontera = g.degree(maximoNodo);
    //tenemos el nodo de mayor grado. maxfrontera comienza con sus vecinos como frontera maxima.
    vector <int> nodosDisponibles = g.get_neigh(maximoNodo);//vemos los vecinos del nodo de mayor frontera....(el vecindario esta conformado por los vecinos del de mayor grado)
    vector <vector < int > > aux;//en aux guardo grafo nuevo
    vector <int> nodos;//nodos comienza vacio(formo la clique aqui?)
    nodos.push_back(maximoNodo);//aqui agregamos nodos de la clique
    aux.resize(maximoNodo + 1);//aux tiene tantos nodos como vecinos.
    //grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);//genero un grafo vacio con maximo + 1 posiciones. 
    int nodoAAgregar;
    vector<int> nodosDisponiblesAux;
    grafo grafoActualAux = grafoActual;
    while (nodosDisponibles.size() > 0 ){//mientras haya un nodo que fue vecino al primero que  vi.(mientras no sea igual a los aux.)
        int i = 0;
        int maximoGrado = 0;
        grafo copia = grafoActual;//genero copia al actual
        while(i < nodosDisponibles.size()){
            int nodoAAgregar = nodosDisponibles[i];
            grafoActualAux = grafoActual;
            copia.add_to_clique(nodoAAgregar);
            int fronteraDeLaCopia = frontera(copia,g);
            if (fronteraDeLaCopia >= maxfrontera){//si la frontera de agregar este nodo aumenta la maxima
                nodosDisponiblesAux = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));//los vecimos son los que estan en disponibles aux
                maxfrontera = fronteraDeLaCopia;//actualizo la frontera
                grafoActualAux = copia;//actualizo el grafoaux
            }
            i++;
            copia.del_special();//vacio la copia
        }
        if(nodosDisponibles.size() == nodosDisponiblesAux.size()){
            break;
        }
        grafoActual = grafoActualAux;
        nodosDisponibles = nodosDisponiblesAux;
    }
    return grafoActual;
}
*/
grafo constructiva_con_random(grafo g, int& maxfrontera){
    vector <int> nodoPorGrado = g.nodes_by_degree();
    int maximoNodo = nodoPorGrado[nodoPorGrado.size() - 1] + 1 ;
    maxfrontera = g.degree(maximoNodo);
    //vector<int> maximos(3, 0);
    //tenemos el nodo de mayor grado. maxfrontera comienza con sus vecinos como frontera maxima.
    vector <int> nodosDisponibles = g.get_neigh(maximoNodo);//vemos los vecinos del nodo de mayor frontera....(el vecindario esta conformado por los vecinos del de mayor grado)
    vector <vector < int > > aux;//en aux guardo grafo nuevo
    vector <int> nodos;//nodos comienza vacio(formo la clique aqui?)
    nodos.push_back(maximoNodo);//aqui agregamos nodos de la clique
    aux.resize(maximoNodo + 1);//aux tiene tantos nodos como vecinos.
    //grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);//genero un grafo vacio con maximo + 1 posiciones. 
    int nodoAAgregar;
    vector<int> nodosDisponiblesAux;
    grafo grafoActualAux = grafoActual;
    while (nodosDisponibles.size() > 0 ){//mientras haya un nodo que fue vecino al primero que  vi.(mientras no sea igual a los aux.)
        int i = 0;
        int maximoGrado = 0;
        grafo copia = grafoActual;
        vector< tuple<int, int> > fronteras(nodosDisponibles.size(), make_tuple(maxfrontera, 0));//genero copia al actual
        while(i < nodosDisponibles.size()){//agrego el nodo que maximize la frontera.
            int nodoAAgregar = nodosDisponibles[i];
            grafoActualAux = grafoActual;
            copia.add_to_clique(nodoAAgregar);
            fronteras[i] = make_tuple(frontera(copia,g), i);
            i++;
            copia.del_special();//vacio la copia
        }
        sort(fronteras.begin(), fronteras.end());//me ordena losnodos por el de menos al que mas frontera aumenta.
        reverse(fronteras.begin(), fronteras.end());
        vector<tuple<int, int> >elecciones;
        for(int i = 0; i < 3; i++){
            elecciones.push_back(fronteras[i]);
        }
        int indice = rand() % elecciones.size(); 
        if(get<0>(elecciones[indice]) >= maxfrontera){
            nodosDisponiblesAux = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));//los vecimos son los que estan en disponibles aux
            maxfrontera = get<1>(elecciones[indice]);//actualizo la frontera
            grafoActualAux = copia;//actualizo el grafoaux
        }
        if(nodosDisponibles.size() == nodosDisponiblesAux.size()){
            break;
        }
        grafoActual = grafoActualAux;
        nodosDisponibles = nodosDisponiblesAux;
    }
    return grafoActual;
}




















int main(){

 
    
    int vertices;
    cin >> vertices;
    int aristas;
    cin >> aristas;
    
    vector< vector <int> > listaAdyacencia = levantarAristas(vertices,aristas);
    //mostrar(listaAdyacencia);
    grafo g(listaAdyacencia);

    
    //mostrar(Conjunto_de_partes());
    int maxfrontera = 0;


    //grafo res = constructiva(g,maxfrontera);
    grafo res = constructiva_con_random(g, maxfrontera);
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << (res.ejes()).size() << " ";
    mostrar(res.ejes());
    cout << "" <<endl;
    
    return 0;
}