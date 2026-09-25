// 2.7 --- Mergesort (version 2)
// Corta la recursion cuando el subvector es "suficientemente pequenyo" y en ese
// punto usa insertion sort, que sobre trozos cortos es mas rapido (menos
// constantes ocultas y menos llamadas recursivas).
//
// Coste: Theta(n log n), pero con mejores constantes que la version 1.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
void merge (vector<elem>& v, int l, int m, int r);
template <typename elem>
void ins_sort (vector<elem>& v, int l, int r);

template <typename elem>
void merge_sort_2 (vector<elem>& v, int l, int r) {
    const int critical_size = 50;
    if (r - l < critical_size) {
        ins_sort(v, l, r);
    } else {
        int m = (l + r) / 2;
        merge_sort_2(v, l, m);
        merge_sort_2(v, m + 1, r);
        merge(v, l, m, r);
    }
}

template <typename elem>
void merge_sort_2 (vector<elem>& v) {
    merge_sort_2(v, 0, v.size() - 1);
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
    if (not v.empty()) merge_sort_2(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
