// 5.3 --- Breadth First Search (recorrido en anchura)
// Las funciones devuelven la lista de vertices segun el orden en que se visitan
// en un recorrido en anchura.
// Este codigo usa C++11.

#include <queue>
#include "../../00-Comun/eda.hh"
#include "../../00-Comun/graph.hh"

// ---------------------------------------------------------------------------
// Version directa: igual que el dfs iterativo pero con una cola en vez de una
// pila. Encola cada vertice tantas veces como su grado de entrada.
// Coste: Theta(|V| + |E|).
// ---------------------------------------------------------------------------
list<int> bfs_1 (const graph& G) {
    int n = G.size();
    list<int> L;
    queue<int> Q;
    vector<boolean> vis(n, false);
    for (int u = 0; u < n; ++u) {
        Q.push(u);
        while (not Q.empty()) {
            int v = Q.front(); Q.pop();
            if (not vis[v]) {
                vis[v] = true; L.push_back(v);
                for (int w : G[v])  {
                    Q.push(w);
    }   }   }   }
    return L;
}

// ---------------------------------------------------------------------------
// Version mejor: evita encolar un vertice mas de una vez, marcandolo como
// "encontrado" en el momento de encolarlo y no en el de desencolarlo.
// Coste: Theta(|V| + |E|), pero la cola nunca supera |V| elementos.
// ---------------------------------------------------------------------------
list<int> bfs_2 (const graph& G) {
    int n = G.size();
    list<int> L;
    queue<int> Q;
    vector<boolean> enc(n, false);
    for (int u = 0; u < n; ++u) {
        if (not enc[u]) {
            Q.push(u); enc[u] = true;
            while (not Q.empty()) {
                int v = Q.front(); Q.pop();
                L.push_back(v);
                for (int w : G[v])  {
                    if (not enc[w]) {
                        Q.push(w);  enc[w] = true;
    }   }   }   }   }
    return L;
}

// ---------------------------------------------------------------------------
// EXTRA (no esta en el PDF): BFS desde un origen s calculando DISTANCIAS.
// En un grafo SIN pesos, el BFS da los caminos minimos en numero de aristas.
// Coste: Theta(|V| + |E|).
// ---------------------------------------------------------------------------
vector<int> bfs_distancias (const graph& G, int s) {
    int n = G.size();
    vector<int> d(n, -1);              // -1 = inalcanzable
    queue<int> Q;
    d[s] = 0;  Q.push(s);
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : G[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                Q.push(v);
    }   }   }
    return d;
}

// ------------------------------------------------------------------- demo
// Entrada:  n m  seguido de m arcos "u v".
int main() {
    int n, m;
    cin >> n >> m;
    graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    cout << "bfs_1: ";
    for (int u : bfs_1(G)) cout << u << " ";
    cout << endl;

    cout << "bfs_2: ";
    for (int u : bfs_2(G)) cout << u << " ";
    cout << endl;

    cout << "distancias desde 0: ";
    for (int d : bfs_distancias(G, 0)) cout << d << " ";
    cout << endl;
}
