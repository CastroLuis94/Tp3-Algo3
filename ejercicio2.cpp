#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>

#include "coloreo.h"//grafo representado como lista de adyacencias.
/*
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
    if((frontera(maximales[i], g) > maxfrontier) or  maximasubchicle(maximales[i], g).size() > maxfrontier ){
        if( ( maximasubchicle(maximales[i], g).size()) > frontera(maximales[i], g) ){
        maxfrontier =  maximasubchicle(maximales[i], g).size();
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

*/

//Me niego a hacer algo tan negro.

bool esta(int v, vector<int>& nodos){    
    for(int i = 0; i < nodos.size(); i++){
        if(nodos[i] == v){
            return true;
        }
    }
    return false;
}

bool escliche(grafo&g, vector<int>& nodos){	//dado un conjunto de nodos, me dice si son clique	
    for(int i =0; i < nodos.size(); i++ ){
        if(g.get_neigh(nodos[i]).size() < nodos.size()-1){
            return false;
        }
    }
    return true;
}



int frontera(grafo&g, vector<int>& nodos){
    int res = 0;
    int vertices = g.n();
    for(int i =0; i < vertices; i++){
        if(! esta(i, nodos)){
            res++;
        } 
    } 

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
            //cout << "i : " << i << "j :" << j<< endl;                      
            //if(((auxiliar % (1 << j)) == 0) and (auxiliar > 0) and ((auxiliar == i) or ((auxiliar< i) and (auxiliar > 1) )) ){
            
            if(auxiliar >= (1<<j)){  
            //cout <<"paso"<< "i : " << i << "j :" << j<< endl;              
                parte_enesima.push_back(j+1);
                auxiliar = auxiliar -(1 << j); 
            }
        }
        if(!parte_enesima.empty()){             
            res.push_back(parte_enesima);
        }
    }
    vector<int> vacio;
    res.push_back(vacio);
    return res;
}








vector<int> frontera_maxima(grafo& g, int& maxfrontier){
    int nodos = g.n();//me da todos los nodos.
    vector<vector<int> > partes = Conjunto_de_partes(nodos);
    int maxima_frontera = 0;
    vector<int> res;
    for(int i = 0; i < partes.size(); i++ ){
        if((escliche(g, partes[i])) and (frontera(g, partes[i]) > maxima_frontera)){
            maxima_frontera = frontera(g, partes[i]);
            res = partes[i];
        }
    }
return res;
//La idea es esta. Veo las partes del grafo, y luego por cada parte veo si es cliche. Y luego por cada cliche veo su frontera y me quedo con la maxima.
}

void mostrar(vector<int> vs){
    cout << "[";
    int i = 0;
    while(i < vs.size()){
        cout << vs[i];
        i++;
        if(i < vs.size()){
            cout << ",";
        }
    }
    cout << "]" <<endl;
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







int main(){
   // vector<vector <int> > res = Conjunto_de_partes(4);
   // mostrar(res);

    int instancias;
    cin >> instancias;
    for(int i=0; i < instancias; i++){        
        grafo g = crear_grafo();
        //Ahora deberia resolver el problema
        int maxfrontier = 0;
        cout<<  maxfrontier << frontera_maxima(g, maxfrontier).size() << endl;
        for(int j = 0; j< frontera_maxima(g, maxfrontier).size(); j++){
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