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

vector<int> actualizar_Nodos_Disponibles(grafo g ,vector<int> nodosUsados){
    vector<int> res;
    if (nodosUsados.size() == 1){
        res = g.get_neigh(nodosUsados[0]);
    }
    else
    {   
        if(nodosUsados.size() == 0){
            res = g.ejes();
        }
        else
        {   
            res = g.get_neigh(nodosUsados[0]);
            int i = 1;
            while(i < nodosUsados.size()){
                res = interseccion(res,g.get_neigh(nodosUsados[i]));
                ++i;
            }
        }
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

vector <int> busquedalocal(grafo g, int& maxfrontera){
	vector <int> listaNodos = g.ejes();
    int indiceprimerNodo = rand() % (listaNodos.size());
    int primerNodo = listaNodos[indiceprimerNodo];   
    vector <int> nodosDisponibles = g.get_neigh(primerNodo);
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(primerNodo);
    aux.resize(primerNodo+ 1);   
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    while(nodosDisponibles.size() > 0){
    	int cont = 0;
    	while(cont < nodosDisponibles.size()) {
    		if(not esta1(grafoActual.ejes(),nodosDisponibles.at(cont))){
    			nodoAAgregar = nodosDisponibles.at(cont);
    		}
    		cont ++;
    	}
    	grafoActual.add_to_clique(nodoAAgregar);
    	nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));
    }
    maxfrontera = frontera(grafoActual,g);
    int mayorCreciente = maxfrontera;
    int nodomayorCreciente = 0;
    int cont = 0;
    grafo grafoaux(aux,grafoActual.ejes());
    int mayorDecreciente = maxfrontera;
	int nodomayorDecreciente = 0;
	grafoaux = grafoActual;
	bool fin = false;
	int nodoAeliminar;
    while (fin == false){
        mayorDecreciente = 0;
        mayorCreciente = 0;
        cont = 0;        
        while (cont < nodosDisponibles.size()){
            if (not esta1(grafoaux.ejes(),nodosDisponibles[cont])){
                grafoaux.add_to_clique(nodosDisponibles.at(cont));
                if(frontera(grafoaux,g) > mayorCreciente){
                    mayorCreciente = frontera(grafoaux,g);
                    nodomayorCreciente = cont;
                }
                grafoaux.del_from_clique(nodosDisponibles.at(cont));
            }
            cont ++;
        }
        cont = 0;
        while (cont < grafoaux.tamano()) {
            nodoAeliminar = grafoaux.ejes()[0];
            grafoaux.del_from_clique(nodoAeliminar);
            if (frontera(grafoaux,g) > mayorDecreciente){              
                mayorDecreciente = frontera(grafoaux,g);
                nodomayorDecreciente = nodoAeliminar;
            }
            grafoaux.add_to_clique(nodoAeliminar);
            cont ++;
        }
        if (mayorCreciente > maxfrontera and mayorCreciente > mayorDecreciente){
            grafoaux.add_to_clique(nodosDisponibles.at(nodomayorCreciente));
            maxfrontera = mayorCreciente;
            nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));   
        }else if (mayorDecreciente > maxfrontera) {
                    grafoaux.del_from_clique(nodomayorDecreciente);
                    maxfrontera = mayorDecreciente;
                    nodosDisponibles =actualizar_Nodos_Disponibles(g,grafoaux.ejes());
                }else{
                    fin = true;
                }
                
    }
	return grafoaux.ejes();
}



int main(){
    int vertices;
    cin >> vertices;
    int aristas;
    cin >> aristas;
    vector< vector <int> > listaAdyacencia = levantarAristas(vertices,aristas);
    grafo g(listaAdyacencia);
    int maxfrontera = 0;
    vector <int> res = busquedalocal(g,maxfrontera);
    cout << maxfrontera << " " ;
    cout << res.size() << " ";
    mostrar(res);    
    return 0;
}