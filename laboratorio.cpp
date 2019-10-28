#define forn(i, a, b) for(int i=a; i<b; i++)
#include <bitset>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
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
	a++;
	b++;

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

#include <iostream>
vector<int> laboratorio(vector<string> mapa, vector<int> perrosF, vector<int> perrosC) {
	n = mapa.size();
	m = mapa[0].size();

	forn (i, 0, n) {
		forn (j, 0, m) {
			int index = i*m+j;
			set[index] = index;
			size[index] = 1;

			miMapa[index] = (mapa[i][j] != '#'); 
		}
	}

	set[n*m] = n*m;
	size[n*m] = 1;

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
				if (mapa[i][j] == 'E') {
					union_set(-1, index);
				}

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

	forn (i, 0, n) {
		forn (j, 0, m) {
			cout << set[i*m+j] << " ";
		}
		cout << endl;
	}

	forn (i, 0, p) {
		int fila = perrosF[i];
		int columna = perrosC[i];
		int index = fila*m+columna;
 
		resultados.push_back(size[find_set(0)]-1);

		// saco un perro
		miMapa[index] = true;

		if (mapa[fila][columna] == 'E')
			union_set(-1, index);

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

#include <iostream>	
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
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
