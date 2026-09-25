// EXTRA (no esta en el PDF) --- Mochila 0/1 por programacion dinamica
// El mismo problema que 07-Backtracking/Mochila, pero con pesos ENTEROS.
//
// Subproblema:
//   dp[i][c] = valor maximo usando solo los objetos 0..i-1 con capacidad c
//
// Recurrencia:
//   dp[i][c] = max( dp[i-1][c],                        // no coger el objeto i-1
//                   dp[i-1][c-p[i-1]] + v[i-1] )       // cogerlo (si cabe)
//
// Coste: Theta(n*C) de tiempo.  Memoria: Theta(n*C), o Theta(C) con la version
// optimizada (que no permite reconstruir que objetos se han cogido).
//
// OJO: Theta(n*C) es PSEUDOPOLINOMICO, no polinomico: C se codifica con log(C)
// bits, asi que el coste es exponencial en el tamanyo de la entrada. La mochila
// 0/1 sigue siendo NP-dificil.

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Version con tabla completa: permite reconstruir la solucion.
int mochila (const vector<int>& p, const vector<int>& v, int C,
             vector<bool>& cogidos) {
    int n = p.size();
    vector<vector<int>> dp(n+1, vector<int>(C+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= C; ++c) {
            dp[i][c] = dp[i-1][c];                   // no coger el objeto i-1
            if (p[i-1] <= c) {
                dp[i][c] = max(dp[i][c], dp[i-1][c - p[i-1]] + v[i-1]);
    }   }   }

    // Reconstruccion: se va hacia atras viendo si dp[i][c] cambio respecto a
    // dp[i-1][c]. Si cambio, el objeto i-1 se cogio.
    cogidos.assign(n, false);
    int c = C;
    for (int i = n; i >= 1; --i) {
        if (dp[i][c] != dp[i-1][c]) {
            cogidos[i-1] = true;
            c -= p[i-1];
    }   }

    return dp[n][C];
}

// Version optimizada en memoria: Theta(C).
// El bucle de c va HACIA ATRAS para no usar dos veces el mismo objeto
// (si fuera hacia delante, seria la mochila con repeticiones).
int mochila_memoria_lineal (const vector<int>& p, const vector<int>& v, int C) {
    int n = p.size();
    vector<int> dp(C+1, 0);
    for (int i = 0; i < n; ++i) {
        for (int c = C; c >= p[i]; --c) {
            dp[c] = max(dp[c], dp[c - p[i]] + v[i]);
    }   }
    return dp[C];
}

// ------------------------------------------------------------------- demo
// Entrada:  n C   seguido de n pares "peso valor".
//
// Ejemplo:
//   4 10
//   5 10
//   4 40
//   6 30
//   3 50
int main() {
    int n, C;
    cin >> n >> C;
    vector<int> p(n), v(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> v[i];

    vector<bool> cogidos;
    int best = mochila(p, v, C, cogidos);

    cout << "valor maximo = " << best << endl;
    cout << "objetos      = ";
    for (int i = 0; i < n; ++i) if (cogidos[i]) cout << i << " ";
    cout << endl;
    cout << "peso usado   = ";
    int peso = 0;
    for (int i = 0; i < n; ++i) if (cogidos[i]) peso += p[i];
    cout << peso << " / " << C << endl;

    cout << "(memoria lineal) valor maximo = "
         << mochila_memoria_lineal(p, v, C) << endl;
}
