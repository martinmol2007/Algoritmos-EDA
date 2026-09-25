// EXTRA (no esta en el PDF) --- Busqueda lineal (secuencial)
// Recorre el vector de izquierda a derecha hasta encontrar el elemento.
// Es el unico metodo posible si el vector NO esta ordenado.
//
// Coste: Theta(n) en el caso peor, Theta(n) en el caso medio (n/2 comparaciones
//        si el elemento esta, n si no esta), Theta(1) en el mejor caso.

#include <vector>
#include <iostream>
using namespace std;

// Devuelve la posicion de x en v, o -1 si no esta.
template <typename elem>
int busqueda_lineal (const vector<elem>& v, const elem& x) {
    for (int i = 0; i < int(v.size()); ++i) {
        if (v[i] == x) return i;
    }
    return -1;
}

// Variante con centinela: evita comprobar el limite del vector en cada vuelta.
// Cuesta lo mismo asintoticamente, pero hace la mitad de comparaciones por
// iteracion. Necesita una copia del vector con espacio para el centinela.
template <typename elem>
int busqueda_lineal_centinela (vector<elem> v, const elem& x) {
    int n = v.size();
    v.push_back(x);                 // centinela: garantiza que se encuentra
    int i = 0;
    while (v[i] != x) ++i;
    return i < n ? i : -1;
}

// ------------------------------------------------------------------- demo
// Entrada: primero el elemento buscado, despues la secuencia.
int main() {
    int x;
    cin >> x;
    vector<int> v;
    int y;
    while (cin >> y) v.push_back(y);
    cout << busqueda_lineal(v, x) << endl;
    cout << busqueda_lineal_centinela(v, x) << endl;
}
