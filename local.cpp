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

vector<int> actualizar(grafo g ,vector<int> nodosUsados){
    vector<int> res;
    if (nodosUsados.size() == 1){
        //cout << "actualizar1" << endl;
        res = g.get_neigh(nodosUsados[0]);
    }
    else
    {   
        //cout << "actualizar2" << endl;
        if(nodosUsados.size() == 0){
            res = g.ejes();
        }
        else
        {   
            //cout << "actualizar3" << endl;
            res = g.get_neigh(nodosUsados[0]);
            int i = 1;
            while(i < nodosUsados.size()){
               //cout << "actualizar3-2" << endl;
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
	/*while (fin == false ){
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

	}*/
        while (fin == false ){
        //cout << "deberia terminar?:" ;
        //cout << fin << endl;
        //cout << "llegue4"<< endl;
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
        if (mayorCreciente > maxfrontera and mayorCreciente >= mayorDecreciente){
              //  cout << "llegue5a"<< endl;
            grafoaux.add_to_clique(nodosDisponibles.at(nodomayorCreciente));
            maxfrontera = mayorCreciente;
            nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));        
        }
        else if (mayorDecreciente > maxfrontera) {
               // cout << "llegue5b"<< endl;     
                grafoaux.del_from_clique(nodomayorDecreciente);
               // cout << "llegue5b"<< endl;       
                maxfrontera = mayorDecreciente;
                nodosDisponibles =actualizar(g,grafoaux.ejes());
               //  cout << "llegue5b3"<< endl;      
        }
        else
        {
           // cout << "llegue5c"<< endl;
            fin = true;
            // cout << "llegue5c"<< endl;
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
    //cout << "yolo" <<endl;
    //cout << "tamaño de la frontera es:";
    cout << maxfrontera << " " ;
    //cout << "cantidad de nodos es:";
    cout << res.size() << " ";
    //cout << "los nodos son:";
    mostrar(res);
    //cout << "" <<endl;
    
    return 0;
}