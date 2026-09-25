// eda.hh --- Apendice A.1 del PDF "Data Structures and Algorithms / Algorithms in C++"
// Jordi Petit, Salvador Roura (juliol 2010). Traduccio a l'angles: A. Atserias (setembre 2013).
//
// Fichero de macros y utilidades que usan casi todos los codigos de los
// capitulos de Grafos y Backtracking.
//
// Compilacion tipica:   g++ -std=c++17 -I<ruta a 00-Comun> fichero.cc -o fichero

#ifndef eda_hh
#define eda_hh

// ---------------------------------------------------------------- Inclusiones
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <sys/resource.h>
using namespace std;

// ------------------------------------------------------------- Tipo `boolean`
// El tipo boolean es un int, pero se usa como si fuera un bool. El objetivo es
// poder tener vectores de booleanos que sean rapidos: vector<bool> es lento
// porque trabaja a nivel de bit.
typedef int boolean;

// --------------------------------------------------------- Puntero nulo `null`
// En C++ un puntero nulo es simplemente un cero.
// (Hoy en dia se prefiere nullptr; se mantiene por fidelidad al PDF.)
#define null 0

// ------------------------------------------------------------- Clase `matrix`
// Tablas bidimensionales sin usar vectores de vectores. El inconveniente es que
// el numero de filas y de columnas queda fijado en la construccion.
template <typename T>
class matrix {
    int r,c;
    vector<vector<T> > t;
public:
    matrix() :
        r(0), c(0) {  }
    matrix(int rows, int cols, T init=T()) :
        r(rows), c(cols), t(vector<vector<T> >(r, vector<T>(c, init))) {  }
    int rows() const {
        return r;
    }
    int cols() const {
        return c;
    }
    vector<T>& operator[](int i) {
        return t[i];
    }
    const vector<T>& operator[](int i) const {
        return t[i];
    }
    friend ostream& operator<<(ostream& s, matrix<T> m) {
        for (int j = 0; j < m.c; ++j) {
            for (int i = 0; i < m.r; ++i) {
                s << m.t[i][j] << " ";
            }
            s << endl;
        }
        return s;
    }
};

// ------------------------------------------- Escritura del contenido de un vector
template <typename T> ostream& operator<<(ostream& s, vector<T> v) {
    for (int i = 0; i < int(v.size()); ++i) {
        s << v[i] << " ";
    }
    return s;
}

// ------------------------------------------------- Lectura de tipos basicos
inline int      readint     ()  { int    n;  cin >> n;  return n; }
inline char     readchar    ()  { char   n;  cin >> n;  return n; }
inline bool     readbool    ()  { bool   n;  cin >> n;  return n; }
inline double   readdouble  ()  { double n;  cin >> n;  return n; }

// `infinity`: un double mayor que cualquier otro double (excepto el mismo).
const double infinity = numeric_limits<double>::infinity();

// `maxint`: el mayor entero representable.
const int maxint = numeric_limits<int>::max();

// --------------------------------------------------------- Numeros aleatorios
// Devuelve un real aleatorio en [0, 1).
inline double randdouble() {
    return rand() / double(RAND_MAX);
}
// Devuelve un entero aleatorio en [a..b].
inline int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}
// Devuelve un entero aleatorio en [0..n-1].
inline double randint(int n) {
    return rand() % n;
}
// Devuelve cierto con probabilidad p.
inline boolean randbit(double p) {
    return randdouble() < p;
}
// Devuelve una matriz n x n de reales aleatorios.
inline matrix<double> randmatrix(int n) {
    matrix<double> m(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; j++) {
            m[i][j] = randdouble();
        }
    }
    return m;
}
// Devuelve un vector de n reales aleatorios.
inline vector<double> randvector(int n) {
    vector<double> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = randdouble();
    }
    return v;
}
// Devuelve un vector de n enteros aleatorios en [a..b].
inline vector<int> randvector(int n, int a, int b) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = randint(a, b);
    }
    return v;
}

// ------------------------------------------------- Medida de tiempo de CPU
inline double now() {
    // Esto funciona en Linux, no se si en otros sistemas.
    struct rusage u;
    getrusage(RUSAGE_SELF, &u);
    return
        u.ru_utime.tv_sec  + u.ru_stime.tv_sec
      +(u.ru_utime.tv_usec + u.ru_stime.tv_usec)/1000000.0;
}

// -------------------------------------- Macro para recorrer un contenedor
#define foreach(it,c) for (__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

// ------------------------------------------------------------------ Errores
// ErrorPrec y ErrorImpl son excepciones. Error es la clase base comun, util
// para hacer catch de las dos. Es el unico sitio del curso donde hay herencia.
class Error {
    private:
        string err;
    public:
        Error(string s) : err(s) {}
        string error() const {return err;}
};

class ErrorPrec: public Error {
    public:
        ErrorPrec(string s) : Error("Precondition error: " + s) {}
};

class ErrorImpl: public Error {
    public:
        ErrorImpl(string s) : Error("Implementation error: " + s) {}
};

#endif
