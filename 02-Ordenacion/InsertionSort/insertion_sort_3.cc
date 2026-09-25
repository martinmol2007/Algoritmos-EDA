// 2.4 --- Insertion Sort (version 3)
// Para evitar el test "j > 0" en cada iteracion, coloca primero el elemento mas
// pequenyo en la primera posicion: actua como centinela.
//
// Coste: O(n^2) en el caso peor y medio, Theta(n) si el vector ya esta ordenado.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
int pos_min (vector<elem>& v, int l, int r) {
    int p = l;
    for (int j = l + 1; j <= r; ++j) {
        if (v[j] < v[p]) {
            p = j;
    }   }
    return p;
}

template <typename elem>
void ins_sort_3 (vector<elem>& v) {
    int n = v.size();
    swap(v[0], v[pos_min(v, 0, n-1)]);
    for (int i = 2; i < n; ++i) {
        elem x = v[i];
        int j;
        for (j = i; v[j - 1] > x; --j) {
            v[j] = v[j - 1];
        }
        v[j] = x;
}   }

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (not v.empty()) ins_sort_3(v);   // ojo: la version del PDF supone v no vacio
    for (int y : v) cout << y << " ";
    cout << endl;
}
