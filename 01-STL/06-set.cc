// 1.6 --- Sets: set
// Lee dos secuencias de numeros acabadas en 0 y escribe su interseccion.
#include <set>
#include <iostream>
#include <string>
using namespace std;

int main() {
    set<int> s1, s2;
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
    for (set<int>::iterator it = s1.begin(); it != s1.end(); ++it) {
        if (s2.find(*it) != s2.end()) cout << *it << endl;
    }
}
