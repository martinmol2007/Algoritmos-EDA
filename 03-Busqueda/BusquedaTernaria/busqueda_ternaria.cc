// EXTRA (no esta en el PDF) --- Busqueda ternaria
// Encuentra el maximo (o el minimo) de una funcion UNIMODAL: una funcion que
// crece hasta un pico y despues decrece (o al reves).
//
/*         /\
          /  \          <- unimodal: sirve
         /    \                                                             */
//
// No sirve para funciones con varios picos.
//
// Idea: se parte el intervalo en tres con dos puntos m1 < m2.
//   - si f(m1) < f(m2), el maximo esta en [m1, r]  -> l = m1
//   - si no,            el maximo esta en [l, m2]  -> r = m2
// Cada vuelta descarta un tercio del intervalo.
//
// Coste: Theta(log_{3/2} n) = Theta(log n).

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// ---- version continua (sobre reales) ----
// Devuelve el x que maximiza f en [l, r], con precision eps.
template <typename Func>
double ternaria_real (Func f, double l, double r, double eps = 1e-9) {
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;
        else               r = m2;
    }
    return (l + r) / 2;
}

// ---- version discreta (sobre un vector unimodal) ----
// Devuelve la posicion del maximo de v, que se supone unimodal.
int ternaria_vector (const vector<int>& v) {
    int l = 0, r = int(v.size()) - 1;
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (v[m1] < v[m2]) l = m1 + 1;
        else               r = m2;
    }
    int best = l;
    for (int i = l; i <= r; ++i) if (v[i] > v[best]) best = i;
    return best;
}

// ------------------------------------------------------------------- demo
int main() {
    // Maximo de -(x-3)^2 + 7, que esta en x = 3.
    auto f = [](double x) { return -(x-3)*(x-3) + 7; };
    cout << "maximo continuo en x = " << ternaria_real(f, -100, 100) << endl;

    vector<int> v = {1, 3, 6, 9, 12, 8, 5, 2};
    int p = ternaria_vector(v);
    cout << "maximo del vector en la posicion " << p << " (valor " << v[p] << ")" << endl;
}
