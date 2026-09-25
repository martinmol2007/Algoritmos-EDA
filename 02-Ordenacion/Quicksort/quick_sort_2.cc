// 2.10 --- Quicksort (version 2)
// El pivote se escoge al azar y se lleva a la primera posicion. Asi el caso peor
// deja de depender de la entrada: ningun input concreto puede provocarlo
// sistematicamente.
//
// Coste: Theta(n log n) esperado, Theta(n^2) en el caso peor (muy improbable).

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

// Entero aleatorio en [a..b] (esta en eda.hh, se replica para ser autonomo).
inline int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}

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

template <typename elem>
void quick_sort_2 (vector<elem>& v, int l, int r) {
    if (l < r) {
        int p = randint(l, r);
        swap(v[l], v[p]);
        int q = partition(v, l, r);
        quick_sort_2(v, l, q);
        quick_sort_2(v, q + 1, r);
    }
}

template <typename elem>
void quick_sort_2 (vector<elem>& v) {
    quick_sort_2(v, 0, v.size() - 1);
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (not v.empty()) quick_sort_2(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
