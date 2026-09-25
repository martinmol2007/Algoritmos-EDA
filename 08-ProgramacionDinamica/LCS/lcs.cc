// EXTRA (no esta en el PDF) --- Subsecuencia comun mas larga (LCS)
// Dadas dos cadenas, encontrar la subsecuencia (no necesariamente contigua) mas
// larga que aparece en las dos.
//
//   A = "AGGTAB"
//   B = "GXTXAYB"
//   LCS = "GTAB" (longitud 4)
//
// Subproblema:
//   dp[i][j] = longitud de la LCS de A[0..i-1] y B[0..j-1]
//
// Recurrencia:
//   si A[i-1] == B[j-1]:  dp[i][j] = dp[i-1][j-1] + 1
//   si no:                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
//
// Coste: Theta(n*m) de tiempo y de memoria.
//
// Es la base del comando `diff`, de los sistemas de control de versiones y de
// la comparacion de secuencias de ADN.

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int lcs (const string& A, const string& B, string& subsecuencia) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    // Reconstruccion hacia atras desde dp[n][m].
    subsecuencia.clear();
    int i = n, j = m;
    while (i > 0 and j > 0) {
        if (A[i-1] == B[j-1])            { subsecuencia += A[i-1]; --i; --j; }
        else if (dp[i-1][j] >= dp[i][j-1]) --i;
        else                               --j;
    }
    reverse(subsecuencia.begin(), subsecuencia.end());

    return dp[n][m];
}

// Version solo-longitud con memoria Theta(min(n,m)).
int lcs_memoria_lineal (const string& A, const string& B) {
    int n = A.size(), m = B.size();
    vector<int> prev(m+1, 0), cur(m+1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i-1] == B[j-1]) cur[j] = prev[j-1] + 1;
            else                  cur[j] = max(prev[j], cur[j-1]);
        }
        swap(prev, cur);
    }
    return prev[m];
}

// ------------------------------------------------------------------- demo
// Entrada: dos cadenas, una por linea.
int main() {
    string A, B;
    if (not (cin >> A >> B)) { A = "AGGTAB"; B = "GXTXAYB"; }

    string sub;
    int len = lcs(A, B, sub);
    cout << "A   = " << A << endl;
    cout << "B   = " << B << endl;
    cout << "LCS = " << sub << "  (longitud " << len << ")" << endl;
    cout << "(memoria lineal) longitud = " << lcs_memoria_lineal(A, B) << endl;
}
