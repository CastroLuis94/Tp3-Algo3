#ifndef COLOREOAED3
#define COLOREOAED3 

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;



class grafo {
public:
	grafo(vector< vector<int> >& vs);
	grafo(vector<int> vs);
	grafo(const grafo& g, vector<int> nodos){
		vecinos = g.vecinos;
		axis = nodos;
	}
	grafo(vector<vector<int> > neigh, vector<int> nodos){
		vecinos = neigh;
		axis = nodos;
	}
	grafo& operator=(const grafo& other){
		vecinos = other.vecinos;
		axis = other.axis;
	}
	int degrees();
	void add_edge(int v1, int v2);
	void add_axis(int v1);
	vector <int> ejes();
	vector<int>& get_neigh(int v);
	int n();
	void print();
	int tamano();
	// nodos ordenados por grado
	vector<int> nodes_by_degree();
	int degree(int nodo);
	void add_to_clique(int v1);
	void add_edge_to_clique(int v1, int v2);
	void add_to_grafo(int v1);
	void del_from_clique(int v1);
	void del_special();
private:
	vector< vector<int> > vecinos;
	vector <int> axis;
};



//grafo crear_grafo();

#endif