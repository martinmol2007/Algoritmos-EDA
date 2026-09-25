// 5.6 --- Minimum Spanning Tree: Prim's Algorithm
// Arbol de expansion minimo de un grafo NO dirigido y conexo con pesos.
//
// Las aristas se insertan en la cola de prioridad con el signo cambiado.
// Alternativamente se podria haber redefinido el orden de la cola.
// Coste: Theta((|V| + |E|) log |V|).
//
// ERRATA DEL PDF: la linea  Q.push({0.0, {0, 0}));  tiene los parentesis mal
// cerrados y no compila. Aqui esta corregida a  Q.push({0.0, {0, 0}});

#include "../../00-Comun/eda.hh"

typedef pair< double, pair<int, int> > WEdge;
typedef vector< vector< pair<double, int> > > WGraph;

void MST(const WGraph& G, vector<int>& parent) {
    vector<bool> used(G.size(), false);
    priority_queue<WEdge> Q;                   // cola de MAXIMOS
    Q.push({0.0, {0, 0}});                     // arista ficticia hacia el vertice 0

    while (not Q.empty()) {
        double p = Q.top().first;
        int u = Q.top().second.first;
        int v = Q.top().second.second;
        Q.pop();
        (void)p;                               // p no se usa (esta en el PDF)
        if (not used[v]) {
            used[v] = true;
            parent[v] = u;
            for (auto e : G[v]) {
                double p = e.first;
                int w = e.second;
                Q.push({-p, {v, w}});          // signo cambiado: max-heap -> min
}   }   }   }

// ------------------------------------------------------------------- demo
// Entrada:  n m   seguido de m aristas "u v peso" (grafo NO dirigido).
//
// Ejemplo:
//   5 7
//   0 1 2
//   0 3 6
//   1 2 3
//   1 3 8
//   1 4 5
//   2 4 7
//   3 4 9
int main() {
    int n, m;
    cin >> n >> m;
    WGraph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;  double w;
        cin >> u >> v >> w;
        G[u].push_back({w, v});
        G[v].push_back({w, u});      // no dirigido: cada arista son dos arcos
    }

    vector<int> parent(n, -1);
    MST(G, parent);

    double total = 0;
    for (int v = 1; v < n; ++v) {
        int u = parent[v];
        double w = 0;
        for (auto e : G[v]) if (e.second == u) { w = e.first; break; }
        cout << "arista " << u << " - " << v << "  peso " << w << endl;
        total += w;
    }
    cout << "peso total del MST = " << total << endl;
}
