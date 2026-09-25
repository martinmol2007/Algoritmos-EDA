// 2.9 --- Quicksort con particion de Hoare (version 1)
// El pivote es siempre el primer elemento del subvector.
//
// Coste: Theta(n log n) en el caso medio, Theta(n^2) en el caso peor
// (por ejemplo, con un vector ya ordenado). Memoria auxiliar: la pila de
// recursion, O(n) en el peor caso. No es estable.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
int partition (vector<elem>& v, int l, int r);

template <typename elem>
void quick_sort_1 (vector<elem>& v, int l, int r) {
    if (l < r) {
        int q = partition(v, l, r);
        quick_sort_1(v, l, q);
        quick_sort_1(v, q + 1, r);
}   }

template <typename elem>
void quick_sort_1 (vector<elem>& v) {
    quick_sort_1(v, 0, v.size() - 1);
}

// Particion de Hoare: reordena v[l..r] y devuelve q tal que
// todo v[l..q] <= pivote <= todo v[q+1..r].
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
}   }

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (not v.empty()) quick_sort_1(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
