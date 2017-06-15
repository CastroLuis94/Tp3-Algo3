#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include "coloreo.h"

using namespace std;

bool esta(vector<int>& nodos,int v){    
    for(int i = 0; i < nodos.size(); i++){
        if(nodos[i] == v){
            return true;
        }
    }
    return false;
}

grafo::grafo(vector< vector<int> >& vs){
		vecinos = vs;
		int i = 0;
		vector<int> ejes;
		while(i < vs.size()){
			int k = 0;
			while(k < vs[i].size()){
				if(not esta(axis,vs[i][k])){
					ejes.push_back(vs[i][k]);
				}
				k++;
			}
			i++;
		}
		axis = ejes;
}

void grafo::add_edge(int v1, int v2) {
	vecinos[v1].push_back(v2);
	vecinos[v2].push_back(v1);
}
vector<int> grafo::ejes() {
	return axis;
}
void grafo::add_axis(int v1) {
	vector <int> vacio;
	while(vecinos.size() < v1){
		vecinos.push_back(vacio);
	}
	axis.push_back(v1);
}
vector<int>& grafo::get_neigh(int v) {
	// for (auto w : vecinos[v])
	// 	cout << w;
	// cout << endl;
	return vecinos[v];
}

int grafo::degree(int nodo){
	return (get_neigh(nodo)).size();
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

void grafo::add_to_clique(int v1){
	if (vecinos.size() <= v1){
		vecinos.resize(v1 + 1);
	}
	int i = 0;
	while(i < axis.size()){
 		add_edge(axis[i],v1);
		i++;
	}
	axis.push_back(v1);
}

