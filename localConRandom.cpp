#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>

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
    	//cout << "cant es:";
    	//cout << nodosDisponibles.size() << endl;
    	while(cont < nodosDisponibles.size()) {
    		if(not esta1(grafoActual.ejes(),nodosDisponibles.at(cont))){
    			nodoAAgregar = nodosDisponibles.at(cont);
    			//cout << "llegue" << endl;
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
	//cout << "tamaño grafo actual es:";
	//cout << grafoActual.tamano() << endl;
	//mostrar(grafoActual.ejes());
	grafoaux = grafoActual;
	bool fin = false;
	int nodoAeliminar;
	while (fin == false ){
		//cout << "yolo0" << endl;
		mayorDecreciente = 0;
    	mayorCreciente = 0;
    	while (cont < nodosDisponibles.size()){
    		grafoaux.add_to_clique(nodosDisponibles.at(cont));
    		if(frontera(grafoaux,g) > mayorCreciente){
    			mayorCreciente = frontera(grafoaux,g);
    			nodomayorCreciente = cont;
		//		cout << "yolo1" << endl;
    		}
    		grafoaux.del_from_clique(nodosDisponibles.at(cont));
    		cont ++;
		}
		cont = 0;
		while (cont < grafoaux.tamano()) {
		//	cout << "entre a disminuir" << endl;
			//cout << grafoaux.tamano() << endl;
			//cout << cont << endl;
			nodoAeliminar = grafoaux.ejes()[0];
		//	cout << "cantidad ejes original:" ;
		//	mostrar(grafoaux.ejes());
        //   cout << "grados:";
		//	cout << grafoaux.degrees() << endl;
        //    vector <int> testeo2 = grafoaux.get_neigh(nodoAeliminar);
        //    cout << "vecinos de eliminar son:";
        //    mostrar(testeo2);
            //mostrar(grafoaux.ejes()[0].get_neigh());
			grafoaux.del_from_clique(nodoAeliminar);
		//	cout << "desp de borrar:" ;
		//	mostrar(grafoaux.ejes());
        //    cout << "grados:";
		//	cout << grafoaux.degrees() << endl;
		//	cout << frontera(grafoaux,g) << endl;
			if (frontera(grafoaux,g) > mayorDecreciente){
				mayorDecreciente = frontera(grafoaux,g);
				nodomayorDecreciente = nodoAeliminar;
		//		cout << "yolo2" << endl;
			}
			grafoaux.add_to_clique(nodoAeliminar);
        //    testeo2 = grafoaux.get_neigh(nodoAeliminar);
        //    cout << "vecinos del eliminado son:";
        //    mostrar(testeo2);
			cont ++;
		}
		if (mayorCreciente >= maxfrontera and mayorCreciente >= mayorDecreciente){
			grafoaux.add_to_clique(nodosDisponibles.at(nodomayorCreciente));
			maxfrontera = mayorCreciente;
		//	cout << "creci" << endl;
		}
		else if (mayorDecreciente >= maxfrontera) {
				//mostrar(grafoaux.ejes());
				grafoaux.del_from_clique(nodomayorDecreciente);
				//cout << nodomayorDecreciente << endl;
				//mostrar(grafoaux.ejes());
				maxfrontera = mayorDecreciente;
		//		cout << "me achique" << endl;
		}
		else {

			fin = true;
		//	cout << "termine" << endl;
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
    //mostrar(listaAdyacencia);
    grafo g(listaAdyacencia);

    
    //mostrar(Conjunto_de_partes());
    int maxfrontera = 0;


    vector <int> res = busquedalocal(g,maxfrontera);
    cout << "yolo" <<endl;
    cout << "tamaño de la frontera es:";
    cout << maxfrontera << " " << endl;
    cout << "cantidad de nodos es:";
    cout << res.size() << " " <<endl;
    cout << "los nodos son:";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}