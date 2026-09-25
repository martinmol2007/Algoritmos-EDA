// EXTRA (no esta en el PDF) --- Busqueda binaria SOBRE LA RESPUESTA
// La busqueda binaria no necesita un vector: solo necesita un predicado
// MONOTONO, es decir, una propiedad que sea falsa hasta cierto punto y cierta a
// partir de el:
//
//       F F F F F V V V V V
//                 ^ queremos este punto
//
// Se busca binariamente sobre el RANGO DE RESPUESTAS posibles, no sobre datos.
//
// Ejemplo clasico: repartir n tablones entre k pintores minimizando el tiempo
// del que mas tarda. "Se puede hacer en tiempo T?" es monotono: si se puede con
// T, tambien con T+1.
//
// Coste: Theta(log(rango) * coste_del_predicado).

#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

// Se pueden repartir los tablones en <= k tramos contiguos de suma <= T?
bool se_puede (const vector<int>& tablones, int k, long long T) {
    int tramos = 1;
    long long suma = 0;
    for (int t : tablones) {
        if (t > T) return false;        // un tablon solo ya no cabe
        if (suma + t <= T) suma += t;
        else { ++tramos; suma = t; }
    }
    return tramos <= k;
}

long long minimo_tiempo (const vector<int>& tablones, int k) {
    // El intervalo de busqueda: [max(tablon), suma(tablones)]
    long long lo = 0, hi = 0;
    for (int t : tablones) { lo = max(lo, (long long)t); hi += t; }

    // Invariante: se_puede(hi) es cierto, se_puede(lo-1) es falso.
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (se_puede(tablones, k, mid)) hi = mid;
        else                            lo = mid + 1;
    }
    return lo;
}

// ------------------------------------------------------------------- demo
// Entrada: k, despues las longitudes de los tablones.
int main() {
    int k;
    cin >> k;
    vector<int> tablones;
    int t;
    while (cin >> t) tablones.push_back(t);
    cout << minimo_tiempo(tablones, k) << endl;
}
