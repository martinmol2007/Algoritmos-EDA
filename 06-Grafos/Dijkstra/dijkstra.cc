// 5.5 --- Shortest Paths: Dijkstra's Algorithm
// Caminos minimos desde un origen en un grafo dirigido con pesos NO NEGATIVOS.
//
// En vez de disminuir la prioridad asociada a un vertice, el algoritmo reinserta
// ese vertice con la nueva prioridad. Como consecuencia, cada vertice se puede
// insertar tantas veces como su grado de entrada. Esto no afecta al coste
// asintotico, que sigue siendo Theta((|V| + |E|) log |V|).
//
// Este codigo usa C++11.
//
// ERRATA DEL PDF: usa `infinit` (catalan); en eda.hh la constante es `infinity`.

#include "../../00-Comun/eda.hh"

typedef pair<double, int> WArc;         // weighted arc   (peso, destino)
typedef vector<vector<WArc>> WGraph;    // weighted digraf

// d[v] = distancia minima de s a v   (infinity si es inalcanzable)
// p[v] = predecesor de v en el camino minimo   (-1 si no lo tiene)
void dijkstra(const WGraph& G, int s, vector<double>& d, vector<int>& p) {
    int n = G.size();
    d = vector<double>(n, infinity);  d[s] = 0;
    p = vector<int>(n, -1);
    vector<boolean> S(n, false);                    // vertices ya definitivos
    priority_queue<WArc, vector<WArc>, greater<WArc> > Q;   // cola de MINIMOS
    Q.push(WArc(0, s));
    while (not Q.empty()) {
        int u = Q.top().second;  Q.pop();
        if (not S[u]) {                 // si ya es definitivo, entrada obsoleta
            S[u] = true;
            for (WArc a : G[u]) {
                int v = a.second;
                double c = a.first;
                if (d[v] > d[u] + c) {  // relajacion del arco (u,v)
                    d[v] = d[u] + c;
                    p[v] = u;
                    Q.push(WArc(d[v], v));
}
        }   }
    }
}

// ------------------------------------------------------------------- demo
// Entrada:  n m s   seguido de m arcos "u v peso".
//
// Ejemplo:
//   5 7 0
//   0 1 10
//   0 3 5
//   1 2 1
//   3 1 3
//   3 2 9
//   3 4 2
//   4 2 6
int main() {
    int n, m, s;
    cin >> n >> m >> s;
    WGraph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;  double w;
        cin >> u >> v >> w;
        G[u].push_back(WArc(w, v));
    }

    vector<double> d;
    vector<int> p;
    dijkstra(G, s, d, p);

    for (int v = 0; v < n; ++v) {
        cout << "d[" << v << "] = ";
        if (d[v] == infinity) cout << "inf";
        else                  cout << d[v];
        cout << "   camino: ";
        if (d[v] == infinity) cout << "-";
        else {
            // reconstruccion del camino hacia atras por los predecesores
            vector<int> cam;
            for (int u = v; u != -1; u = p[u]) cam.push_back(u);
            for (int i = cam.size() - 1; i >= 0; --i) cout << cam[i] << " ";
        }
        cout << endl;
    }
}
