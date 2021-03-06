#include <numeric>
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
		int i = 1;
		vector<int> ejes;
		while(i < vs.size()){
			ejes.push_back(i);
			i++;
		}
		axis = ejes;
}

vector<int> filtrar(vector<int> axis,int v1){
	int i = 0;
	vector<int> res;
	while(i < axis.size()){
		if(axis.at(i) != v1){
			res.push_back(axis.at(i));
		}
		i++;
	}
	return res;
}

void filtrar(vector< vector < int > >& vecinos,int v1){
	int i = 0;
	vector<vector< int > > res;
	while(i < vecinos.size()){
		vecinos.at(i) = filtrar(vecinos.at(i),v1);
		i++;
	}
	return ;
}

int maximo(vector<int> axis){
	int res = 0;
	int i = 0;
	while(i < axis.size()){
		if(res < axis[i]){
			res = axis[i];
		}
		i++;
	}
	return res;
}

void grafo::del_from_clique(int v1) {
	axis = filtrar(axis,v1);
	filtrar(vecinos,v1);
	//vecinos.resize(maximo(axis)+1);
}
void grafo::del_special() {
	axis.pop_back();
	int i = 0;
	while(i < vecinos.size()){
		if (vecinos[i].size() > 0 ){
			vecinos[i].pop_back();
		}
		i++;
	}
	vecinos.resize(maximo(axis)+1);
}


void grafo::add_edge(int v1, int v2) {
	if (not esta(vecinos[v1],v2)){
		vecinos[v1].push_back(v2);
	}
	if (not esta(vecinos[v2],v1)){
		vecinos[v2].push_back(v1);
	}
}
vector<int> grafo::ejes() {
	return axis;
}
int grafo::tamano() {
	return axis.size();
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

int grafo::degrees(){
	int i = 0;
	int res = 0;
	while(i < axis.size()){
		res += degree(axis[i]);
		i++;
	}
	return res;
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
			/*cout << get_neigh(v).size() << "del nodo " << v <<endl;
			cout << get_neigh(w).size() << "del nodo " << w <<endl;
			*/
			return this->get_neigh(v+1).size() < this->get_neigh(w+1).size();
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
 		add_edge(axis.at(i),v1);
		i++;
	}
	//cout << "llegue hasta aca" << endl;
	axis.push_back(v1);
}

grafo::grafo(vector<int>  vs){
		int i = 0;
		while(i < vs.size()){
			add_to_clique(vs[i]);
		}
	}