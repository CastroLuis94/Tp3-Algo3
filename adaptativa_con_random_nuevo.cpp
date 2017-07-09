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


grafo constructiva_con_random(grafo g, int& maxfrontera,int  porcentaje){
    srand(time(NULL)); 
    vector <int> listaNodos = g.ejes();
    int indiceNodoElegido = rand() % (listaNodos.size());
    int nodoElegido = listaNodos[indiceNodoElegido];
    maxfrontera = g.degree(nodoElegido);
    vector <int> nodosDisponibles = g.get_neigh(nodoElegido);   
   //vemos los vecinos del nodo random elegido...(el vecindario esta conformado por los vecinos del de mayor grado)
    vector <vector < int > > aux;//en aux guardo grafo nuevo
    vector <int> nodos;//nodos comienza vacio(formo la clique aqui?)
    nodos.push_back(nodoElegido);//aqui agregamos nodos de la clique
    aux.resize(nodoElegido + 1);//aux tiene tantos nodos como vecinos.
    grafo grafoActual(aux,nodos);//genero un grafo vacio con maximo + 1 posiciones.    
    vector<int> nodosDisponiblesAux;
   // grafo grafoActualAux = grafoActual;   
    while (nodosDisponibles.size() > 0 ){//mientras haya un nodo que fue vecino al primero que  vi.(mientras no sea igual a los aux.)
        int i = 0;        
        grafo copia = grafoActual;
        vector< tuple<int, int> > fronteras(nodosDisponibles.size(), make_tuple(maxfrontera, 0));//genero copia al actual
        while(i < nodosDisponibles.size()){//agrego el nodo que maximize la frontera.
            int nodoAAgregar = nodosDisponibles[i];            
            copia.add_to_clique(nodoAAgregar);
            fronteras[i] = make_tuple(frontera(copia,g), i);
            i++;
            copia.del_special();//vacio la copia
        }
        sort(fronteras.begin(), fronteras.end());//me ordena losnodos por el de menos al que mas frontera aumenta.
        reverse(fronteras.begin(), fronteras.end());
        vector<tuple<int, int> >elecciones;
        float porcentaje;
        porcentaje = floor((nodosDisponibles.size()/10)*porcentaje);
        if(porcentaje == 0){
            porcentaje = 1;    
        }        
        for(float i = 0; i < porcentaje; i++){
            if (get<0>(fronteras[i]) >= maxfrontera){
                elecciones.push_back(fronteras[i]);
            }
        }
        srand(time(NULL)); 
        int indice; 
        if ( elecciones.size() == 0){
            break;
        }else{ 
            indice = rand() % elecciones.size();
        }
        nodosDisponiblesAux = interseccion(nodosDisponibles,g.get_neigh(nodosDisponibles[get<1>(elecciones[indice])]));//los vecimos son los que estan en disponibles aux
        //grafoActualAux = grafoActual;
        copia.add_to_clique(nodosDisponibles[get<1>(elecciones[indice])]);
        maxfrontera = get<0>(elecciones[indice]);//actualizo la frontera            
        //grafoActualAux = copia;//actualizo el grafoaux
        //copia.del_special();
        if(nodosDisponibles.size() == nodosDisponiblesAux.size()){
            break;
        }
        grafoActual = copia;
        //copia.del_special();
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
    grafo g(listaAdyacencia);
    int maxfrontera = 0;
    int porcentaje = 3;
    grafo res = constructiva_con_random(g, maxfrontera, porcentaje);
    cout << maxfrontera << " ";
    cout << (res.ejes()).size() << " ";
    mostrar(res.ejes());
    cout << "" <<endl;
    
    return 0;
}