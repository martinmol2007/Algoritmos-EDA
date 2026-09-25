// 6.5 --- Knight Jumps
// Se coloca un caballo en una casilla dada de un tablero de n x n. Escribir un
// algoritmo que determine si hay una manera de visitar todas las casillas del
// tablero moviendolo n^2 - 1 veces. (Es el "recorrido del caballo".)
//
// Backtracking: desde cada casilla se prueban los 8 saltos posibles. M[x][y]
// guarda el numero de paso en el que se visito la casilla, o -1 si no se ha
// visitado.
//
// try_it() hace tres cosas a la vez: comprobar que el salto cae dentro del
// tablero, que la casilla esta libre, y que aun no se ha encontrado solucion.

#include "../../00-Comun/eda.hh"

class KnightJumps {
    typedef matrix<int> board;

    int n;                  // number of rows and columns
    int ox,oy;              // origin
    bool found;             // a solution is found
    board M;                // current configuration
    board S;                // solution (if found)

    inline void try_it(int step, int x, int y) {
        if (not found and x >= 0 and x < n
            and y >= 0 and y < n and M[x][y] == -1) {
            M[x][y] = step + 1;
            recursive(step + 1, x, y);
            M[x][y] = -1;               // deshacer
        }
    }

    void recursive(int step, int x, int y) {
        if (step == n*n-1) {
            found = true;
            S = M;
        } else {
            try_it(step, x+2, y-1); try_it(step, x+2, y+1);
            try_it(step, x+1, y+2); try_it(step, x-1, y+2);
            try_it(step, x-2, y+1); try_it(step, x-2, y-1);
            try_it(step, x-1, y-2); try_it(step, x+1, y-2);
        }
    }

public:
    KnightJumps(int n, int ox, int oy) {
        this->n   = n;
        this->ox  = ox;
        this->oy  = oy;
        found     = false;
        M         = board(n, n, -1);
        M[ox][oy] = 0;
        recursive(0, ox, oy);
    }

    bool has_a_solution() {
        return found;
    }

    board solution() {
        return S;
    }
};

// ------------------------------------------------- Main program
// Entrada: n ox oy
// Se puede encontrar una solucion para 6x6 empezando en 0 1 (tarda un rato).
// Para 5x5 empezando en 0 0 es instantaneo.
//
// NOTA: el main del PDF escribe `kj.has_a_solution()` (o sea, un 1), que no
// aporta nada; aqui se escribe el tablero con el orden de los saltos.
int main () {
    int n,ox,oy;
    cin >> n >> ox >> oy;
    KnightJumps kj(n,ox,oy);
    if (kj.has_a_solution()) cout << kj.solution();
    else                     cout << "no hay solucion" << endl;
}
