// 2.6 --- Mergesort (version 1)
// Divide y venceras clasico: parte el vector por la mitad, ordena cada mitad
// recursivamente y fusiona (merge) las dos mitades ordenadas.
//
// Coste: Theta(n log n) en todos los casos.  Memoria auxiliar: Theta(n).
// Es estable.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
void merge (vector<elem>& v, int l, int m, int r);

template <typename elem>
void merge_sort_1 (vector<elem>& v, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_1(v, l, m);
        merge_sort_1(v, m + 1, r);
        merge(v, l, m, r);
    }
}

template <typename elem>
void merge_sort_1 (vector<elem>& v) {
    merge_sort_1(v, 0, v.size() - 1);
}

// Fusiona v[l..m] y v[m+1..r], ambos ya ordenados. Coste: Theta(r-l+1).
template <typename elem>
void merge (vector<elem>& v, int l, int m, int r) {
    vector<elem> b(r - l + 1);
    int i = l,  j = m + 1,  k = 0;
    while (i <= m and j <= r) {
        if (v[i] <= v[j]) b[k++] = v[i++];
        else b[k++] = v[j++];
    }
    while (i <= m) b[k++] = v[i++];
    while (j <= r) b[k++] = v[j++];
    for (k = 0; k <= r - l; ++k) v[l + k] = b[k];
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (not v.empty()) merge_sort_1(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
