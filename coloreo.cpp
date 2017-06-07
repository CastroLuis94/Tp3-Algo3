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
	return vecinos.size();
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

bool coloreo::is_valid() {
	return all_of(color.cbegin(), color.cend(), 
		[&](int v){ 
			return all_of(
				g.get_neigh(v).cbegin(), g.get_neigh(v).cend(),
				 [&](int w){
					return v != w;
				}
			);
		}
	);
}
	
bool coloreo::color_factible(int v) {
	return all_of(g.get_neigh(v).cbegin(), g.get_neigh(v).cend(),
		[&] (int w) {
			return color[v] != color[w];
		}
	);
}

int coloreo::min_color_disponible(int v) {
	vector<int> colores_vecinos;
	for (auto w : g.get_neigh(v)) {
		colores_vecinos.push_back(color[w]);
	}
	sort(colores_vecinos.begin(), colores_vecinos.end());
	int color_min = 0;
	for (auto c : colores_vecinos) {
		if (c == color_min) {
			color_min++;
		}
	}

	return color_min;
}

int coloreo::chi() {
	// empezamos los colores en 0 y son todos consecutivos!
	return *max_element(color.begin(), color.end()) + 1;
}

void coloreo::colorear_secuencial(vector<int>& nodos_en_orden) {
	for (auto v : nodos_en_orden) {
		this->color[v] = this->min_color_disponible(v);
	}
}
	
void coloreo::recolorear_consecutivos() {
	int min_c = 0;
	for (auto cl : this->clases()) {
		if (cl.second.size() > 0) {
			this->asignar_color(cl.second, min_c);
			min_c++;
		}
	}
}

void coloreo::print(){
	cout << n << ' ' << this->chi() << endl;
	for(int v = 0; v < n; ++ v) {
		cout << v << ' ' << color[v] << endl;
	}
}

vector<pair<int, vector<int> > > coloreo::clases() {
	vector< pair<int, vector<int> > > c_clases(this->chi(), pair<int, vector<int> >(-1, vector<int>()));
	for (int c = 0; c < this->chi(); ++c) {
		c_clases[c].first = c;
	}
	for(int v = 0; v < n; ++v) {
		c_clases[color[v]].second.push_back(v);
	}
	return c_clases;
}

set<int> coloreo::nodos_conflictivos(int v) {
	set<int> conflictos;
	for (auto w : g.get_neigh(v)) {
		if (color[v] == color[w]) {
			conflictos.insert(w);
		}
	}
	return conflictos;
}

set<int> coloreo::nodos_conflictivos() {
	set<int> conflictos;
	for(int v = 0; v < n; ++v) {
		for (auto w : this->nodos_conflictivos(v)) {
			conflictos.insert(w);
		}
	}
	return conflictos;
}



void coloreo::asignar_color(vector<int> vs, int c) {
	for(auto v : vs) {
		color[v] = c;
	}
}

grafo crear_grafo() {
	char c, p;
	string f;
	int n, m, v1, v2;
/*
	for(cin >> c; c == 'c'; cin >> c) {
		getline(cin, f);
		//cout << c << endl;
	}
*/
	cin >> p >> f >> n >> m;
	grafo g = grafo(n);
	for (int i = 0 ; i < m; ++i) {
		cin >> c >> v1 >> v2;
		//cout << c << v1 << v2 << endl;
		g.add_edge(v1-1, v2-1);
	}
	return g;
}

