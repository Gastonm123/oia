#define forn(i, a, b) for(int i=a; i<b; i++)
#include <bitset>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 2e5;
int n, m;
bool miMapa[MAXN];
int set[MAXN];
int size[MAXN];

bool entra(int y, int x) {
	return (y >= 0 && y < n && x >= 0 && x < m);
}

int find_set(int a) {
	if (set[a] == a) {
		return a;
	}

	return set[a] = find_set(set[a]);
}

int areas_accesible = 0;

void union_set(int a, int b) {
	a = find_set(a);
	b = find_set(b);

	if (a == b)
		return;

	if (size[a] < size[b]) {
		swap(a, b);
	}

	set[b] = set[a];
	size[a] += size[b];
	size[b] = 0;
}


vector<int> laboratorio(vector<string> mapa, vector<int> perrosF, vector<int> perrosC) {
	n = mapa.size();
	m = mapa[0].size();

	forn (i, 0, n) {
		forn (j, 0, m) {
			int index = i*m+j;
			set[index] = index;
			size[index] = 1;
		}
	}

	int entrada; bool hayEntrada = false;
	vector<pair<int, int> > entradas;
	int nro_entradas = 0;
	
	forn (i, 0, n) {
		forn (j, 0, m) {
			int index = i*m+j;

			miMapa[index] = (mapa[i][j] != '#');
			if (mapa[i][j] == 'E') {
				entradas.push_back(make_pair(i, j));	
				nro_entradas++;
			}
		}
	}

	int p;
	p = perrosF.size();
	
	forn (i, 0, p) {
		int fila = perrosF[i];
		int columna = perrosC[i];
		int index = fila*m+columna;

		miMapa[index] = false;
	}

	reverse(perrosF.begin(), perrosF.end());
	reverse(perrosC.begin(), perrosC.end());

	forn (i, 0, n) {
		forn (j, 0, m) { 
			int index = i*m+j;

			if (miMapa[index]) {
				if (i < n-1 && miMapa[(i+1)*m+j]) {
					union_set(index, (i+1)*m+j);
				}

				if (j < m-1 && miMapa[i*m+j+1]) {
					union_set(index, i*m+j+1);
				}
			}
		}
	}

	vector<int> resultados;
	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};
	bitset<MAXN> contados;

	forn (i, 0, p) {
		int fila = perrosF[i];
		int columna = perrosC[i];
		int index = fila*m+columna;
 
		int areas_accesibles = 0;
	
		for (auto pos : entradas) {
			int index_entrada = pos.first*m+pos.second;
			int set_entrada = find_set(index_entrada);

			if (contados[set_entrada]) 
				continue;

			if (miMapa[index_entrada]) {
				areas_accesibles += size[set_entrada];
				contados[set_entrada] = true;
			}
		}
		
		contados.reset();

		resultados.push_back(areas_accesibles);

		// saco un perro
		miMapa[index] = true;

		forn (j, 0, 4) {
			int new_fila = fila + dy[j];	
			int new_columna = columna + dx[j];	
			int new_index = new_fila*m+new_columna;

			if (!entra(new_fila, new_columna)) 
				continue;

			if (miMapa[new_index]) {
				union_set (index, new_index);
			}
		}
	}

	reverse(resultados.begin(), resultados.end());

	return resultados;
}

#ifndef SERVIDOR
	#include <iostream>	
	#include <vector>
	int main() {
		int n, m, p;
		cin >> n >> m >> p;

		vector<string> mapa(n);

		for(int i=0; i<n; i++) {
			string in;
			cin >> in;
			mapa[i] = in;
		}

		vector<int> perrosF(p);
		vector<int> perrosC(p);
		
		for(int i=0; i<p; i++) {
			int fila, col;
			cin >> fila >> col;
			perrosF[i] = fila;
			perrosC[i] = col;
		}

		auto result = laboratorio(mapa, perrosF, perrosC);

		for (int query : result) {
			cout << query << " ";
		}
		cout << endl;
	}
#endif