// EXTRA (no esta en el PDF) --- Algoritmo de Kruskal
// Arbol de expansion minimo (MST) de un grafo no dirigido, conexo y con pesos.
//
// Estrategia VORAZ distinta de la de Prim: ordena TODAS las aristas por peso y
// las va cogiendo de menor a mayor, descartando las que formarian ciclo. Para
// detectar los ciclos en tiempo casi constante se usa un Union-Find.
//
// Coste: Theta(|E| log |E|) --- dominado por la ordenacion de las aristas.
//        (El Union-Find aporta solo Theta(|E| alpha(|V|)).)

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

// ------------------------------------------------------------- Union-Find
class UnionFind {
    vector<int> parent, rank_;
public:
    UnionFind (int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find (int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite (int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) ++rank_[rx];
        return true;
    }
};

// --------------------------------------------------------------- Kruskal
struct Edge {
    double w;
    int u, v;
    bool operator< (const Edge& e) const { return w < e.w; }
};

// Devuelve las aristas del MST y deja su peso total en `total`.
vector<Edge> kruskal (int n, vector<Edge> edges, double& total) {
    sort(edges.begin(), edges.end());        // Theta(|E| log |E|)
    UnionFind uf(n);
    vector<Edge> mst;
    total = 0;
    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {            // no forma ciclo -> la cogemos
            mst.push_back(e);
            total += e.w;
            if (int(mst.size()) == n - 1) break;   // ya tenemos el arbol
        }
    }
    return mst;
}

// ------------------------------------------------------------------- demo
// Entrada:  n m   seguido de m aristas "u v peso".
int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    double total;
    vector<Edge> mst = kruskal(n, edges, total);

    for (const Edge& e : mst) {
        cout << "arista " << e.u << " - " << e.v << "  peso " << e.w << endl;
    }
    cout << "peso total del MST = " << total << endl;
    if (int(mst.size()) != n - 1) cout << "(el grafo NO es conexo)" << endl;
}
