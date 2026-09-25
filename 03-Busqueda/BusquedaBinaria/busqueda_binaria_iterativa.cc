// EXTRA (no esta en el PDF) --- Busqueda binaria ITERATIVA
// Sobre un vector ORDENADO: compara con el elemento central y descarta la mitad
// en la que el elemento no puede estar.
//
// Coste: Theta(log n) en el caso peor.  Memoria extra: Theta(1).
// Precondicion: v esta ordenado de menor a mayor.

#include <vector>
#include <iostream>
using namespace std;

// Devuelve una posicion de x en v, o -1 si no esta.
template <typename elem>
int busqueda_binaria (const vector<elem>& v, const elem& x) {
    int l = 0, r = int(v.size()) - 1;
    while (l <= r) {
        // Asi, y no (l+r)/2: con l y r grandes, l+r puede desbordar el int.
        int m = l + (r - l) / 2;
        if (v[m] == x)      return m;
        else if (v[m] < x)  l = m + 1;   // x esta en la mitad derecha
        else                r = m - 1;   // x esta en la mitad izquierda
    }
    return -1;
}

// ------------------------------------------------------------------- demo
// Entrada: primero el elemento buscado, despues la secuencia ORDENADA.
int main() {
    int x;
    cin >> x;
    vector<int> v;
    int y;
    while (cin >> y) v.push_back(y);
    int p = busqueda_binaria(v, x);
    if (p == -1) cout << "no esta" << endl;
    else         cout << "posicion " << p << endl;
}
