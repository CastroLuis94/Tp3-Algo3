#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include <tuple>
#include "coloreo.h"


int minimaFrontera(vector< pair< grafo, int > >& respuestas){
    int i = 0;
    int minimo = respuestas[0].second;
    while(i < respuestas.size()){
        if(minimo < respuestas[i].second){
            minimo = respuestas[i].second;
        }
        i++;
    }
    return minimo;
}

vector< pair< grafo, int > >& actualizarRespuestas(vector< pair< grafo, int > >& respuestas, grafo& g,int frontera,int tamanioMaximoDeseado){
    int minimo = minimaFrontera(respuestas);
    vector< pair< grafo, int > > aux;
    if (respuestas.size() >= tamanioMaximoDeseado){
        if(minimo < frontera){
            int i = 0;
            bool yaSaqueUno = false;
            while(i < respuestas.size()){
                if(respuestas[i].second != minimo){
                    if(yaSaqueUno){
                        aux.push_back(respuestas[i]);
                    }
                }else{
                yaSaqueUno = true;
                }
                i++;
            }
            aux.push_back(make_pair(g,frontera));
            respuestas = aux;
            return respuestas;
        }
    }else{
        respuestas.push_back(make_pair(g,frontera));
    }
    return respuestas;

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


vector <int> busquedalocal(grafo original,grafo g, int& maxfrontera){
    vector <int> listaNodos = g.ejes();
    vector <int> nodosDisponibles;
    vector <int> nodos;
     vector <vector <int> > aux;
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    int cont = 0;
    grafo grafoaux(aux,grafoActual.ejes());
    grafoaux = grafoActual;
    bool fin = false;
    bool flag = false;
    int nodoAeliminar;
    tuple <int, int, bool> aux2;
    vector< tuple< int, int,bool > > guardar;
    int contador = 0;
    cout << "yolo1" <<endl;
    while (contador < g.tamano()*2){
        while (cont < nodosDisponibles.size()){
            flag = false;
            grafoaux.add_to_clique(nodosDisponibles.at(cont));
            if (guardar.size() < 5){
                if(frontera(grafoaux,g) >= maxfrontera){
                    aux2 = make_tuple(cont,frontera(grafoaux,g),true);
                    guardar.push_back(aux2);
                }
            }
            else
            {
                for (int i = 0; i < guardar.size() and flag == false ; ++i)
                {
                    if (frontera(grafoaux,g) > get<2>(guardar[i]) )
                    {
                        //aux2 = make_tuple(cont,frontera(grafoaux,g),true);
                        get<0>(guardar[i]) = cont;
                        get<1>(guardar[i]) = frontera(grafoaux,g);
                        get<2>(guardar[i]) = true;
                        flag = true;
                    }
                }
            }
            grafoaux.del_from_clique(nodosDisponibles.at(cont));
            cont ++;
        }
        cout << "yolo2" <<endl;
        cont = 0;
        while (cont < grafoaux.tamano()) {
            nodoAeliminar = grafoaux.ejes()[0];
            flag = false;
            grafoaux.del_from_clique(nodoAeliminar);
             if (guardar.size() < 5){
                if(frontera(grafoaux,g) > maxfrontera){
                    aux2 = make_tuple(nodoAeliminar,frontera(grafoaux,g),false);
                    guardar.push_back(aux2);
                }
            }
            else
            {
                for (int i = 0; i < guardar.size() and flag == false ; ++i)
                {
                    if (frontera(grafoaux,g) > get<2>(guardar[i]) )
                    {
                        //aux2 = make_tuple(nodoAeliminar,frontera(grafoaux,g),false);
                        //guardar.push_back(aux2);
                        get<0>(guardar[i]) = nodoAeliminar;
                        get<1>(guardar[i]) = frontera(grafoaux,g);
                        get<2>(guardar[i]) = false;
                        flag = true;
                    }
                }
            }
            grafoaux.add_to_clique(nodoAeliminar);
            cont ++;
        }
        
        if(guardar.size() > 0){
            int indice = rand() % guardar.size();
            aux2 = guardar[indice];
            if (get<2>(aux2))
            {
            grafoaux.add_to_clique(get<0>(aux2));
            maxfrontera = get<1>(aux2);  
            }
            else
            {
                grafoaux.del_from_clique(get<0>(aux2));
                maxfrontera = get<1>(aux2);
            }
        }
        ++contador;
       cout << "yolo4" <<endl;
    }

    return grafoaux.ejes();
}





vector <int> grasp(grafo g, int& maxfrontera){
    vector <int> listaNodos = g.ejes();
    int indiceNodoElegido = rand() % (listaNodos.size());
    int nodoElegido = listaNodos[indiceNodoElegido];
    maxfrontera = g.degree(nodoElegido);
    vector <int> nodosDisponibles = g.get_neigh(nodoElegido);
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(nodoElegido);
    aux.resize(nodoElegido + 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    vector<int> nodosDisponiblesAux;
    grafo grafoActualAux = grafoActual;
    cout << "yolo" <<endl;
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
    vector<vector<int> > basura;
     
     int j = 0;
     vector<int> paraElGrafo = busquedalocal(grafoActual,g,j);
    //cout << "yolo2" <<endl;
    grafoActualAux = grafo(paraElGrafo);
     //cout << "yolo3" <<endl;
    return grafoActual.ejes();
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