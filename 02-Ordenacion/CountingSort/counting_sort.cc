// EXTRA (no esta en el PDF) --- Counting Sort
// Ordenacion por conteo. No compara elementos: cuenta cuantas veces aparece cada
// valor y reconstruye el vector. Solo sirve para claves enteras dentro de un
// rango [minv..maxv] no demasiado grande.
//
// Coste: Theta(n + k), donde k = maxv - minv + 1.
// Memoria auxiliar: Theta(n + k).  Es estable (en esta version con prefijos).

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void counting_sort (vector<int>& v) {
    if (v.empty()) return;
    int minv = *min_element(v.begin(), v.end());
    int maxv = *max_element(v.begin(), v.end());
    int k = maxv - minv + 1;

    // 1) contar apariciones
    vector<int> cnt(k, 0);
    for (int x : v) ++cnt[x - minv];

    // 2) sumas prefijas: cnt[i] = cuantos elementos son <= minv+i
    for (int i = 1; i < k; ++i) cnt[i] += cnt[i-1];

    // 3) colocar de derecha a izquierda para mantener la estabilidad
    vector<int> out(v.size());
    for (int i = int(v.size()) - 1; i >= 0; --i) {
        out[--cnt[v[i] - minv]] = v[i];
    }
    v = out;
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    counting_sort(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
