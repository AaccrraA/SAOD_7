#include <iostream>
#include <locale>
#include <time.h>
#include <vector>
using namespace std;

struct Vertex {
	int number;
};

struct Edge {
	Vertex begin;
	Vertex end;
};

struct Graph {
	// Incedence Matrix
    vector<vector<int>> M;
	vector<Vertex> vertexSet;
	vector<Edge> edgeSet;

	// v - кол-во вершин, e - кол-во ребер
	Graph(int v, int e) {
        M.resize(e);
        vertexSet.resize(v);
        edgeSet.resize(e);
        for (int i = 0; i < v; i++)
            vertexSet[i].number = i + 1;
        
		for (int i = 0; i < e; i++) {
            M[i].resize(v);
			if (i > v - 1) {
                edgeSet[i].begin.number = rand()%v;
                edgeSet[i].end.number = rand()%v;
                M[i][edgeSet[i].end.number] = rand()%99 + 1;
			}
			else {
				M[i][(i+1)%v] = i + 1;
                edgeSet[i].begin.number = i;
                edgeSet[i].end.number = (i+1)%v;
			}
		}
	}

	void printMatrix() {
		cout << "Матрица:" << endl;
		for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < M[0].size(); j++) {
                M[i][j] != 0 ? cout << M[i][j] : cout << ".";
                cout << " ";
                M[i][j] < 10 ? cout << " " : cout << "";
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
    G.printMatrix();
	return 0;
}