#include <iostream>
#include <locale>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

struct Vertex {
	int num;
	bool isPainted;

	Vertex() : num(0), isPainted(false) {}
};
struct Edge {
	int B; // begin ind
	int E; // end ind
};

struct Graph {
public:
    vector<vector<int>> M; // Матрица инцидентности
	vector<Vertex> vertexSet; // Вектор вершин
	vector<Edge> edgeSet; // Вектор дуг

	// Инициализируем граф
	Graph(int v, int e, int w, int h) {
        M.resize(e);
        vertexSet.resize(v);
		
		for (int i = 0; i < v; i++) {
			vertexSet[i].num = i;
		}
		
		for (int i = 0; i < e; i++) {
			M[i].resize(v);
		}

		for (int i = 0, j = 0; i < v; i++) {
			if (i + 1 < v && ((i + 1) % w - i%w) == 1)  {
				if (addEdge(i, i + 1)) {
					M[j][edgeSet[j].B] = 1;
					M[j][edgeSet[j].E] = 1;
					j++;
				}
			}
			if (i - 1 >= 0 && (i%w - (i - 1) % w) == 1) {
				if (addEdge(i, i - 1)) {
					M[j][edgeSet[j].B] = 1;
					M[j][edgeSet[j].E] = 1;
					j++;
				}
			}
			if (i - w >= 0) {
				if (addEdge(i, i - w)) {
					M[j][edgeSet[j].B] = 1;
					M[j][edgeSet[j].E] = 1;
					j++;
				}
			}
			if (i + w < v) {
				if (addEdge(i, i + w)) {
					M[j][edgeSet[j].B] = 1;
					M[j][edgeSet[j].E] = 1;
					j++;
				}
			}
		}
	}

	// Распечатываем матрицу инцидентности
	void PrintMatrix () {
		cout << "Матрица:" << endl;
		for (int i = 0; i <= M.size(); i++) {
			if (i - 1 == -1)
				cout << "     ";
			else
				cout << " " << edgeSet[i-1].B << ">" << edgeSet[i-1].E << " ";
            for (int j = 0; j < M[0].size(); j++) {
				if (i - 1 == -1) {
					cout << vertexSet[j].num << " ";
					vertexSet[j].num < 10 ? cout << " " : cout << "";
				}
				else {
					M[i-1][j] != 0 ? cout << M[i-1][j] : cout << ".";
					cout << " ";
					M[i-1][j] < 10 ? cout << " " : cout << "";
				}
            }
            cout << endl;
        }

		ofstream fout("Grapgh.gv");
		
		fout << "graph {" << endl;
		for (int i = 0; i < M[i].size(); i++)
			if (vertexSet[i].isPainted)
				fout << vertexSet[i].num << "[color=lightblue,style=filled];" << endl;
		for (int i = 0; i < M.size(); i++)
			fout << edgeSet[i].B << " -- " << edgeSet[i].E << endl;
		fout << "}" << endl;
	}

	void DepthFirstSearch (int num) {
		vertexSet[num].isPainted = true;
		for (int i = 0; i < M.size(); i++) {
			if (vertexSet[edgeSet[i].B].num == num && !vertexSet[edgeSet[i].E].isPainted) {
				DepthFirstSearch(vertexSet[edgeSet[i].E].num);
			}
			else if (vertexSet[edgeSet[i].E].num == num && !vertexSet[edgeSet[i].B].isPainted) {
				DepthFirstSearch(vertexSet[edgeSet[i].B].num);
			}
		}
	}

private:
	// Добавляем дугу, если отсутствует
	bool addEdge(int begin, int end) {
		Edge tempEdge;
		tempEdge.B = begin;
		tempEdge.E = end;

		bool isAdded = true;
		for (int i = 0; i < edgeSet.size(); i++) {
			if ((edgeSet[i].B == begin && edgeSet[i].E == end) || (edgeSet[i].E == begin && edgeSet[i].B == end)) {
				isAdded = false;
			}
		}
		if (isAdded) {
			edgeSet.push_back(tempEdge);
		}
		return isAdded;
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	srand(static_cast<unsigned int>(time(NULL)));

	int W, H, V, E;
	cout << "Введи ширину изображения: ";
	cin >> W;
	cout << "Введи высоту изображения: ";
	cin >> H;
	V = W*H;
	E = W*(H - 1) + H*(W - 1);

	Graph G(V, E, W, H);
	G.DepthFirstSearch(4);
    G.PrintMatrix();

	return 0;
}