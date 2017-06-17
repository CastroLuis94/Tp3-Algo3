#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include "coloreo.h"


int elegiUno(vector< pair <int,float > > nodos){
        float chosen = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //cout << chosen <<endl;
        float current = 0;
        int i = 0;
        while(i < nodos.size()){
            //cout << current <<endl;
            //cout << nodos[i].second <<endl;
            current += nodos[i].second;
            if (current >= chosen){
                return nodos[i].first;
            }
            i++;
        }
    }


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

vector <pair<int , float> > calcularProbabilidades(grafo& g,int gradoTotal){
    vector < pair<int,float> > res;
    vector <int> ejes = g.ejes();
    int i = 0;
    while(i < ejes.size()){
        float probabilidad = (float)(g.degree(ejes[i]))/gradoTotal;
        
        res.push_back(make_pair(ejes[i],probabilidad));
        i++;
    }
    return res;
}

vector <int> grasp(grafo g, int& maxfrontera){
    vector <int> listaNodos = g.ejes();
    int gradoTotal = g.degrees();
    vector <pair<int , float> > listaNodosYProbabilidades = calcularProbabilidades(g,gradoTotal);
    int nodoElegido = elegiUno(listaNodosYProbabilidades);
    if(nodoElegido == 0){
        nodoElegido++;
    }
    vector <vector < int > > aux;
    vector <int> nodos;
    //cout << "yolo2" <<endl;
    nodos.push_back(nodoElegido);
    aux.resize(nodoElegido + 1);
    // cout << "yolo3" <<endl;
    grafo mejorClique(aux,nodos);
   
    //mostrar(mejorClique.ejes());
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    vector <int> nodosDisponibles = g.get_neigh(nodoElegido);
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


    vector <int> res = grasp(g,maxfrontera);
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << res.size() << " ";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}