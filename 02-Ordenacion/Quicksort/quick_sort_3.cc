// 2.11 --- Quicksort (version 3)
// Deja de partir cuando el subvector es "suficientemente pequenyo". Al final se
// hace una unica pasada de insertion sort sobre todo el vector: como ningun
// elemento esta a mas de `critical_size` posiciones de su sitio, esa pasada
// cuesta Theta(n).
//
// Coste: Theta(n log n) en el caso medio, con mejores constantes que la version 1.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
int partition (vector<elem>& v, int l, int r) {
    elem x = v[l];
    int i = l - 1;
    int j = r + 1;
    for (;;) {
        while (x < v[--j]);
        while (v[++i] < x);
        if (i >= j) return j;
        swap(v[i], v[j]);
    }
}

// Insertion sort sobre el rango v[l..r]. (El PDF lo usa pero no lo lista.)
template <typename elem>
void ins_sort (vector<elem>& v, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        elem x = v[i];
        int j;
        for (j = i; j > l and v[j - 1] > x; --j) {
            v[j] = v[j - 1];
        }
        v[j] = x;
    }
}

template <typename elem>
void quick_psort_3 (vector<elem>& v, int l, int r) {
    const int critical_size = 100;
    if (r - l >= critical_size) {
        int q = partition(v, l, r);
        quick_psort_3(v, l, q);
        quick_psort_3(v, q + 1, r);
    }
}

template <typename elem>
void quick_sort_3 (vector<elem>& v) {
    quick_psort_3(v, 0, v.size() - 1);
    ins_sort(v, 0, v.size() - 1);
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (not v.empty()) quick_sort_3(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
