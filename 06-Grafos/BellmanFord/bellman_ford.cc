// EXTRA (no esta en el PDF) --- Algoritmo de Bellman-Ford
// Caminos minimos desde un origen en un grafo dirigido que PUEDE TENER PESOS
// NEGATIVOS. Ademas detecta si hay ciclos de peso negativo alcanzables.
//
// Dijkstra no sirve con pesos negativos: da por definitivo el vertice de
// distancia minima, y con un arco negativo esa distancia todavia podria bajar.
//
// Idea: relajar TODOS los arcos |V|-1 veces. Un camino minimo tiene como mucho
// |V|-1 aristas, y tras la pasada i estan bien todas las distancias cuyo camino
// minimo usa <= i aristas.
//
// Coste: Theta(|V| * |E|).  Bastante peor que Dijkstra, pero mas general.

#include <vector>
#include <iostream>
#include <limits>
using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Arc { int u, v; double w; };

// Devuelve false si hay un ciclo de peso negativo alcanzable desde s.
bool bellman_ford (int n, const vector<Arc>& arcs, int s,
                   vector<double>& d, vector<int>& p) {
    d.assign(n, INF);  d[s] = 0;
    p.assign(n, -1);

    // |V|-1 pasadas de relajacion de todos los arcos
    for (int i = 0; i < n - 1; ++i) {
        bool cambio = false;
        for (const Arc& a : arcs) {
            if (d[a.u] != INF and d[a.u] + a.w < d[a.v]) {
                d[a.v] = d[a.u] + a.w;
                p[a.v] = a.u;
                cambio = true;
            }
        }
        if (not cambio) break;        // ya ha convergido: podemos parar
    }

    // Pasada extra: si algo AUN mejora, hay un ciclo negativo.
    for (const Arc& a : arcs) {
        if (d[a.u] != INF and d[a.u] + a.w < d[a.v]) return false;
    }
    return true;
}

// ------------------------------------------------------------------- demo
// Entrada:  n m s   seguido de m arcos "u v peso" (los pesos pueden ser < 0).
//
// Ejemplo (con un arco negativo):
//   5 8 0
//   0 1 -1
//   0 2 4
//   1 2 3
//   1 3 2
//   1 4 2
//   3 2 5
//   3 1 1
//   4 3 -3
int main() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<Arc> arcs(m);
    for (int i = 0; i < m; ++i) cin >> arcs[i].u >> arcs[i].v >> arcs[i].w;

    vector<double> d;
    vector<int> p;
    if (not bellman_ford(n, arcs, s, d, p)) {
        cout << "Hay un ciclo de peso negativo alcanzable desde " << s << endl;
        return 0;
    }
    for (int v = 0; v < n; ++v) {
        cout << "d[" << v << "] = ";
        if (d[v] == INF) cout << "inf" << endl;
        else             cout << d[v] << endl;
    }
}
