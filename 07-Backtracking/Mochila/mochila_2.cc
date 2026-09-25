// 6.10 --- Knapsack (version 2)
// El mismo problema de la mochila, pero con PODA por cota superior: se tiene en
// cuenta la maxima aportacion de valor que podrian dar los objetos que quedan
// (aunque superen la capacidad).
//
// sv[i] = v[i] + v[i+1] + ... + v[n-1]   (sumas sufijas de los valores)
//
// Si val + sv[i] <= best, ni cogiendo TODO lo que queda se superaria la mejor
// solucion conocida: se poda la rama entera.
//
// Ordenar los objetos de forma inteligente (por valor/peso decreciente) mejoraria
// todavia mas el algoritmo, porque hace que `best` suba antes y pode mas.
//
// Coste: Theta(2^n) en el caso peor, pero en la practica muchisimo mejor que la
// version 1.

#include "../../00-Comun/eda.hh"

class Knapsack {
    int n;                  // number of objects
    vector<double> p;       // weights
    vector<double> v;       // values
    double C;               // capacity
    vector<boolean> s;      // current solution
    vector<boolean> sol;    // best solution so far
    double best;            // value of the best solution so far
    vector<double> sv;      // sum of values for the bound

    void recursive(int i, double val, double pes) {
        // i   = currently handled object
        // val = accumulated value
        // pes = accumulated weight
        if (i == n) {
            if (val > best) {
                best = val;
                sol = s;
            }
        } else {
            // 1st option: take object i
            if (pes+p[i] <= C and val+sv[i] > best) {
                s[i] = true;
                recursive(i+1, val+v[i], pes+p[i]);
            }
            // 2nd option: do not take object i
            if (val+sv[i+1] > best) {
                s[i] = false;
                recursive(i+1, val, pes);
            }
        }
    }

public:
    Knapsack(int n, vector<double> p, vector<double> v, double C) {
        this->n = n;
        this->p = p;
        this->v = v;
        this->C = C;
        s = sol = vector<boolean>(n);
        best    = 0;
        sv      = vector<double>(n+1);
        sv[n] = 0;
        for (int i = n-1; i >= 0; --i) {
            sv[i] = sv[i+1]+v[i];
        }
        recursive(0, 0, 0);
    }

    vector<boolean> solution() {
        return sol;
    }

    double value() {
        return best;
    }
};

// ------------------------------------------------- Main program
int main () {
    int n = readint();
    vector<double> p = randvector(n);
    vector<double> v = randvector(n);
    double C = 0.4*n;
    cout << v << endl << p << endl << C << endl;
    Knapsack k(n,p,v,C);
    cout << k.value() << endl;
    cout << k.solution() << endl;
}
