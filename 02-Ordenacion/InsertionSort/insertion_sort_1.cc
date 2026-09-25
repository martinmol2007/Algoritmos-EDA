// 2.2 --- Insertion Sort (version 1)
// Version basica: hace intercambios hasta colocar v[i] en su sitio.
//
// Coste: O(n^2) en el caso peor y medio, Theta(n) si el vector ya esta ordenado.

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
void ins_sort_1 (vector<elem>& v) {
    int n = v.size();
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 and v[j - 1] > v[j]; --j) {
            swap(v[j - 1], v[j]);
}   }   }

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    ins_sort_1(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
