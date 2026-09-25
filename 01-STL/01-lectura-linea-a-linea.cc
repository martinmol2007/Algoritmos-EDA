// 1.1 --- Reading the input line by line: istringstream
// Lee una secuencia de lineas y, por cada linea, escribe la suma de los numeros
// que contiene.
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        istringstream ss(s);
        int sum = 0;
        int x;
        while (ss >> x) sum += x;
        cout << sum << endl;
}   }
