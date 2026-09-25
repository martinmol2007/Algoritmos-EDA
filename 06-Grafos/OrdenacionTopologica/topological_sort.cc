// 5.4 --- Topological Sort (ordenacion topologica)
// Dado un grafo dirigido aciclico (DAG), devuelve una lista con sus vertices
// ordenados topologicamente, es decir, de forma que un vertice v no aparezca
// antes que un vertice u si hay un camino de u a v.
// Coste: Theta(|V| + |E|).
// Este codigo usa C++11.

#include <stack>
#include "../../00-Comun/eda.hh"
#include "../../00-Comun/graph.hh"

list<int> topological_sort(const graph& G) {
    int n = G.size();

    // ge[v] = grado de entrada de v
    vector<int> ge(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : G[u]) {
            ++ge[v];
        }
    }

    // Los vertices sin dependencias pendientes pueden salir ya.
    stack<int> S;
    for (int u = 0; u < n; ++u) {
        if (ge[u] == 0) {
            S.push(u);
        }
    }

    list<int> L;
    while (not S.empty()) {
        int u = S.top();  S.pop();
        L.push_back(u);
        for (int v : G[u]) {
            if (--ge[v] == 0) {     // v ya no depende de nadie
                S.push(v);
    }
        }
    }
    return L;
}

// ------------------------------------------------------------------- demo
// Entrada:  n m  seguido de m arcos "u v" (u debe ir antes que v).
//
// Ejemplo (un plan de estudios):
//   6 6
//   5 2
//   5 0
//   4 0
//   4 1
//   2 3
//   3 1
int main() {
    int n, m;
    cin >> n >> m;
    graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    list<int> L = topological_sort(G);
    if (int(L.size()) < n) {
        cout << "El grafo tiene un ciclo: no hay ordenacion topologica" << endl;
    } else {
        for (int u : L) cout << u << " ";
        cout << endl;
    }
}
