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

void mostrar(vector<int> vs){
    int i = 0;
    while(i < vs.size()){
        cout << vs[i] << " ";
        i++;
        /*if(i < vs.size()){
            cout << ",";
        }*/
    }
    cout << "" <<endl;
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

int frontera1(grafo&g, vector<int>& nodos){
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
    for(int i = 0; i < (1 << n) ; i++){
        vector<int> parte_enesima;
        int auxiliar = i;
        /*if((auxiliar%2) == 1){
            parte_enesima.push_back(1);
            auxiliar--;
        }*/ //Ahora son todos pares.
        for(int j  = n-1; j >= 0; j--){//puede ser que deba ser modificado           
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
        if((escliche(g, partes[i])) and (frontera1(g, partes[i]) >= maxfrontier)){ 
       // cout << "llegue" << i <<endl;       
            maxfrontier = frontera1(g, partes[i]);
            res = partes[i];
        }
    }
return res;
//La idea es esta. Veo las partes del grafo, y luego por cada parte veo si es cliche. Y luego por cada cliche veo su frontera y me quedo con la maxima.
}

vector<int> constructiva_no_greedy(grafo& g, int& maxfrontier){
    vector <int> listaNodos = g.ejes();
    int indiceprimerNodo = rand() % (listaNodos.size());
    int primerNodo = listaNodos[indiceprimerNodo];
    int Crecimiento = 0;
    vector <int> nodosDisponibles = g.get_neigh(primerNodo);
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(primerNodo);
    aux.resize(primerNodo+ 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    while(Crecimiento < listaNodos.size()/2 and nodosDisponibles.size() > 0){
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
    maxfrontier = frontera(grafoActual,g);
    return mejorClique.ejes();
}








vector <int> busquedalocal(grafo g, int& maxfrontera){
	vector <int> listaNodos = g.ejes();
    int indiceprimerNodo = rand() % (listaNodos.size());
    int primerNodo = listaNodos[indiceprimerNodo];
    int Crecimiento = 0;
    vector <int> nodosDisponibles = g.get_neigh(primerNodo);
    vector <vector < int > > aux;
    vector <int> nodos;
    nodos.push_back(primerNodo);
    aux.resize(primerNodo+ 1);
    grafo mejorClique(aux,nodos);
    grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    while(Crecimiento < listaNodos.size()/2 and nodosDisponibles.size() > 0){
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
    int mayorCreciente = 0;
    int nodomayorCreciente = 0;
    int cont = 0;
    grafo grafoaux(aux,grafoActual.ejes());
    int mayorDecreciente = 0;
	int nodomayorDecreciente = 0;
	grafoaux = grafoActual;
	bool fin = false;
	int nodoAeliminar;
	while (fin == false ){		
		mayorDecreciente = 0;
    	mayorCreciente = 0;
    	while (cont < nodosDisponibles.size()){
    		grafoaux.add_to_clique(nodosDisponibles.at(cont));
    		if(frontera(grafoaux,g) > mayorCreciente){
    			mayorCreciente = frontera(grafoaux,g);
    			nodomayorCreciente = cont;		
    		}
    		grafoaux.del_from_clique(nodosDisponibles.at(cont));
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
		if (mayorCreciente >= maxfrontera and mayorCreciente >= mayorDecreciente){
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

	}
	return grafoaux.ejes();
}






grafo constructiva_adaptativa(grafo g, int& maxfrontera){
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
}





int main(){

	vector<int> exacto;	
	vector<int> tiempo_exacto;
	vector<int> greedy_no_ad;
	vector<int> tiempo_greedy_no_ad;
	vector<int> greedy_ad;
	vector<int> tiempo_greedy_ad;
	vector<int> no_greedy;
	vector<int> tiempo_no_greedy;
	vector<int> local;
	vector<int> tiempo_local;
	vector<int> grasp;
	vector<int> tiempo_grasp;

	cout << "exacto, tiempo_e, greedy_no_ad, tiempo_gna, greedy_ad, tiempo_ga, no_greedy, tiempo_ng, local, tiempo_local, grasp, tiempo_grasp\n";
	while(true){
		int cantNodos;			
		int cantAristas;
		cin << cantNodos << cantAristas;
		if((cantNodos == -1) and (cantAristas == -1)){
			break;
		}
		vector< vector <int> > listaAdyacencia = levantarAristas(vertices,aristas);    	
   		grafo g(listaAdyacencia);
   		int maxfrontier = 0;
   		auto start = ya();  
   		vector <int> res = frontera_maxima(g, maxfrontier);  
    	auto end = ya();
    	exacto.push_back(maxfrontier);
    	tiempo_exacto.push_back(chrono::duration_cast<chrono::nanoseconds>(end-start).count()); 
    	maxfrontier = 0;
    	auto start2 = ya();
    	grafo res = constructiva(g,maxfrontier);
    	auto end2 =  ya();
    	greedy_no_ad.push_back(maxfrontier);
    	tiempo_greedy_no_ad.push_back(chrono::duration_cast<chrono::nanoseconds>(end2-start2).count());
    	maxfrontier = 0;
    	auto start3 = ya();
    	grafo res = constructiva_adaptativa(g,maxfrontier);
    	auto end3 =  ya();
    	greedy_ad.push_back(maxfrontier);
    	tiempo_greedy_ad.push_back(chrono::duration_cast<chrono::nanoseconds>(end3-start3).count());
    	maxfrontier = 0;
    	auto start4 = ya();
    	grafo res = constructiva_no_greedy(g,maxfrontier);
    	auto end4 =  ya();
    	no_greedy.push_back(maxfrontier);
    	tiempo_no_greedy.push_back(chrono::duration_cast<chrono::nanoseconds>(end4-start4).count());
    	maxfrontier = 0;
    	auto start5 = ya();
    	grafo res = busquedalocal(g,maxfrontier);
    	auto end5 =  ya();
    	local.push_back(maxfrontier);
    	tiempo_local.push_back(chrono::duration_cast<chrono::nanoseconds>(end5-start5).count());
    	maxfrontier = 0;
    	auto start6 = ya();
    	grafo res = grasp(g,maxfrontier);
    	auto end6 =  ya();
    	grasp.push_back(maxfrontier);
    	tiempo_grasp.push_back(chrono::duration_cast<chrono::nanoseconds>(end6-start6).count());
    	 
	}
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < exacto.size()){
        cout << exacto[i];
        i++;
        if(i < exacto.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;

    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_exacto.size()){
        cout << tiempo_exacto[i];
        i++;
        if(i < tiempo_exacto.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;

    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < greedy_no_ad.size()){
        cout << greedy_no_ad[i];
        i++;
        if(i < greedy_no_ad.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_greedy_no_ad.size()){
        cout << tiempo_greedy_no_ad[i];
        i++;
        if(i < tiempo_greedy_no_ad.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < greedy_ad.size()){
        cout << greedy_ad[i];
        i++;
        if(i < greedy_ad.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_greedy_ad.size()){
        cout << tiempo_greedy_ad[i];
        i++;
        if(i < tiempo_greedy_ad.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < no_greedy.size()){
        cout << no_greedy[i];
        i++;
        if(i < no_greedy.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_no_greedy.size()){
        cout << tiempo_no_greedy[i];
        i++;
        if(i < tiempo_no_greedy.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < local.size()){
        cout << local[i];
        i++;
        if(i < local.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
   cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_local.size()){
        cout << tiempo_local[i];
        i++;
        if(i < tiempo_local.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
   cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < grasp.size()){
        cout << grasp[i];
        i++;
        if(i < grasp.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
   cout << "res = ";
    cout << "[";
    int i = 0;    
    while(i < tiempo_grasp.size()){
        cout << tiempo_grasp[i];
        i++;
        if(i < tiempo_grasp.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
    






    salida.close();          
    return 0;    

       
	return 0;
}