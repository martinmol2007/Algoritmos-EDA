// 1.5 --- Priority queues with inverted order
// (Un metodo alternativo es invertir el signo de los elementos.)
// Lee una secuencia de numeros y la escribe en orden creciente. El parametro
// importante es el tercero, pero hay que dar tambien el segundo.
#include <queue>
#include <iostream>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> pq;
    int x;
    while (cin >> x) pq.push(x);
    while (not pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
}   }
