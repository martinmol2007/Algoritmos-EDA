// 4.2 --- Priority queue. Iterative implementation.
// La misma cola de prioridad de minimos que la version 4.1, pero con shift_up y
// shift_down escritos de forma iterativa y, sobre todo, DESPLAZANDO en vez de
// intercambiando: un swap son 3 asignaciones, un desplazamiento es 1.
// Es la misma optimizacion que la de insertion sort version 2.
//
// Costes identicos a la version recursiva: insert y remove_min en Theta(log n),
// minimum, size y empty en Theta(1).

#include <vector>
#include <iostream>
using namespace std;

template <typename Elem>
class PriorityQueue {

private:
    vector<Elem> v;       // Vector for the heap (position 0 is not used)

public:
    // -------------------------------------- Constructor. Coste: Theta(1).
    PriorityQueue () {
        v.push_back(Elem());
    }

    // ------------------------------ Inserta un elemento. Coste: Theta(log n).
    void insert (const Elem& x) {
        v.push_back(x);
        int i = size();
        while (i != 1 and v[i/2] > x) {
            v[i] = v[i/2];
            i = i/2;
        }
        v[i] = x;
    }

    // -------------- Borra y devuelve el elemento minimo. Coste: Theta(log n).
    Elem remove_min () {
        if (empty()) throw "Priority queue is empty";
        int n = size();
        Elem e = v[1],  x = v[n];
        v.pop_back();  --n;
        int i = 1,  c = 2*i;
        while (c <= n) {
            if (c+1 <= n and v[c+1] < v[c]) ++c;
            if (x <= v[c]) break;
            v[i] = v[c];
            i = c;
            c = 2*i;
        }
        v[i] = x;
        return e;
    }

    // ------------------------------------ Devuelve el minimo. Coste: Theta(1).
    Elem minimum () {
        if (empty()) throw "Priority queue is empty";
        return v[1];
    }

    // ------------------ Devuelve la talla de la cola de prioridad. Theta(1).
    int size () {
        return v.size() - 1;
    }

    // ------------------------------- Indica si la cola esta vacia. Theta(1).
    bool empty () {
        return size() == 0;
    }
};

// ------------------------------------------------------------------- demo
int main() {
    PriorityQueue<int> pq;
    int x;
    while (cin >> x) pq.insert(x);
    while (not pq.empty()) cout << pq.remove_min() << " ";
    cout << endl;
}
