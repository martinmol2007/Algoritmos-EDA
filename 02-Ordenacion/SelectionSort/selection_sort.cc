// 2.1 --- Selection Sort
// Ordenacion por seleccion: en cada iteracion busca el minimo del subvector que
// queda por ordenar y lo coloca en su sitio con un intercambio.
//
// Coste: Theta(n^2) en todos los casos.  Intercambios: Theta(n).

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
int pos_min (vector<elem>& v, int l, int r);   // declaracion previa

template <typename elem>
void sel_sort (vector<elem>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        int p = pos_min(v, i, n-1);
        swap(v[i], v[p]);
    }
}

// Devuelve la posicion del minimo de v[l..r].
template <typename elem>
int pos_min (vector<elem>& v, int l, int r) {
    int p = l;
    for (int j = l + 1; j <= r; ++j) {
        if (v[j] < v[p]) {
            p = j;
        }
    }
    return p;
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    sel_sort(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
