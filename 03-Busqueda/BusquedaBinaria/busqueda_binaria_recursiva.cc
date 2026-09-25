// EXTRA (no esta en el PDF) --- Busqueda binaria RECURSIVA
// Misma idea que la iterativa, expresada como divide y venceras.
//
// Coste: T(n) = T(n/2) + Theta(1)  =>  Theta(log n).
// Memoria extra: Theta(log n) de pila (o Theta(1) si el compilador hace
// eliminacion de la recursion de cola, que aqui es aplicable).

#include <vector>
#include <iostream>
using namespace std;

// Busca x en v[l..r]. Devuelve la posicion, o -1 si no esta.
template <typename elem>
int busqueda_binaria (const vector<elem>& v, const elem& x, int l, int r) {
    if (l > r) return -1;                 // caso base: rango vacio
    int m = l + (r - l) / 2;
    if (v[m] == x)     return m;
    else if (v[m] < x) return busqueda_binaria(v, x, m + 1, r);
    else               return busqueda_binaria(v, x, l, m - 1);
}

template <typename elem>
int busqueda_binaria (const vector<elem>& v, const elem& x) {
    return busqueda_binaria(v, x, 0, int(v.size()) - 1);
}

// ------------------------------------------------------------------- demo
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
