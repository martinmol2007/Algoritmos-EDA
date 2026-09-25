// 6.6 --- Task Scheduling
// Un jefe tiene n trabajadores para n tareas. El tiempo que el trabajador i
// tarda en completar la tarea j viene dado por T[i][j]. Quiere asignar una tarea
// a cada trabajador minimizando el tiempo total.
//
// Backtracking CON PODA (branch and bound): antes de bajar por una rama se
// estima una COTA INFERIOR del coste que aun queda por pagar (bound) y, si
// t + T[worker][task] + bound >= best, la rama se descarta entera.
//
// bound(worker, task) = para cada trabajador que queda, el minimo de los tiempos
// de las tareas aun libres. Es optimista (ignora que dos trabajadores no pueden
// coger la misma tarea), y por eso es una cota inferior valida: nunca descarta
// una rama que pudiera contener el optimo.

#include "../../00-Comun/eda.hh"

typedef matrix<double> time_matrix;

class Scheduling {
    time_matrix T;         // time matrix
    int n;                 // number of tasks and workers
    vector<int> assig;     // assignment: each worker gets a task
    vector<boolean> done;  // for each task, indicates if taken
    vector<int> sol;       // best solution so far
    double best;           // cost of the best solution so far

    void recursive(int worker, double t) {
        // worker = index of the worker, t = accumulated time
        if (worker == n) {
            if (t < best) {
                best = t;
                sol = assig;
            }
        } else {
            for (int task = 0; task < n; ++task) {
                if (not done[task]) {
                    assig[worker] = task;
                    done[task] = true;
                    if (t + T[worker][task] + bound(worker, task) < best) {
                        recursive(worker+1, t + T[worker][task]);
                    }
                    done[task] = false;         // deshacer
                    assig[worker] = -1;
    }   }   }   }

    // Cota inferior del tiempo que falta por acumular.
    double bound(int worker, int task) {
        double f = 0;
        for (int i = worker+1; i < n; ++i) {
            double m = infinity;
            for (int j = 0; j < n; ++j) if (not done[j]) {
                m = min(m, T[i][j]);
            }
            f += m;
        }
        return f;
    }

public:
    Scheduling(time_matrix T) {
        this->T = T;
        n = T.rows();
        assig = vector<int>(n, -1);
        done = vector<boolean>(n, false);
        best = infinity;
        recursive(0, 0);
    }

    vector<int> solution() {
        return sol;
    }

    double cost() {
        return best;
    }
};

// ------------------------------------------------- Main program
// Lee n, crea una matriz de tiempos aleatoria, resuelve y escribe la solucion.
int main () {
    int n = readint();
    time_matrix M = randmatrix(n);
    cout << M;
    Scheduling tasks(M);
    cout << tasks.cost() << endl;
    cout << tasks.solution() << endl;
}
