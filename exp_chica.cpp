#include <numeric>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <ostream>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <sstream>
#include "coloreo.h"

#define ya chrono::high_resolution_clock::now



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



bool esta(int v, vector<int>& nodos){    
    for(int i = 0; i < nodos.size(); i++){
        if(nodos[i] == v){
            return true;
        }
    }
    return false;
}


bool escliche(grafo&g, vector<int>& nodos){
    for(int i =0; i < nodos.size(); i++){
        if(g.get_neigh(nodos[i]).size() < nodos.size()-1){
            return false;
        }else{
            for(int j = 0; j < nodos.size(); j++ ){
                if( (nodos[j] != nodos[i]) and (esta(nodos[j], g.get_neigh(nodos[i])) == false)){
                    return false;
                }
            }
        }
    }
    
    return true;
}

int frontera_exacta(grafo&g, vector<int>& nodos){
    int res = 0;
    int vertices = g.n();

    for(int j =0; j< nodos.size(); j++ ){
        for(int i =1; i < vertices+1; i++){        
         if(((esta(i, g.get_neigh(nodos[j]))== true) and (esta(i, nodos) == false)) and(i != nodos[j])){ 
             res++;
         } 
        }
    }
    return res; 

}



vector<vector <int> > Conjunto_de_partes(int n){
    vector<vector<int > > res;
    int repeticiones  =( 1 << n);
    for(int i = 0; i < repeticiones ; i++){
        vector<int> parte_enesima;
        int auxiliar = i;
        for(int j  = n-1; j >= 0; j--){
            if(auxiliar >= (1<<j)){               
                parte_enesima.push_back(j+1);
                auxiliar = auxiliar -(1 << j); 
            }
        }
        if(!parte_enesima.empty()){             
            res.push_back(parte_enesima);
        }
    }
    return res;
}








vector<int> frontera_maxima(grafo& g, int& maxfrontier){
    int nodos = g.n();//me da todos los nodos.
    vector<vector<int> > partes = Conjunto_de_partes(nodos);
    //int maxima_frontera = 0;
    vector<int> res;
    for(int i = 0; i < partes.size(); i++ ){       
        if((escliche(g, partes[i])) and (frontera_exacta(g, partes[i]) >= maxfrontier)){ 
       // cout << "llegue" << i <<endl;       
            maxfrontier = frontera_exacta(g, partes[i]);
            res = partes[i];
        }
    }
return res;
//La idea es esta. Veo las partes del grafo, y luego por cada parte veo si es cliche. Y luego por cada cliche veo su frontera y me quedo con la maxima.
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
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(maximoNodo);
    aux.resize(maximoNodo + 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;    
    while (nodosDisponibles.size() > 0 ){
        int i = 0;
        int maximoGrado = 0;
        while(i < nodosDisponibles.size()){            
            if ((g.degree(nodosDisponibles.at(i)) > maximoGrado) and (not (esta1(grafoActual.ejes(),nodosDisponibles.at(i))))){
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
    //mostrar(mejorClique.ejes());
    return mejorClique.ejes();
}


grafo constructiva_con_random(grafo g, int& maxfrontera){
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
    //grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);//genero un grafo vacio con maximo + 1 posiciones. 
    int nodoAAgregar;
    vector<int> nodosDisponiblesAux;
    grafo grafoActualAux = grafoActual;   
    //int j = 0; 
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
        float porcentaje;
        
        //cout << nodosDisponibles.size() << endl; 
        //cout << floor(4/10) << endl;
        porcentaje = floor((nodosDisponibles.size()/10)*3);
        if(porcentaje == 0){
        porcentaje = 1;    
        }        
        for(float i = 0; i < porcentaje; i++){
            elecciones.push_back(fronteras[i]);
        }
        srand(time(NULL));        
        int indice = rand() % elecciones.size();
        //cout << indice << endl;
        if(get<0>(elecciones[indice]) >= maxfrontera){
            nodosDisponiblesAux = interseccion(nodosDisponibles,g.get_neigh(nodosDisponibles[get<1>(elecciones[indice])]));//los vecimos son los que estan en disponibles aux
            grafoActualAux = grafoActual;
            copia.add_to_clique(nodosDisponibles[get<1>(elecciones[indice])]);
           // cout << "llega" << endl;
            maxfrontera = get<0>(elecciones[indice]);//actualizo la frontera            
            grafoActualAux = copia;//actualizo el grafoaux
            copia.del_special();
        }        
        if(nodosDisponibles.size() == nodosDisponiblesAux.size()){
            break;
        }
        //cout << "llega" << endl;
        grafoActual = grafoActualAux;
        nodosDisponibles = nodosDisponiblesAux;
        //j++;
        //cout << "iteracion"<< j << endl;
        }
    return grafoActual;
}






int main(){

	int exacto;	
	//constexpr rep tiempo_exacto;
	int greedy_no_ad;
	//constexpr rep tiempo_greedy_no_ad;
	int greedy_ad;
	//constexpr rep tiempo_greedy_ad;
	int local;
	//constexpr rep tiempo_local;
	int grasp;
	//constexpr rep tiempo_grasp;

	cout << "exacto, tiempo_e, greedy_no_ad, tiempo_gna, greedy_ad, tiempo_ga\n";//, no_greedy, tiempo_ng, local, tiempo_local, grasp, tiempo_grasp\n";*/
	while(true){
		int cantNodos;			
		int cantAristas;
		cin >> cantNodos >> cantAristas;
		if((cantNodos == -1) and (cantAristas == -1)){
			break;
		}
		vector< vector <int> > listaAdyacencia = levantarAristas(cantNodos,cantAristas);    	
   		grafo g(listaAdyacencia);
   		int maxfrontier = 0;
   		auto start = ya();  
   		vector <int> reso = frontera_maxima(g, maxfrontier);  
    	auto end = ya();
    	exacto = (maxfrontier);
    	//tiempo_exacto = (chrono::duration_cast<chrono::nanoseconds>(end-start).count()); 
    	cout << exacto << ";" << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << ";";
    	maxfrontier = 0;
    	auto start2 = ya();        
    	reso = constructiva(g,maxfrontier);
    	auto end2 =  ya();
    	greedy_no_ad = (maxfrontier);
    	//tiempo_greedy_no_ad = (chrono::duration_cast<chrono::nanoseconds>(end2-start2).count());
    	cout << greedy_no_ad << ";" <<  chrono::duration_cast<chrono::nanoseconds>(end2-start2).count() << ";";
    	maxfrontier = 0;
    	auto start3 = ya();
    	grafo res = constructiva_con_random(g,maxfrontier);
    	auto end3 =  ya();
    	greedy_ad = (maxfrontier);
    	//tiempo_greedy_ad = (chrono::duration_cast<chrono::nanoseconds>(end3-start3).count());
    	cout << greedy_ad << ";" << chrono::duration_cast<chrono::nanoseconds>(end3-start3).count() << endl;    	
    	//maxfrontier = 0;
    	//auto start5 = ya();
    	//res = busquedalocal(g,maxfrontier);
    	//auto end5 =  ya();
    	//local =(maxfrontier);
    	//tiempo_local = (chrono::duration_cast<chrono::nanoseconds>(end5-start5).count());
    	//cout << local << ";" << chrono::duration_cast<chrono::nanoseconds>(end5-start5).count() << ";";
    	//maxfrontier = 0;
    	//auto start6 = ya();        
    	//res = grasp_1(g,maxfrontier);
    	//auto end6 =  ya();
    	//grasp = maxfrontier;
    	//tiempo_grasp = (chrono::duration_cast<chrono::nanoseconds>(end6-start6).count());
    	//cout << grasp << ";" << chrono::duration_cast<chrono::nanoseconds>(end6-start6).count() << ";";
    	
	}    

       
	return 0;
}


