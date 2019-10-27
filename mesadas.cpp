#include <utility>
#include <iostream>
#define forn(i, a, b) for(int i=a; i<b; i++)
#include <algorithm>

using namespace std;

const int MAXN = 2e5;
pair<int, int> mesadas[MAXN];

int main() {
	freopen("mesadas.in", "r", stdin);
	freopen("mesadas.out", "w", stdout);

	int n;
	cin >> n;

	forn(i, 0, n) {
		int a, b;
		cin >> a >> b;

		if (a < b) {
			swap(a, b);
		}

		mesadas[i] = make_pair(a, b);
	}

	sort(mesadas, mesadas+n);
	int anterior = 0;
	int ans = 0;

	forn (i, 0, n) {
		auto mesada = mesadas[i];
		if (mesada.second < anterior || anterior == 0) {
			ans += 1;
		}
		anterior = mesada.second;	
	}

	cout << ans << endl;
	return 0;
}
