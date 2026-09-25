// EXTRA (no esta en el PDF) --- Algoritmo de Floyd-Warshall
// Caminos minimos entre TODOS los pares de vertices. Admite pesos negativos
// (pero no ciclos de peso negativo).
//
// Es programacion dinamica: d[k][i][j] = camino minimo de i a j usando como
// vertices intermedios solo los de {0..k-1}. La recurrencia
//     d[k+1][i][j] = min(d[k][i][j], d[k][i][k] + d[k][k][j])
// se puede aplicar sobre la MISMA matriz (por eso el bucle de k va FUERA).
//
// Coste: Theta(|V|^3) de tiempo, Theta(|V|^2) de memoria.
// Para grafos densos es mejor que ejecutar |V| veces Dijkstra.

#include <vector>
#include <iostream>
#include <limits>
using namespace std;

const double INF = numeric_limits<double>::infinity();

// d[i][j] entra con el peso del arco i->j (INF si no hay, 0 en la diagonal)
// y sale con la distancia minima de i a j.
void floyd_warshall (vector<vector<double>>& d) {
    int n = d.size();
    for (int k = 0; k < n; ++k) {           // OJO: k es el bucle EXTERNO
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] != INF and d[k][j] != INF and
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
    }   }   }   }
}

// ------------------------------------------------------------------- demo
// Entrada:  n m   seguido de m arcos "u v peso".
//
// Ejemplo:
//   4 5
//   0 1 5
//   0 3 10
//   1 2 3
//   2 3 1
//   3 0 2
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<double>> d(n, vector<double>(n, INF));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;  double w;
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v], w);
    }

    floyd_warshall(d);

    // Un ciclo negativo se detecta porque algun d[i][i] queda < 0.
    for (int i = 0; i < n; ++i) {
        if (d[i][i] < 0) { cout << "Hay un ciclo de peso negativo" << endl; return 0; }
    }

    cout << "matriz de distancias minimas:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] == INF) cout << "inf\t";
            else                cout << d[i][j] << "\t";
        }
        cout << endl;
    }
}
