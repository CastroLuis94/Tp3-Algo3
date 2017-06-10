#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include "coloreo.h"

using namespace std;

void grafo::add_edge(int v1, int v2) {
	vecinos[v1].push_back(v2);
	vecinos[v2].push_back(v1);
}

vector<int>& grafo::get_neigh(int v) {
	// for (auto w : vecinos[v])
	// 	cout << w;
	// cout << endl;
	return vecinos[v];
}

int grafo::n() {
	return vecinos.size() -1 ;//numerados del 1 a n
}

void grafo::print(){
	for (int v = 0; v < n(); ++v) {
		for (auto w : vecinos[v]) {
			cout << v << ' ' << w << endl;
		}
	}
}

vector<int> grafo::nodes_by_degree() {
	vector<int> nodos(this->n());
	iota(nodos.begin(), nodos.end(), 0);
	sort(nodos.begin(), nodos.end(), 
		[&] (int v, int w) {
			return this->get_neigh(v).size() < this->get_neigh(w).size();
		}
	);
	return nodos;
}


/*
grafo crear_grafo() {
	char c, p;
	string f;
	int n, m, v1, v2;

	for(cin >> c; c == 'c'; cin >> c) {
		getline(cin, f);
		//cout << c << endl;
	}

	cin >> p >> f >> n >> m;
	grafo g = grafo(n);
	for (int i = 0 ; i < m; ++i) {
		cin >> c >> v1 >> v2;
		//cout << c << v1 << v2 << endl;
		g.add_edge(v1-1, v2-1);
	}
	return g;
}
*/
