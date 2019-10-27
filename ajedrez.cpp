#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>
#define forn(i, a, b) for(int i = a; i < b; i++)
#define forr(i, a, b) for(int i = b; i >= a; a--)

using namespace std;

const int MAXN = 1000;
int n;

bool obstaculos[MAXN][MAXN];

bool entran(int y, int x) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

vector<pair<int, int> > movimientosCaballo(int x, int y) {
    int movimientos[] = {
        2, -1,
        2, 1,
        1, 2,
        -1, 2,
        -2, -1,
        -2, 1,
        1, -2,
        -1, -2
    };

    vector<pair<int, int> > ans;
    for (int i = 0; i < 16; i += 2) {
        int ny = y + movimientos[i];
        int nx = x + movimientos[i+1];

        if (entran(ny, nx) && obstaculos[ny][nx] == false) {
            ans.push_back(make_pair(ny, nx));
        }
    }

    return ans;
}

vector<pair<int, int> > movimientosAlfil(int x, int y) {
    int movimientos[] = {
        1, 1,
        -1, 1,
        -1, -1,
        1, -1
    };

    vector<pair<int, int> > ans;
    for(int i = 0; i < 8; i += 2) {
        int ny = y;
        int nx = x;

        while(1) {
            ny += movimientos[i];
            nx += movimientos[i+1];

            // fijo si puedo realizar el movimiento
            if (entran(ny, nx) && obstaculos[ny][nx] == false) {
                ans.push_back(make_pair(nx, ny));
            } else {
                break;
            }
        }
       
    }

    return ans;
} 

vector<pair<int, int> > movimientosTorre(int x, int y) {
    int movimientos[] = {
        1, 0,
        0, 1,
        -1, 0,
        0, -1
    };

    vector<pair<int, int> > ans;
    for(int i = 0; i < 8; i += 2) {
        int ny = y;
        int nx = x;

        while(1) {
            ny += movimientos[i];
            nx += movimientos[i+1];

            // fijo si puedo realizar el movimiento
            if (entran(ny, nx) && obstaculos[ny][nx] == false) {
                ans.push_back(make_pair(ny, nx));
            } else {
                break;
            }
        }
       
    }

    return ans;
} 

int distancias[MAXN][MAXN];

int distancia_absoluta(int x, int y) {
    return (n-1-x + n-1-y);
}

int main() {
    // freopen("ajedrez.in", "r", stdin);
    // freopen("ajedrez.out", "w", stdout);

    int c;

    cin >> n >> c;

    forn(i, 0, c) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        a--; b--; c--; d--;

        if (a == c) { // horizontal
            forn(i, min(b, d), max(b, d)+1) {
                obstaculos[a][i] = 1;
            }
        }
        else {
            if (b == d) { // vertical
                forn(i, min(a, c), max(a, c)+1) {
                    obstaculos[i][b] = 1;
                }
            }
            else { // diagonal
                int inicio_x = b;
                int inicio_y = a;
                int direccion_y = c - a < 0 ? -1 : 1;
                int direccion_x = d - b < 0 ? -1 : 1;

                forn(i, 0, abs(b-d)+1) {
                    a = inicio_y + i*direccion_y;
                    b = inicio_x + i*direccion_x;
                    obstaculos[a][b] = 1;
                }
            }
        }
    } 

    priority_queue<tuple<int, int, int, int, int, tuple<int, int, int> >, vector<tuple<int, int, int, int, int, tuple<int, int, int> > >, greater<tuple<int, int, int, int, int, tuple<int, int, int> > > > pq;
    pq.push(make_tuple(0,0,0,0,0,make_tuple(0,0,0)));
    
    forn(i, 0, n) forn(j, 0, n) distancias[i][j] = 1e9; 

    while(pq.size()) {
        auto pos = pq.top();
        pq.pop();

        int y = get<3>(pos);
        int x = get<4>(pos);
        int dist = get<0>(pos);
        int jugadas = get<1>(pos);

        auto anteriores = get<5>(pos);

        int ant_caballo = get<0>(anteriores);
        int ant_alfil = get<1>(anteriores);
        int ant_torre = get<2>(anteriores);

        if (distancias[y][x] < dist) {
            continue;
        }

        distancias[y][x] = dist;
        int distancia_llegada = distancia_absoluta(x, y);

        if (y == n-1 && x == n-1) {
            cout << jugadas << " " << dist << endl;
            break;
        }

        if (ant_caballo+1 < 3) {
            vector<pair<int, int> > caballo = movimientosCaballo(x, y);

            for (auto movimiento : caballo) {
                if (distancias[movimiento.first][movimiento.second] < dist+1) {
                    continue;
                }

                pq.push(make_tuple(dist+1, distancia_llegada, jugadas+1, movimiento.first, movimiento.second, make_tuple(ant_caballo+1, 0, 0)));
            }
        }

        if (ant_alfil+1 < 3) {
            vector<pair<int, int> > alfil = movimientosAlfil(x, y);

            for (auto movimiento : alfil) {
                if (distancias[movimiento.first][movimiento.second] < dist+2) {
                    continue;
                }

                pq.push(make_tuple(dist+2, distancia_llegada, jugadas+1, movimiento.first, movimiento.second, make_tuple(0, ant_alfil+1, 0)));
            }
        }


        if (ant_torre+1 < 3) {
            vector<pair<int, int> > torre = movimientosTorre(x, y);

            for (auto movimiento : torre) {
                if (distancias[movimiento.first][movimiento.second] < dist+3) {
                    continue;
                }

                pq.push(make_tuple(dist+3, distancia_llegada, jugadas+1, movimiento.first, movimiento.second, make_tuple(0, 0, ant_torre+1)));
            }
        }
    }

    return 0;
}