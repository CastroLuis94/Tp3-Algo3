#include <iostream>
#include <ostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
#include "coloreo.h"
#include <tuple>


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

grafo busquedalocal(grafo g, int& maxfrontera, grafo& construido){
    //cout << "llegue2"<< endl;
    if(construido.ejes().size()>0){
        vector <int> nodosDisponibles = g.get_neigh(construido.ejes()[0]);
    //esto lo saque yo
    for (int i = 0; i < construido.ejes().size(); ++i)
    {
        nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(construido.ejes()[i]));
     //   mostrar(nodosDisponibles);
    //esto no da siempre vacio??
    }
    //hasta aca
        int nodoAAgregar;

       //cout << "llegue3"<< endl;
        int mayorCreciente = 0;
        int nodomayorCreciente = 0;
        int cont = 0;
        grafo grafoaux = construido;
        int mayorDecreciente = 0;
        int nodomayorDecreciente = 0;
        grafoaux = construido;
        bool fin = false;
        int nodoAeliminar;
        //cout << "nodos antes de hacer nada:";
        //mostrar(construido.ejes());
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
      // cout << "termine local con grafoaux" << endl;
    return grafoaux;
    }else
    {
      // cout << "termine local con construido" << endl;
    return construido;
    }
}



grafo constructiva_con_random(grafo g,int nodoElegido ,int& maxfrontera){
   
    int recorredor = 0;
    int mejorFrontera = 0;
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


vector<int> grasp(grafo g, int& maximaFrontera){
    srand(time(NULL)); 
    vector <int> listaNodos = g.ejes();
    vector <int> primerosNodos;
    vector <vector <int> > basura;
    vector <int> basura1;
    grafo res(basura,basura1);
    while(primerosNodos.size() < ( ( g.ejes().size() ) * 2) ){
        primerosNodos.push_back(listaNodos.at(rand() % (listaNodos.size())));
    }

    int indice = 0;
    while(indice < primerosNodos.size()){        
        int maxfronteraAux = 0;
        int primerNodo = primerosNodos[indice];
        grafo conLaConstructiva = constructiva_con_random(g,primerNodo,maxfronteraAux);
        int maxfronteraAux2 = 0;

        /*
        Parte  local .*/
        grafo conElLocal = busquedalocal(g,maxfronteraAux,conLaConstructiva);
        if (maxfronteraAux >= maximaFrontera ){
            maximaFrontera = maxfronteraAux;
            res = conElLocal;
            //cout << "grasp1a" << endl;
        }
        indice++;
    }
    return res.ejes();

}


int main(){

 
    
    int vertices;
    cin >> vertices;
    int aristas;
    cin >> aristas;
    
    vector< vector <int> > listaAdyacencia = levantarAristas(vertices,aristas);
    //mostrar(listaAdyacencia);
    int maxfrontera = 0;
    grafo g(listaAdyacencia);    
   // vector <int> listaNodos = g.ejes();
    //cout << "LLEGA" << endl;
    //int nodoElegido = listaNodos.at(rand() % (listaNodos.size()));

    //grafo r = constructiva_con_random(g,nodoElegido ,maxfrontera); 
    
  //  vector<int> res = busquedalocal(g, maxfrontera, r);    
 
    //cout << "yolo" <<endl;
    //cout << "llegue"<< endl;
    vector <int> res = grasp(g,maxfrontera);
    //cout << "yolo2" <<endl;
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << res.size() << " ";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}
