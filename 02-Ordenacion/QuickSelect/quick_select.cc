// EXTRA (no esta en el PDF) --- Quickselect (algoritmo de seleccion de Hoare)
// Devuelve el k-esimo elemento mas pequenyo (k contando desde 0) sin ordenar todo
// el vector. Es quicksort pero bajando por una sola rama.
//
// Coste: Theta(n) en el caso medio (n + n/2 + n/4 + ... = 2n),
//        Theta(n^2) en el caso peor. Con pivote aleatorio el peor es improbable.
// Memoria auxiliar: Theta(1) (esta version es iterativa).

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

inline int randint(int a, int b) { return a + rand() % (b - a + 1); }

// Particion de Lomuto: deja el pivote en su posicion final y la devuelve.
template <typename elem>
int partition_lomuto (vector<elem>& v, int l, int r) {
    swap(v[randint(l, r)], v[r]);      // pivote aleatorio al final
    elem x = v[r];
    int i = l;
    for (int j = l; j < r; ++j) {
        if (v[j] < x) swap(v[i++], v[j]);
    }
    swap(v[i], v[r]);
    return i;
}

// Devuelve el elemento que ocuparia la posicion k si v estuviera ordenado.
// OJO: modifica v (lo reordena parcialmente).
template <typename elem>
elem quick_select (vector<elem>& v, int k) {
    int l = 0, r = v.size() - 1;
    while (true) {
        if (l == r) return v[l];
        int q = partition_lomuto(v, l, r);
        if (k == q)      return v[q];
        else if (k < q)  r = q - 1;
        else             l = q + 1;
    }
}

// ------------------------------------------------------------------- demo
// Entrada: primero k, despues la secuencia de numeros.
int main() {
    int k;
    cin >> k;
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    if (k < 0 or k >= int(v.size())) {
        cout << "k fuera de rango" << endl;
        return 1;
    }
    cout << quick_select(v, k) << endl;
}
