// 1.4 --- Priority queues: priority_queue
// Lee una secuencia de numeros y la escribe en orden decreciente.
#include <queue>
#include <iostream>
using namespace std;

int main() {
    priority_queue<int> pq;
    int x;
    while (cin >> x) pq.push(x);
    while (not pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
}   }
