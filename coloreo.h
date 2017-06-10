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
	grafo(vector< vector<int> >& vs){
		vecinos = vs;
	}
	void add_edge(int v1, int v2);
	vector<int>& get_neigh(int v);
	int n();
	void print();
	// nodos ordenados por grado
	vector<int> nodes_by_degree();
private:
	vector< vector<int> > vecinos;
};



//grafo crear_grafo();

#endif