// 1.2 --- Stacks: stack
// Lee una secuencia de numeros y la escribe al reves.
#include <stack>
#include <iostream>
using namespace std;

int main() {
    stack<int> s;
    int x;
    while (cin >> x) s.push(x);
    while (not s.empty()) {
        cout << s.top() << endl;
        s.pop();
}   }
