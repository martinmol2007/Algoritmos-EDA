// 1.9 --- Unordered sets: unordered_set
// Lee dos secuencias de numeros acabadas en 0 y escribe su interseccion.
// Este codigo usa C++11.
#include <unordered_set>
#include <iostream>
#include <string>
using namespace std;

int main() {
    unordered_set<int> s1, s2;
    int x;
    cin >> x;
    while (x != 0) {
        s1.insert(x);
        cin >> x;
    }
    cin >> x;
    while (x != 0) {
        s2.insert(x);
        cin >> x;
    }
    for (auto x : s1) {
        if (s2.find(x) != s2.end()) cout << x << endl;
    }
}
