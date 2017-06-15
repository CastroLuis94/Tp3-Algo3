#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>

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

vector <int> constructiva(grafo g, int& maxfrontera){
    vector <int> nodoPorGrado = g.nodes_by_degree();
    int maximoNodo = nodoPorGrado[nodoPorGrado.size() - 1] + 1 ;
    maxfrontera = g.degree(maximoNodo);
    vector <int> nodosDisponibles = g.get_neigh(maximoNodo);
    /*int i = 0;
    while(i < nodoPorGrado.size()){
        cout << "imprimiento nodo" << endl;
        cout << nodoPorGrado[i]+1 << endl;
        cout << "imprimiento grado del nodo" << endl;
         cout << (g.degree(nodoPorGrado[i]+1)) << endl;
         i++;
    }
   */
    //cout << maximoNodo << endl;
    //mostrar(nodosDisponibles);
    vector <vector < int > > aux;
    vector <int> nodos;
    //cout << "yolo2" <<endl;
    nodos.push_back(maximoNodo);
    aux.resize(maximoNodo + 1);
    // cout << "yolo3" <<endl;
    grafo mejorClique(aux,nodos);
   
    //mostrar(mejorClique.ejes());
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    while (nodosDisponibles.size() > 0 ){
        int i = 0;
        int maximoGrado = 0;
        while(i < nodosDisponibles.size()){
            if (g.degree(nodosDisponibles.at(i)) > maximoGrado and not esta1(grafoActual.ejes(),nodosDisponibles.at(i))){
                nodoAAgregar = nodosDisponibles.at(i);
                maximoGrado = g.degree(nodosDisponibles.at(i));
            }
            i++;
        }
        
        grafoActual.add_to_clique(nodoAAgregar);
        /*mostrar(grafoActual.ejes());
        cout << "valores de las fronteras" <<endl;
        cout << frontera(grafoActual,g) <<endl;
         cout << maxfrontera <<endl;
        */
        if (maxfrontera < frontera(grafoActual,g)){
            mejorClique = grafoActual;
            maxfrontera = frontera(grafoActual,g);
        }
        nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));
    }
    return mejorClique.ejes();
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


    vector <int> res = constructiva(g,maxfrontera);
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << res.size() << " ";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}