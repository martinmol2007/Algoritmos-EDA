// 2.3 --- Insertion Sort (version 2)
// Evita la cadena de swaps: en vez de intercambiar, desplaza los elementos hacia
// la derecha (pasa de 3 asignaciones por iteracion a 1).
//
// Coste: O(n^2) en el caso peor y medio, Theta(n) si el vector ya esta ordenado.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
void ins_sort_2 (vector<elem>& v) {
    int n = v.size();
    for (int i = 1; i < n; ++i) {
        elem x = v[i];
        int j;
        for (j = i; j > 0 and v[j - 1] > x; --j) {
            v[j] = v[j - 1];
        }
        v[j] = x;
    }
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    ins_sort_2(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
