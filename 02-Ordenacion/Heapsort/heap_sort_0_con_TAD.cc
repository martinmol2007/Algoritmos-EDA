// 2.12 --- Heapsort usando el TAD cola de prioridad (version 1)
// Mete todos los elementos en una priority_queue y los va sacando. Como la
// priority_queue de la STL es un max-heap, los elementos salen de mayor a menor
// y se colocan de derecha a izquierda.
//
// Coste: Theta(n log n).  Memoria auxiliar: Theta(n) (la cola de prioridad).

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

template <typename elem>
void heap_sort_0 (vector<elem>& v) {
    int n = v.size();
    priority_queue<elem> pq;
    for (int i = 0; i < n; ++i) {
        pq.push(v[i]);
    }
    for (int i = n-1; i >= 0; --i) {
        v[i] = pq.top();
        pq.pop();
    }
}

// ------------------------------------------------------------------- demo
int main() {
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    heap_sort_0(v);
    for (int y : v) cout << y << " ";
    cout << endl;
}
