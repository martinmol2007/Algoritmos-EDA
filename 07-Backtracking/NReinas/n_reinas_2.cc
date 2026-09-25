// 6.2 --- n Queens (version 2)
// La misma solucion, pero menos ingenua: en vez de comprobar la legalidad
// recorriendo las reinas anteriores, MARCA las columnas y las dos diagonales
// ocupadas. Comprobar si una casilla es valida pasa a costar Theta(1).
//
// diag1(i,j) = n-j-1+i  identifica la diagonal "/"
// diag2(i,j) = i+j      identifica la diagonal "\"
// Hay 2n-1 diagonales de cada tipo.
//
// Las marcas se ponen antes de la llamada recursiva y se QUITAN despues: ese
// deshacer es la esencia del backtracking.

#include "../../00-Comun/eda.hh"

class NQueens {
    int n;                  // number of queens
    vector<int> T;          // current configuration
    vector<boolean> mc;     // column labeling
    vector<boolean> md1;    // diagonal 1 labeling
    vector<boolean> md2;    // diagonal 2 labeling

    inline int diag1(int i, int j) {
        return n-j-1 + i;
    }
    inline int diag2(int i, int j) {
        return i+j;
    }

    void recursive(int i) {
        if (i == n) {
            write();
        } else {
            for (int j = 0; j < n; ++j) {
                if (not mc[j] and not md1[diag1(i, j)]
                    and not md2[diag2(i, j)]) {
                    T[i] = j;
                    mc[j] = true;
                    md1[diag1(i, j)] = true;
                    md2[diag2(i, j)] = true;
                    recursive(i+1);
                    mc[j] = false;                  // deshacer
                    md1[diag1(i, j)] = false;
                    md2[diag2(i, j)] = false;
    }   }   }   }

    void write() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << (T[i] == j ? "O " : "* ") ;
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    NQueens(int n) {
        this->n = n;
        T   = vector<int>(n);
        mc  = vector<boolean>(n, false);
        md1 = vector<boolean>(2*n-1, false);
        md2 = vector<boolean>(2*n-1, false);
        recursive(0);
    }
};

// ------------------------------------------------- Main program
int main () {
    int n = readint();
    NQueens r(n);
}
