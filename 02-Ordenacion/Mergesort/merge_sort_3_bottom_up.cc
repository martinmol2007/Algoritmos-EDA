// 2.8 --- Mergesort con fusion "bottom-up" (version 3)
// Sin recursion: fusiona primero trozos de tamanyo 1, luego de 2, de 4, ...
// hasta cubrir todo el vector.
//
// Coste: Theta(n log n).  Memoria auxiliar: Theta(n) (dentro de merge).

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

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

template <typename elem>
void merge_sort_bu (vector<elem>& v) {
    int n = v.size();
    for (int m = 1; m < n; m *= 2) {
        for (int i = 0; i < n - m; i += 2*m) {
            merge(v, i, i + m - 1, min(i + 2 * m - 1, n - 1));
}   }   }

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    merge_sort_bu(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
