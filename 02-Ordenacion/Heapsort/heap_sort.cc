// 2.13 --- Heapsort (version 2, in-place)
// Primero convierte el vector en un max-heap (make_heap, coste Theta(n)) y luego
// n-1 veces intercambia la raiz (el maximo) con el ultimo elemento del heap y
// rehunde la nueva raiz.
//
// Coste: Theta(n log n) en todos los casos.  Memoria auxiliar: Theta(1).
// No es estable.

#include <vector>
#include <iostream>
using namespace std;

// Hunde v[i] dentro del heap v[0..n-1].
template <typename elem>
void sink (vector<elem>& v, int n, int i) {
    elem x = v[i];
    int c = 2*i + 1;
    while (c < n) {
        if (c+1 < n and v[c] < v[c + 1]) c++;
        if (x >= v[c]) break;
        v[i] = v[c];
        i = c;
        c = 2*i + 1;
    }
    v[i] = x;
}

// Convierte v en un max-heap. Coste: Theta(n).
template <typename elem>
void make_heap (vector<elem>& v) {
    int n = v.size();
    for (int i = n/2 - 1; i >= 0; i--) {
        sink(v, n, i);
    }
}

template <typename elem>
void heap_sort (vector<elem>& v) {
    int n = v.size();
    make_heap(v);
    for (int i = n - 1; i >= 1; --i) {
        swap(v[0], v[i]);
        sink(v, i, 0);
    }
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    heap_sort(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
