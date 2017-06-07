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
	grafo(int n) : vecinos(n, vector<int>()){};
	void add_edge(int v1, int v2);
	vector<int>& get_neigh(int v);
	int n();
	void print();
	// nodos ordenados por grado
	vector<int> nodes_by_degree();
private:
	vector< vector<int> > vecinos;
};

class coloreo {
public:
	coloreo(grafo& g) : g(g), n(g.n()), color(n) {
		iota(color.begin(), color.end(), 0);
	};
	coloreo(const coloreo& c) : g(c.g), n(c.n), color(c.color) {};
	coloreo(grafo& g, int c) : g(g), n(g.n()), color(n, c) {};

	bool is_valid();
	// el color de v es distinto al de sus vecinos
	bool color_factible(int v);
	int min_color_disponible(int v);
	int chi();
	// algoritmo de coloreo secuencia, en el orden de nodos_en_orden
	void colorear_secuencial(vector<int>& nodos_en_orden);
	// recolorear para usar colores desde 0, todos consecutivos
	void recolorear_consecutivos();
	void print();
	// el conjunto de nodos pintados de cada color
	vector<pair<int, vector<int> > > clases();
	// los vecinos de v de su mismo color
	set<int> nodos_conflictivos(int v);
	// todos los nodos que tienen algún vecino de su mismo color 
	set<int> nodos_conflictivos();
	// pintar con el color c todos los nodos de vs
	void asignar_color(vector<int> vs, int c);
	
	grafo& g;
	int n;
	vector<int> color;
};

grafo crear_grafo();

#endif