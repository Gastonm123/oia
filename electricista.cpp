#define forn(i, a, b) for(int i=a; i<b; i++)
#include <utility>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 5;
vector<int> grafo[MAXN];
bool interno[MAXN];
int n, modulo;

vector<pair<int ,int> > criba[MAXN];

long long pot(long long num, int potencia) {
	if (potencia == 0) 
		return 1;
	if (potencia == 1)
		return num;

	if (potencia % 2 == 0)
		return pot((num*num) % modulo, potencia/2);
	else
		return (num * pot((num*num) % modulo, potencia/2)) % modulo; 
}

#include <iostream>

int electricista(vector<int> tubosA, vector<int> tubosB, int x, int mod) {
	n = tubosA.size();
	modulo = mod;

	int hojas = n;

	forn (i, 0, n) {
		int a = tubosA[i];
		int b = tubosB[i];
		
		grafo[a].push_back(b);
		grafo[b].push_back(a);
		
		if (!interno[a] && a != 0 && grafo[a].size() > 1) {
			interno[a] = true;
			hojas--;
		}
		if (!interno[b] && b != 0 && grafo[b].size() > 1) {
			interno[b] = true;
			hojas--;
		}
	}
	
	int internos = n - hojas;
	int sobrantes = x - hojas;
	
	if (sobrantes < 0 || sobrantes > internos) {
		return -1;
	}
	
	if (internos == sobrantes || sobrantes == 0) {
	    return 1;
	}

	forn (i, 2, n) {
		if (criba[i].size() == 0) {
			for(int j = i, cont = 0; j < n; j+=i, cont++) {
				int potencia = 0;
				int numero = j;

				while (numero % i == 0) numero /= i, potencia++;
 
				criba[j].push_back(make_pair(i, potencia));
			}
		} 
	}

	// factorial de internos
	vector<int> factores_1;
	int num = internos;
	int factorial_1[n];
	int factorial_2[n];

	fill(factorial_1, factorial_1+n, 0);
	fill(factorial_2, factorial_2+n, 0);

	for (int i = num; i >= 2; i--) {
		for (auto factor : criba[i]) {
			if (factorial_1[factor.first] == 0) {
				factores_1.push_back(factor.first);
			}
			factorial_1[factor.first] += factor.second;
		}
	}

	// factorial de internos - sobrantes
	vector<int> factores_2;
	num = internos - sobrantes;
	for (int i = num; i >= 2; i--) {
		for (auto factor : criba[i]) {
			if (factorial_2[factor.first] == 0) {
				factores_2.push_back(factor.first);
			}
			factorial_2[factor.first] += factor.second;
		}
	}

	// factorial de sobrantes
	num = sobrantes;
	for (int i = num; i >= 2; i--) {
		for (auto factor : criba[i]) {
			if (factorial_2[factor.first] == 0) {
				factores_2.push_back(factor.first);
			}
			factorial_2[factor.first] += factor.second;
		}
	}

	for (int factor : factores_2) {
		factorial_1[factor] -= factorial_2[factor];
	}

	long long ans = 1;
	for (int factor : factores_1) {
		ans = (ans * pot(factor, factorial_1[factor])) % mod;
	}

	return ans;
}

#include <iostream>

int main() {
	int n, x, mod;
	cin >> n >> x >> mod;
	
	vector<int> tubosA(n);
	vector<int> tubosB(n);
	
	forn (i, 0, n) {
		cin >> tubosA[i] >> tubosB[i];
	}

	int ans = electricista(tubosA, tubosB, x, mod);

	cout << ans << endl;
}
