// EXTRA (no esta en el PDF) --- Union-Find / Disjoint Set Union (DSU)
// Estructura para mantener una particion de {0..n-1} en conjuntos disjuntos con
// dos operaciones:
//   find(x)    -> representante del conjunto de x
//   unite(x,y) -> une los conjuntos de x e y
//
// Con las DOS optimizaciones (union por rango + compresion de caminos) el coste
// amortizado de cada operacion es Theta(alpha(n)), donde alpha es la inversa de
// la funcion de Ackermann: para cualquier n imaginable, alpha(n) <= 4.
// A efectos practicos, es CONSTANTE.

#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

class UnionFind {
private:
    vector<int> parent;   // parent[x] = padre de x (x si es raiz)
    vector<int> rank_;    // cota superior de la altura del arbol de x
    int n_sets;           // numero de conjuntos

public:
    UnionFind (int n) : parent(n), rank_(n, 0), n_sets(n) {
        iota(parent.begin(), parent.end(), 0);   // parent[i] = i
    }

    // COMPRESION DE CAMINOS: al buscar la raiz, cuelga todos los nodos del
    // camino directamente de ella. Aplana el arbol para futuras busquedas.
    int find (int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    // UNION POR RANGO: cuelga el arbol mas bajo del mas alto, para que la
    // altura no crezca innecesariamente.
    // Devuelve false si x e y ya estaban en el mismo conjunto.
    bool unite (int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) ++rank_[rx];
        --n_sets;
        return true;
    }

    bool same (int x, int y) { return find(x) == find(y); }

    int count_sets () const { return n_sets; }
};

// ------------------------------------------------------------------- demo
int main() {
    UnionFind uf(10);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(5, 6);
    cout << "same(0,2) = " << uf.same(0, 2) << endl;   // 1
    cout << "same(0,5) = " << uf.same(0, 5) << endl;   // 0
    cout << "conjuntos = " << uf.count_sets() << endl; // 10 - 3 = 7
    uf.unite(2, 6);
    cout << "same(0,5) = " << uf.same(0, 5) << endl;   // 1
    cout << "conjuntos = " << uf.count_sets() << endl; // 6
}
