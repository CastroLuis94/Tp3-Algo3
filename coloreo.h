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
	grafo(const grafo& g, vector<int> nodos){
		vecinos = g.vecinos;
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
	// nodos ordenados por grado
	vector<int> nodes_by_degree();
	int degree(int nodo);
	void add_to_clique(int v1);
private:
	vector< vector<int> > vecinos;
	vector <int> axis;
};



//grafo crear_grafo();

#endif