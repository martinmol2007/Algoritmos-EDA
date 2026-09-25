// 6.1 --- n Queens (version 1)
// Escribir un algoritmo que escriba todas las maneras posibles de colocar n
// reinas en un tablero de ajedrez de n x n de forma que ninguna reina amenace a
// otra.
//
// Primera version (ingenua): coloca una reina en cada fila y, tras cada
// colocacion, comprueba la legalidad recorriendo TODAS las reinas anteriores.
//
// Coste de legal(): Theta(i).  El arbol de busqueda tiene O(n^n) nodos, podado
// por legal().

#include "../../00-Comun/eda.hh"

class NQueens {
    int n;                  // number of queens
    vector<int> T;          // current configuration

    void recursive(int i) {
        if (i==n) {
            write();
        } else {
            for (int j = 0; j < n; ++j) {
                T[i] = j;
                if (legal(i)) {
                    recursive(i+1);
                }
            }
        }
    }

    // Indicates if the configuration with queens 0..i is legal
    // knowing that the configuration with queens 0..i-1 is.
    bool legal(int i) {
        for (int k = 0; k < i; ++k) {
            if (T[k]==T[i] or T[i]-i==T[k]-k or T[i]+i==T[k]+k) {
                return false;
            }
        }
        return true;
    }

    void write() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << (T[i]==j ? "O " : "* ") ;
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    NQueens(int n) {
        this->n = n;
        T = vector<int>(n);
        recursive(0);
    }
};

// ------------------------------------------------- Main program
// Entrada: n (por ejemplo, 6)
int main() {
    int n = readint();
    NQueens r(n);
}
