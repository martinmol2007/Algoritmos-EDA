// 6.9 --- Knapsack (version 1)
// Tenemos una mochila que aguanta hasta C unidades de peso y hasta n objetos. El
// objeto i-esimo tiene peso p[i] y valor v[i]. El objetivo es escoger que
// objetos meter en la mochila de forma que la suma de sus valores sea maxima,
// con la restriccion de que la suma de sus pesos no supere C. Los objetos no se
// pueden partir.
//
// Solucion por backtracking SIN cota inferior: para cada objeto se prueban las
// dos opciones (cogerlo / no cogerlo). El arbol de busqueda es binario y tiene
// 2^n hojas.
//
// Coste: Theta(2^n).

#include "../../00-Comun/eda.hh"

class Knapsack {
    int n;                  // number of objects
    vector<double> p;       // weights
    vector<double> v;       // values
    double C;               // weight capacity
    vector<boolean> s;      // current solution
    vector<boolean> sol;    // best solution so far
    double best;            // value of the best solution so far

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
            if (pes+p[i] <= C) {
                s[i] = true;
                recursive(i+1, val+v[i], pes+p[i]);
            }
            // 2nd option: do not take object i
            s[i] = false;
            recursive(i+1, val, pes);
    }   }

public:
    Knapsack(int n, vector<double> p, vector<double> v, double C) {
        this->n = n;
        this->p = p;
        this->v = v;
        this->C = C;
        s = sol = vector<boolean>(n);
        best  = 0;
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
// Lee el numero de objetos, genera pesos y valores al azar, pone la capacidad a
// 0.4 veces el numero de objetos, resuelve y escribe la solucion.
int main () {
    int n = readint();
    vector<double> p = randvector(n);
    vector<double> v = randvector(n);
    double C = 0.4*n;
    cout << v << endl << p << endl << C << endl;
    Knapsack k(n, p, v, C);
    cout << k.value() << endl;
    cout << k.solution() << endl;
}
