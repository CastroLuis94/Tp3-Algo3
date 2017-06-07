#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>

#include "coloreo.h"//grafo representado como lista de adyacencias.

void BronKerboch(vector<int>& P, vector<int>& R, vector<int>& X, vector<vector<int> >& maximales, grafo& g){    
    if( P.empty() and X.empty()){
        maximales.push_back(R);
    }
    vector<int>::iterator it;         
    for(it = P.begin(); it != P.end(); it++){
        BronKerboch( interseccion(P, g.get_neigh((*it))), Union(R, (*it)), interseccion(X, g.get_neigh(*it)));
        X.push_back((*it));
        sacar(P , (*it));
    }
}

int frontera(vector<int> &cliche, grafo& g ){
    //cliche.sort();
    //sort(cliche);
    vector<int> vecinos;
    for(int i = 0; i < cliche.size(); i++){    
    vector<int> vecinos_local =  g.get_neigh(cliche[i]);
        for(int j = 0; j < vecinos_local.size(); j++){
            vecinos.push_back(vecinos_local[j]);
        }
    }
    return vecinos.size() - interseccion(cliche, vecinos).size();
}


vector<int> maximasubchicle(vector<int>& cliche, grafo& g){
    vector<int> res;
    int resultado;
    for(int i = 0; i< cliche.size(); i++){
        vector<int> subcliche = cliche;
        subcliche.erase(subcliche.begin()+ i);
        if(frontera(subcliche, g) > resultado){
            res = subcliche;
        }
    }
    return res;

}


vector<int> frontera_maxima(grafo& g, int& maxfrontier){//res = nodos de la chicle de maxima frontera
 vector<int> P = g.nodes_by_degree();
 vector<int> R;
 vector<int> X;
 vector<vector <int> > maximales;

 vector<vector <int> >::iterator itmax;
 BronKerboch(P, R, X, maximales, g);//ahora en maximales tenemos todas las maximales:
 
 int cliquesize = 0;
 vector<int> res;
 for(int i =0; i < maximales.size(); i++){
    if((frontera(maximales[i], g) > maxfrontier) or /*maximales[i].size()-1 +*/ maximasubchicle(maximales[i], g).size() > maxfrontier ){
        if( (/*maximales[i].size()-1 +*/ maximasubchicle(maximales[i], g).size()) > frontera(maximales[i], g) ){
        maxfrontier = /*maximales[i].size() - 1*/ + maximasubchicle(maximales[i], g).size();
        cliquesize = (maximales[i]).size() -1;
        res = (maximasubchicle(maximales[i], g));
        }else{
        maxfrontier = frontera(maximales[i], g);
        cliquesize = maximales[i].size();
        res = (maximales[i]);
        }     
    }
 }
 return (res);
}



//Me niego a hacer algo tan negro.
void sacar(vector<int>& P, it){
    for(int i =0; i< P.size(); i++){}

}


/*
BronKerbosch3(G)://Vamos por el BronKerboch3
       P = V(G)
       R = X = empty
       for each vertex v in a degeneracy ordering of G:
           BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
           P := P \ {v}
           X := X ⋃ {v}


vector<set<int> >  BronKerbosch2(R,P,X){
    vector<set<int> > res;
    if((empty(X)) and (empty(P))){
        res.push_back(R);
    }
    u = P[0];

    P = P - {v}
    X = X 
  }
       if P and X are both empty:
           report R as a maximal clique
       choose a pivot vertex u in P ⋃ X
       for each vertex v in P \ N(u):
           BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
           P := P \ {v}
           X := X ⋃ {v}
*/


//Vamos a probar usando fuerza bruta.(Complejidad horrible)
/*vector<int> frontera_maxima(grafo& g){
	vector<vector<int> > cliches;    
    for(int i =0; i < g.n(), i++){
    	vector<int> vecinos = g.get_neigh(i);
    	for(int j = 0; j < vecinos.size(); i++){//todos los de dos son cliches de n = 2.
    		vector<int> actual;
    		actual.push_back(i);
    		actual.push_back(vecinos[j]);
    		if(frontera(actual)> fronteramax){
    		cliches.push_back(actual); //me acumulo todas las cliches de dos con maxima frontera
    		}
    	}
    }
    int agregamos = 0;
    for(int j =0; j< cliches.size(); j++){
    	for(int l =0; l < g.get_neigh(cliques[j][0]).size(), l++){
    		for(int m = 1; m < cliques[j].size(); m++){
    			bool valido = true;	
    			if(!esta(g.get_neigh(cliques[j][0])[l]), g.get_neigh(cliques[j][m])){
    				valido = false;
    				break;
    			}
    			if(valido and frontera(cliques, ))
    		}
    	}

    	


    } 

}
*/
bool escliche(grafo&g, vector<int> nodos){	//dado un conjunto de nodos, me dice si son clique
	vector<int>  vecinos = g.get_neigh(nodos[0]);
	for(int i =0; i < vecinos.size(); i++ ){
		for(int j = 0; j < nodos.size(); j++){
			if(!esta(vecinos[i], g.get_neigh(nodos[j]))){
				return  false; 
			}
		}		
	}
	return true;
}



bool esta(int i, vector<int>& vect){
	for(int i = 0; i < vect.size(); i++ ){
		if()
	}
}

int main(){
    int instancias;
    cin >> instancias;
    for(int i=0; i < instancias; i++){        
        grafo g = crear_grafo();
        //Ahora deberia resolver el problema
        int maxfrontier = 0;
        cout<<  maxfrontier << frontera_maxima(g, maxfrontier).size() << endl;
        for(int i = 0; i< frontera_maxima(g, maxfrontier).size(); i++){
            cout << frontera_maxima(g, maxfrontier)[i] << endl;
        }
        //la respuesta esta en una maximal, o en una sub de la maximal.
        //Porque no podria ser en 3...porque si hay una de 4 con 

        //todos los teoricos estan mal, amigo.

        //pensemos, que pasa si yo enlisto las cliques maximales?

        //entonces, las fronteras las de estas o las de uno de sus sub cliques.
        //las subcliques van a tener a lo sumo 
   
        //deberia formar un tipo grafo con esto.

    }
  
    cout << "Fin de la ejecucion del algoritmo." << endl;
    return 0;
}