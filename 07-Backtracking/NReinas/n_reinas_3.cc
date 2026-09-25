// 6.3 --- n Queens (version 3)
// Igual que la version 2, pero busca UNA sola solucion en vez de todas.
// El flag `found` corta la busqueda: en cuanto se encuentra una solucion, los
// bucles pendientes dejan de iterar (`j < n and not found`) y la recursion se
// desenrolla sin explorar nada mas.

#include "../../00-Comun/eda.hh"

class NQueens {
    int n;                  // number of queens
    vector<int> T;          // current configuration
    bool found;             // indicates if a solution has been found
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
            found = true;
            write();
        } else {
            for (int j = 0; j < n and not found; ++j) {
                if (not mc[j] and not md1[diag1(i, j)]
                    and not md2[diag2(i, j)]) {
                    T[i] = j;
                    mc[j] = true;
                    md1[diag1(i, j)] = true;
                    md2[diag2(i, j)] = true;
                    recursive(i+1);
                    mc[j] = false;
                    md1[diag1(i, j)] = false;
                    md2[diag2(i, j)] = false;
                }
            }
        }
    }

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
        found  = false;
        recursive(0);
    }
};

// ------------------------------------------------- Main program
int main() {
    int n = readint();
    NQueens r(n);
}
