#include <iostream>
#include <locale>
#include <time.h>
using namespace std;

struct Vertex {
	string name;

	Vertex(string n) : name(n) {}
};

struct Edge {
	Vertex begin;
	Vertex end;

	Edge(Vertex b, Vertex e) : begin(b), end(e) {}
};

struct Graph {
	// Incedence Matrix
	int** M;
	Vertex* vertexSet;
	Edge* edgeSet;

	// v - кол-во вершин, e - кол-во ребер
	Graph(int v, int e) {
		M = new int*[e];
		for (int i = 0; i < e; i++) {
			M[i] = new int[v];
			if (i > v) {
				for (int j = 0; j < v; j++) {
					M[i][j] = i;
				}
			}
			else {
				M[i][j] = 0;
			}
		}
	}

	void printMatrix(int** M, int n, int m) {
		cout << "Матрица:" << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << M[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	srand(static_cast<unsigned int>(time(NULL)));
	
	int V;
	cout << "Введи кол-во вершин: ";
	cin >> V; // >= 1
	int E;
	cout << "Введи кол-во ребер: ";
	cin >> E; // >= V
	Graph G(V, E);

	return 0;
}