// 1.11 --- Definition of hash functions
// En este caso la funcion de hash es la suma de las funciones de hash aplicadas
// a los tres campos. Hay que definir tambien el operador de comparacion por
// igualdad. Este codigo usa C++11.
#include <unordered_set>
using namespace std;

struct Point {
    int x, y, z;

    friend bool operator== (const Point& p1, const Point& p2) {
        return p1.x == p2.x and p1.y == p2.y and p1.z == p2.z;
    }

    struct Hash {
        size_t operator() (const Point& p) const {
            return hash<int>()(p.x) + hash<int>()(p.y) + hash<int>()(p.z);
        }
    };
};

int main() {
    unordered_set<Point, Point::Hash> cloud;
    cloud.insert({5,2,3});
}
