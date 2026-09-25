// 6.8 --- Traveling Salesman Problem (problema del viajante)
// Un comercial debe visitar los clientes de n ciudades distintas. La distancia
// entre la ciudad i y la ciudad j es D[i][j]. Quiere salir de su ciudad, visitar
// una y solo una vez cada una de las otras, y volver al punto de partida,
// minimizando la distancia total del viaje.
//
// Backtracking con PODA sencilla: si el coste acumulado c ya supera el del mejor
// recorrido encontrado hasta ahora (best), no tiene sentido continuar.
//
//     if (c + M[v][u] < best) { ... }
//
// NOTA: el TSP es NP-dificil. Este algoritmo es Theta(n!) en el caso peor; la
// poda ayuda mucho en la practica pero no cambia el orden.

#include "../../00-Comun/eda.hh"

typedef matrix<double> distance_matrix;

class TSP {
    distance_matrix M;  // distance matrix
    int n;              // number of cities
    vector<int> s;      // next of each city (-1 if not yet used)
    vector<int> sol;    // best solution so far
    double best;        // cost of best solution so far

    void recursive (int v, int t, double c) {
        // v = last vertex in the path
        // t = length of the path
        // c = cost so far
        if (t == n) {
            c += M[v][0];               // cerrar el ciclo
            if (c < best) {
                best = c;
                sol = s;
                sol[v] = 0;
            }
        } else {
            for(int u = 0; u < n; ++u) if (u != v and s[u] == -1) {
                if (c + M[v][u] < best) {       // poda
                    s[v] = u;
                    recursive(u, t+1, c+M[v][u]);
                    s[v] = -1;                  // deshacer
    }   }   }   }

public:
    TSP(distance_matrix M) {
        this->M = M;
        n = M.rows();
        s = vector<int>(n, -1);
        sol = vector<int>(n);
        best = infinity;
        recursive(0, 1, 0);
    }

    vector<int> solution () {
        return sol;
    }

    int next(int x) {
        return sol[x];
    }

    double cost() {
        return best;
    }
};

// ------------------------------------------------- Main program
// Lee n, crea una matriz de distancias con ciudades colocadas al azar, resuelve
// el problema del viajante y escribe el coste de la mejor solucion.
// Prueba con n = 9 o 10; a partir de 12 empieza a tardar de verdad.
int main () {
    int n = readint();
    vector<double> x = randvector(n);
    vector<double> y = randvector(n);
    distance_matrix M = distance_matrix(n, n);
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            M[u][v] = sqrt((x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]));
    }   }
    double t = now();
    TSP tsp(M);
    t = now() - t;
    cout << "temps: " << t << endl;
    cout << tsp.cost() << endl;
    cout << tsp.solution() << endl;
}
