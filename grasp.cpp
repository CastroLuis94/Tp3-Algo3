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
        res = g.get_neigh(nodosUsados[0]);
    }
    else
    {
        if(nodosUsados.size() == 0){
            res = g.ejes();
        }
        else
        {
            res = g.get_neigh(nodosUsados[0]);
            int i = 1;
            while(i < nodosUsados.size()){
                res = interseccion(res,g.get_neigh(nodosUsados[i]));
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

vector <int> busquedalocal(grafo g, int& maxfrontera, grafo construido){
    //vector <int> listaNodos = g.ejes();
    //int indiceprimerNodo = rand() % (listaNodos.size());
    //int primerNodo = listaNodos[indiceprimerNodo];
    //int Crecimiento = 0;
    vector <int> nodosDisponibles = g.get_neigh(construido.ejes()[0]);
    for (int i = 0; i < construido.ejes().size(); ++i)
    {
        nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(construido.ejes()[i]));
    }
    //vector <vector < int > > aux;
    //vector <int> nodos;
    //**nodos.push_back(primerNodo);
    //aux.resize(primerNodo+ 1);
    //grafo mejorClique(aux,nodos);
    //grafo grafoActual(aux,nodos);
    int nodoAAgregar;
    /*while(Crecimiento < listaNodos.size()/2 and nodosDisponibles.size() > 0){
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
    */int mayorCreciente = 0;
    int nodomayorCreciente = 0;
    int cont = 0;
    grafo grafoaux = construido;
    int mayorDecreciente = 0;
    int nodomayorDecreciente = 0;
    //cout << "tamaño grafo actual es:";
    //cout << grafoActual.tamano() << endl;
    //mostrar(grafoActual.ejes());
    grafoaux = construido;
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
        //      cout << "yolo1" << endl;
            }
            grafoaux.del_from_clique(nodosDisponibles.at(cont));
            cont ++;
        }
        cont = 0;
        while (cont < grafoaux.tamano()) {
        //  cout << "entre a disminuir" << endl;
            //cout << grafoaux.tamano() << endl;
            //cout << cont << endl;
            nodoAeliminar = grafoaux.ejes()[0];
        //  cout << "cantidad ejes original:" ;
        //  mostrar(grafoaux.ejes());
        //   cout << "grados:";
        //  cout << grafoaux.degrees() << endl;
        //    vector <int> testeo2 = grafoaux.get_neigh(nodoAeliminar);
        //    cout << "vecinos de eliminar son:";
        //    mostrar(testeo2);
            //mostrar(grafoaux.ejes()[0].get_neigh());
            grafoaux.del_from_clique(nodoAeliminar);
        //  cout << "desp de borrar:" ;
        //  mostrar(grafoaux.ejes());
        //    cout << "grados:";
        //  cout << grafoaux.degrees() << endl;
        //  cout << frontera(grafoaux,g) << endl;
            if (frontera(grafoaux,g) > mayorDecreciente){
                mayorDecreciente = frontera(grafoaux,g);
                nodomayorDecreciente = nodoAeliminar;
        //      cout << "yolo2" << endl;
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
            nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));
        //  cout << "creci" << endl;
        }
        else if (mayorDecreciente >= maxfrontera) {
                //mostrar(grafoaux.ejes());
                grafoaux.del_from_clique(nodomayorDecreciente);
                //cout << nodomayorDecreciente << endl;
                //mostrar(grafoaux.ejes());
                maxfrontera = mayorDecreciente;
                nodosDisponibles =actualizar(g,grafoaux.ejes());

        //      cout << "me achique" << endl;
        }
        else {

            fin = true;
        //  cout << "termine" << endl;
        }

    }
    return grafoaux.ejes();
}

grafo constructiva_con_random(grafo g, int& maxfrontera){
    srand(time(NULL)); 
    vector <int> listaNodos = g.ejes();
    vector <int> primerosNodos;
    while(primerosNodos.size() < ( ( g.ejes().size() ) * 2) ){
        primerosNodos.push_back(listaNodos[rand() % (listaNodos.size()+1)]);
    }
    int recorredor = 0;
    int nodoElegido;
    int mejorFrontera;
    vector <vector < int > > basura;
    vector <int> basura1;
    grafo cliqueResultado(basura,basura1);
    while(recorredor < primerosNodos.size()){
        nodoElegido = primerosNodos[recorredor];
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
        recorredor++;
        if(maxfrontera > mejorFrontera){
            mejorFrontera = maxfrontera;
            cliqueResultado = grafoActual;
        }
    }
    return cliqueResultado;
}

/*vector <int> grasp(grafo g, int& maxfrontera){
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
        
        if (maxfrontera < frontera(grafoActual,g)){
            mejorClique = grafoActual;
            maxfrontera = frontera(grafoActual,g);
        }
        nodosDisponibles = interseccion(nodosDisponibles,g.get_neigh(nodoAAgregar));
    }
    return mejorClique.ejes();
}
*/


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
    cout << "yolo" <<endl;
    grafo res2 = constructiva_con_random(g,maxfrontera);
    cout << "yolo1" <<endl;
    vector <int> res = busquedalocal(g,maxfrontera,res2);
    cout << "yolo2" <<endl;
    //cout << "yolo" <<endl;
    cout << maxfrontera << " ";
    cout << res.size() << " ";
    mostrar(res);
    cout << "" <<endl;
    
    return 0;
}
