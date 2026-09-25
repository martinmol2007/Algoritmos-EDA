// 5.2 --- Depth First Search (recorrido en profundidad)
// Las funciones devuelven la lista de vertices segun su orden de visita en un
// recorrido en profundidad.
// Este codigo usa C++11.
//
// En el PDF los includes son:  #include "eda.hh"  y  #include "graph.hh"
// Aqui se usan rutas relativas para que compile sin flags adicionales.

#include <stack>
#include "../../00-Comun/eda.hh"
#include "../../00-Comun/graph.hh"

// ---------------------------------------------------------------------------
// Version recursiva. Coste: Theta(|V| + |E|).
// ---------------------------------------------------------------------------
void dfs_rec (const graph& G, int u, vector<boolean>& vis, list<int>& L) {
    if (not vis[u]) {
        vis[u] = true;  L.push_back(u);
        for (int v : G[u]) {
            dfs_rec(G, v, vis, L);
}   }   }

list<int> dfs_rec (const graph& G) {
    int n = G.size();
    list<int> L;
    vector<boolean> vis(n, false);
    for (int u = 0; u < n; ++u)  {
        dfs_rec(G, u, vis, L);
    }
    return L;
}

// ---------------------------------------------------------------------------
// Version iterativa: el orden de visita es distinto del de la version
// recursiva, porque los vecinos salen de la pila en orden inverso.
// Coste: Theta(|V| + |E|).
// ---------------------------------------------------------------------------
list<int> dfs_ite (const graph& G) {
    int n = G.size();
    list<int> L;
    stack<int> S;
    vector<boolean> vis(n, false);
    for (int u = 0; u < n; ++u) {
        S.push(u);
        while (not S.empty()) {
            int v = S.top();  S.pop();
            if (not vis[v]) {
                vis[v] = true;  L.push_back(v);
                for (int w : G[v]) {
                    S.push(w);
    }   }   }   }
    return L;
}

// ------------------------------------------------------------------- demo
// Entrada:  n m  seguido de m arcos "u v" (grafo dirigido, vertices 0..n-1).
//
// Ejemplo:
//   6 7
//   0 1
//   0 2
//   1 3
//   2 3
//   3 4
//   4 5
//   5 3
int main() {
    int n, m;
    cin >> n >> m;
    graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    cout << "dfs recursivo: ";
    for (int u : dfs_rec(G)) cout << u << " ";
    cout << endl;

    cout << "dfs iterativo: ";
    for (int u : dfs_ite(G)) cout << u << " ";
    cout << endl;
}
