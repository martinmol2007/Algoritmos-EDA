// 2.5 --- Bubblesort
// Ordenacion por burbuja: recorre el vector de derecha a izquierda intercambiando
// parejas desordenadas, de forma que el minimo "burbujea" hasta la posicion i.
//
// Coste: Theta(n^2) en todos los casos (esta version no detecta si ya esta ordenado).

#include <vector>
#include <iostream>
using namespace std;

template <typename elem>
void bubble_sort (vector<elem>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 1; j > i; --j) {
            if (v[j - 1] > v[j]) {
                swap(v[j - 1], v[j]);
            }
        }
    }
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    bubble_sort(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
