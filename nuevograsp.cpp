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
//    int indiceprimerNodo = rand() % (listaNodos.size());
//    int primerNodo = listaNodos[indiceprimerNodo];
//    int Crecimiento = 0;
//    vector <int> nodosDisponibles = g.get_neigh(primerNodo);
    vector <int> nodosDisponibles:;
//    vector <vector < int > > aux;
    vector <int> nodos;
//    nodos.push_back(primerNodo);
//    aux.resize(primerNodo+ 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
/*    while(Crecimiento < listaNodos.size()/2 and nodosDisponibles.size() > 0){
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
*/  maxfrontera = frontera(original,g);
    int cont = 0;
    grafo grafoaux(aux,grafoActual.ejes());
    grafoaux = grafoActual;
    bool fin = false;
    bool flag = false;
    int nodoAeliminar;
    tuple <int, int, bool> aux2;
    vector< tuple< int, int,bool > > guardar;
    while (contador < g.tamano()*2){
        while (cont < nodosDisponibles.size()){
            flag = false
            grafoaux.add_to_clique(nodosDisponibles.at(cont));
            if (guardar.size() < 5){
                if(frontera(grafoaux,g) > maxfrontera){
                    aux2 = make_tuple(cont,frontera(grafoaux,g),true);
                    guardar.push_back(aux2);
                }
            }
            else
            {
                for (int i = 0; i < guardar.size() and flag = false ; ++i)
                {
                    if (frontera(grafoaux,g) > get<2>(guardar[i]) )
                    {
                        //aux2 = make_tuple(cont,frontera(grafoaux,g),true);
                        guardar[i].get<1> = cont;
                        guardar[i].get<2> = frontera(grafoaux,g);
                        guardar[i].get<1> = true;
                        flag = true;
                    }
                }
            }
            grafoaux.del_from_clique(nodosDisponibles.at(cont));
            cont ++;
        }
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
                for (int i = 0; i < guardar.size() and flag = false ; ++i)
                {
                    if (frontera(grafoaux,g) > get<2>(guardar[i]) )
                    {
                        //aux2 = make_tuple(nodoAeliminar,frontera(grafoaux,g),false);
                        //guardar.push_back(aux2);
                        guardar[i].get<1> = nodoAeliminar;
                        guardar[i].get<2> = frontera(grafoaux,g);
                        guardar[i].get<3> = false;
                        flag = true;
                    }
                }
            }
            grafoaux.add_to_clique(nodoAeliminar);
            cont ++;
        }

        aux2 = rand() % (guardar);


        if (get<3>(true))
        {
          grafoaux.add_to_clique(get<1>(aux2));
          maxfrontera = get<2>(aux2);  
        }
        ++contador
       /* if (mayorCreciente >= maxfrontera and mayorCreciente >= mayorDecreciente){
            grafoaux.add_to_clique(nodosDisponibles.at(nodomayorCreciente));
            maxfrontera = mayorCreciente;
        }
        else if (mayorDecreciente >= maxfrontera) {
                grafoaux.del_from_clique(nodomayorDecreciente);
                maxfrontera = mayorDecreciente;
        }
        else {

            fin = true;
        }
        */
    }

    return grafoaux.ejes();
}





vector <int> grasp(grafo g, int& maxfrontera){
    vector <int> listaNodos = g.ejes();
    int indiceNodoElegido = rand() % (listaNodos.size());
    int nodoElegido = listaNodos[indiceNodoElegido];
    maxfrontera = g.degree(nodoElegido);
    vector <int> nodosDisponibles = g.get_neigh(nodoElegido);
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
    nodos.push_back(nodoElegido);
    aux.resize(nodoElegido + 1);
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


    vector <int> res = grasp(g,maxfrontera);
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << res.size() << " ";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}