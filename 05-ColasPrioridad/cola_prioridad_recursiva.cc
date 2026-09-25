// 4.1 --- Priority queue. Recursive implementation.
// Cola de prioridad de MINIMOS implementada como un heap sobre un vector.
//
// Un heap es un arbol binario completo con la propiedad de que el valor de cada
// nodo es menor o igual que los valores de los nodos de sus subarboles. Un heap
// de n elementos se implementa comodamente en las posiciones 1 a n. Un elemento
// en la posicion i con 1 <= i <= n tiene su hijo izquierdo en la posicion 2i si
// 2i <= n, su hijo derecho en la posicion 2i+1 si 2i+1 <= n, y su padre en la
// posicion floor(i/2) si i > 1. Por comodidad, la tabla incluye una posicion 0
// que no se usa.
//
// Abajo, n denota la talla de la cola de prioridad. Para el analisis se supone
// que anyadir un elemento al final de una tabla tiene coste constante (lo cual
// no es del todo cierto: es coste constante amortizado).
//
// ERRATA DEL PDF: el constructor aparece como `CuaPrio()` (nombre catalan de una
// version anterior) dentro de la clase `PriorityQueue`. Aqui se corrige.

#include <vector>
#include <iostream>
using namespace std;

template <typename Elem>
class PriorityQueue {

private:
    vector<Elem> v;     // Table for the heap (position 0 is not used)

public:
    // -------------------------------------- Constructor. Coste: Theta(1).
    PriorityQueue () {
        v.push_back(Elem());
    }

    // ------------------------------ Inserta un elemento. Coste: Theta(log n).
    void insert (const Elem& x) {
        v.push_back(x);
        shift_up(size());
    }

    // -------------- Borra y devuelve el elemento minimo. Coste: Theta(log n).
    Elem remove_min () {
        if (empty()) throw "Priority queue is empty";
        Elem x = v[1];
        v[1] = v.back();
        v.pop_back();
        shift_down(1);
        return x;
    }

    // ------------------------- Devuelve el elemento minimo. Coste: Theta(1).
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

private:
    // Sube un nodo por el arbol mientras haga falta.
    void shift_up (int i) {
        if (i != 1 and v[i/2] > v[i]) {
            swap(v[i], v[i/2]);
            shift_up(i/2);
        }
    }

    // Hunde un nodo por el arbol mientras haga falta.
    void shift_down (int i) {
        int n = size();
        int c = 2*i;
        if (c <= n) {
            if (c+1 <= n and v[c+1] < v[c]) c++;
            if (v[i] > v[c]) {
                swap(v[i],v[c]);
                shift_down(c);
            }
        }
    }
};

// ------------------------------------------------------------------- demo
// Lee una secuencia de numeros y la escribe en orden creciente.
int main() {
    PriorityQueue<int> pq;
    int x;
    while (cin >> x) pq.insert(x);
    while (not pq.empty()) cout << pq.remove_min() << " ";
    cout << endl;
}
