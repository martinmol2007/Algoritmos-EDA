// 6.7 --- Hamiltonian Graph
// Escribir un algoritmo que determine si un grafo dado es hamiltoniano, es
// decir, si tiene un ciclo que pasa exactamente una vez por cada vertice.
//
// Solucion por backtracking. Se supone que el grafo dado es conexo y que las
// listas de adyacencia estan ordenadas.
//
// s[v] = siguiente vertice de v en el camino (-1 si v no se ha usado). Es una
// representacion del camino "por sucesores" muy comoda para deshacer.
//
// NOTA: el problema del ciclo hamiltoniano es NP-completo. No se conoce ningun
// algoritmo polinomico, y este backtracking es exponencial en el caso peor.

#include "../../00-Comun/eda.hh"
#include <algorithm>

typedef vector< vector<int> > Graph;
typedef list<int>::iterator iter;

class HamiltonianGraph {
    Graph G;            // the graph
    int n;              // number of vertices
    bool found;         // indicates if a cycle has been found
    vector<int> s;      // next of each vertex (-1 if not used)
    vector<int> S;      // solution (if found)

    void recursive(int v, int t) {
        // v = last vertex in the path, t = length of the path
        if (t == n) {
            // we need to check that the cycle can be closed
            if (not G[v].empty() and G[v][0] == 0) {
                s[v] = 0;
                found = true;
                S = s;
                s[v] = -1;
            }
        } else {
            for (int u : G[v]) {
                if (s[u] == -1) {
                    s[v] = u;
                    recursive(u, t+1);
                    s[v] = -1;              // deshacer
                    if (found) return;
    }   }   }   }

public:
    HamiltonianGraph(Graph G) {
        this->G = G;
        n = G.size();
        s = vector<int>(n, -1);
        found = false;
        recursive(0, 1);
    }

    bool has_a_solution() {
        return found;
    }

    vector<int> solution() {
        return S;
    }
};

// ---------------------------------------------------------------------------
// Lee el grafo: primero el numero de vertices; despues, para cada vertice, su
// grado y su lista de adyacencia.
// ---------------------------------------------------------------------------
Graph read_graph() {
    Graph G;
    int n = readint();
    G = Graph(n);
    for (int u = 0; u < n; u++) {
        int d = readint();
        for (int i = 0; i < d; i++) {
            G[u].push_back(readint());
        }
        sort(G[u].begin(), G[u].end());
    }
    return G;
}

// ------------------------------------------------- Main program
// Lee el grafo, crea el resolvedor y lo ejecuta.
//
// Ejemplo (un ciclo de 5 vertices, no dirigido):
//   5
//   2 1 4
//   2 0 2
//   2 1 3
//   2 2 4
//   2 3 0
int main() {
    HamiltonianGraph ham(read_graph());
    if (ham.has_a_solution()) {
        vector<int> s = ham.solution();
        cout << 0 << " ";
        for (int u = s[0]; u != 0; u = s[u]) {
            cout << u << " ";
        }
        cout << endl;
}   }
