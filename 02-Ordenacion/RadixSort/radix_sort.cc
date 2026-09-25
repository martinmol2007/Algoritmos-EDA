// EXTRA (no esta en el PDF) --- Radix Sort (LSD, base 256)
// Ordena enteros digito a digito, del menos significativo al mas significativo,
// usando counting sort (estable) en cada pasada.
//
// Coste: Theta(d * (n + b)) con d = numero de digitos y b = base.
// Para enteros de 32 bits en base 256 son 4 pasadas: Theta(n) en la practica.
// Memoria auxiliar: Theta(n + b).  Es estable.

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Ordena enteros NO negativos.
void radix_sort_no_neg (vector<int>& v) {
    if (v.empty()) return;
    const int B = 256;                 // base
    vector<int> out(v.size());
    int maxv = *max_element(v.begin(), v.end());

    for (int shift = 0; (maxv >> shift) > 0; shift += 8) {
        vector<int> cnt(B, 0);
        for (int x : v) ++cnt[(x >> shift) & (B-1)];
        for (int i = 1; i < B; ++i) cnt[i] += cnt[i-1];
        for (int i = int(v.size()) - 1; i >= 0; --i) {
            out[--cnt[(v[i] >> shift) & (B-1)]] = v[i];
        }
        v = out;
    }
}

// Version general: separa negativos y positivos.
void radix_sort (vector<int>& v) {
    vector<int> neg, pos;
    for (int x : v) (x < 0 ? neg : pos).push_back(x);
    for (int& x : neg) x = -x;         // los pasamos a positivos
    radix_sort_no_neg(neg);
    radix_sort_no_neg(pos);
    v.clear();
    for (int i = int(neg.size()) - 1; i >= 0; --i) v.push_back(-neg[i]);
    for (int x : pos) v.push_back(x);
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    radix_sort(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
