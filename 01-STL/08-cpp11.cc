// 1.8 --- New features in C++11
// En C++11 se puede dejar que el compilador "adivine" los tipos de las
// variables. Ademas, el bucle for se ha extendido para iterar comodamente sobre
// colecciones. Ya no hace falta poner un espacio en blanco en >> dentro de
// plantillas, y se pueden inicializar tipos complejos con listas de valores.
//
// Compilar con:  g++ -std=c++11 08-cpp11.cc   (o -std=c++17, mejor)
#include <vector>
#include <set>
#include <iostream>
using namespace std;

int main() {
    // read a vector from input
    vector<int> v;
    int x;
    while (cin >> x) v.push_back(x);
    // write all elements of v to output
    for (int y : v) cout << y << endl;
    // double all elements of v (note the reference to modify the elements!!!)
    for (int& y : v) y *= 2;
    // write all elements of v again
    for (int y : v) cout << y << endl;
    // make a set of sets of integers and write it
    set<set<int>> S = {{2,3}, {5,1,5}, {}, {3}};
    for (auto s : S) {
        cout << "{";
        for (auto x : s) cout << x << ",";
        cout << "}" << endl;
    }
}
