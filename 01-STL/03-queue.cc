// 1.3 --- Queues: queue
// Lee una secuencia de numeros y la escribe en el mismo orden.
#include <queue>
#include <iostream>
using namespace std;

int main() {
    queue<int> q;
    int x;
    while (cin >> x) q.push(x);
    while (not q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
}
