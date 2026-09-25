// 6.4 --- Latin Squares
// Un cuadrado latino de orden n es una tabla n x n en la que cada casilla esta
// coloreada con uno de n colores, de forma que ninguna fila ni ninguna columna
// contiene un color repetido. Escribir un algoritmo que escriba todos los
// cuadrados latinos de orden n.
//
// Backtracking casilla a casilla (cas = i*n + j) con marcaje de colores libres
// por fila (F) y por columna (C): comprobar si un color cabe cuesta Theta(1).
//
// OJO: el numero de cuadrados latinos crece brutalmente (1, 2, 12, 576, 161280,
// 812851200...). Con n >= 5 ya no acaba en un tiempo razonable si los escribe
// todos.

#include "../../00-Comun/eda.hh"

class LatinSquare {
    int n;              // number of rows and columns
    matrix<int> Q;      // the latin square
    matrix<boolean> F;  // F[i][c] = c is allowed in row i
    matrix<boolean> C;  // C[j][c] = c is allowed in column j

    void recursive(int cas) {
        if (cas == n*n) {
            cout << Q << endl;
        } else {
            int i = cas/n;
            int j = cas%n;
            for (int c = 0; c < n; ++c) {
                if (F[i][c] and C[j][c]) {
                    Q[i][j] = c;
                    F[i][c] = C[j][c] = false;
                    recursive(cas+1);
                    F[i][c] = C[j][c] = true;   // deshacer
                }
            }
        }
    }

public:
    LatinSquare(int n) {
        this->n = n;
        Q       = matrix<int>(n, n);
        F       = matrix<boolean>(n, n, true);
        C       = matrix<boolean>(n, n, true);
        recursive(0);
    }
};

// ------------------------------------------------- Main program
// Entrada: n (prueba con 3 o 4)
int main () {
    int n = readint();
    LatinSquare qll(n);
}
