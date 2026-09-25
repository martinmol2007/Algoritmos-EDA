// 1.10 --- Unordered dictionaries: unordered_map
// Lee una secuencia de palabras y, por cada palabra, escribe el numero de veces
// que aparece. Como se usa un unordered_map, el orden de la salida no esta
// definido. Este codigo usa C++11.
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

int main() {
    unordered_map<string, int> m;
    string x;
    while (cin >> x) ++m[x];
    for (auto elem : m) {
        cout << elem.first << " " << elem.second << endl;
    }
}
