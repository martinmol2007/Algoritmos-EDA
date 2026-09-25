// EXTRA (no esta en el PDF) --- lower_bound / upper_bound a mano
// Variantes de busqueda binaria que NO buscan "una" aparicion, sino una
// FRONTERA. Son las mas utiles en la practica.
//
//   lower_bound(v,x) = primera posicion i con v[i] >= x   (donde insertarias x)
//   upper_bound(v,x) = primera posicion i con v[i] >  x
//
//   numero de apariciones de x = upper_bound - lower_bound
//
// Las dos devuelven v.size() si tal posicion no existe.
// Coste: Theta(log n).  Precondicion: v ordenado.

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Primera posicion con v[i] >= x.
template <typename elem>
int lower_bound_propio (const vector<elem>& v, const elem& x) {
    int l = 0, r = v.size();          // ojo: r = n, intervalo [l, r)
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] < x) l = m + 1;      // v[m] descartado
        else          r = m;          // v[m] todavia es candidato
    }
    return l;
}

// Primera posicion con v[i] > x.
template <typename elem>
int upper_bound_propio (const vector<elem>& v, const elem& x) {
    int l = 0, r = v.size();
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] <= x) l = m + 1;
        else           r = m;
    }
    return l;
}

template <typename elem>
int cuantas_veces (const vector<elem>& v, const elem& x) {
    return upper_bound_propio(v, x) - lower_bound_propio(v, x);
}

// ------------------------------------------------------------------- demo
int main() {
    int x;
    cin >> x;
    vector<int> v;
    int y;
    while (cin >> y) v.push_back(y);

    int lb = lower_bound_propio(v, x);
    int ub = upper_bound_propio(v, x);
    cout << "lower_bound = " << lb << endl;
    cout << "upper_bound = " << ub << endl;
    cout << "apariciones = " << cuantas_veces(v, x) << endl;

    // Comprobacion contra la STL
    cout << "STL lower  = " << (lower_bound(v.begin(), v.end(), x) - v.begin()) << endl;
    cout << "STL upper  = " << (upper_bound(v.begin(), v.end(), x) - v.begin()) << endl;
}
