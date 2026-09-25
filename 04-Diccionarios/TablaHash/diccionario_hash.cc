// 3.3 --- Dictionary with a hash table
// Diccionario implementado con una tabla de hash con encadenamiento.
//
// Esta implementacion reparte los elementos del diccionario en M listas, donde M
// es el valor de M. La lista i-esima contiene todos los pares clave/info <k,x>
// tales que hash(k) = i. Un contador n mantiene el numero de claves que
// pertenecen al diccionario. Usamos n para el valor de n.
//
// El analisis de costes se hace bajo dos hipotesis: 1) dada una clave, hash
// devuelve un natural en tiempo Theta(1), y 2) la funcion hash "reparte
// uniformemente" en cada nueva llamada con una clave distinta.
//
// El constructor por copia, el operador de asignacion y el destructor implicitos
// hacen ya su trabajo; no hace falta implementarlos. Su coste en el caso peor y
// en el caso medio es Theta(n+M).
//
// NOTA: el PDF escribe `hash(key)` sin definir la funcion. Aqui se define como
// metodo privado que delega en std::hash<Key>.

#include <utility>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
    typedef pair<Key, Info> Pair;
    typedef list<Pair> List;
    typedef typename List::iterator iter;

    vector<List> t;     // Hash table
    int n;              // Number of keys
    int M;              // Number of positions

public:
    // -----------------------------------------------------------------------
    // Constructor. Crea un diccionario vacio.
    // Coste en el caso peor: Theta(M).
    // -----------------------------------------------------------------------
    Dictionary (int M = 1009)
    :   t(M), n(0), M(M) { }

    // -----------------------------------------------------------------------
    // Asigna info a key. Si la clave ya pertenece al diccionario, se modifica la
    // informacion asociada.
    // Coste en el caso peor:  Theta(n).
    // Coste en el caso medio: Theta(1 + n/M).
    // -----------------------------------------------------------------------
    void assign (const Key& key, const Info& info) {
        int h = hash(key) % M;
        iter p = find(key, t[h]);
        if (p != t[h].end()) {
            p->second = info;
        } else {
            t[h].push_back(Pair(key, info));
            ++n;
        }
    }

    // -----------------------------------------------------------------------
    // Borra key y su informacion asociada. Si la clave no pertenece al
    // diccionario, no cambia nada.
    // Coste en el caso peor:  Theta(n).
    // Coste en el caso medio: Theta(1 + n/M).
    // -----------------------------------------------------------------------
    void erase (const Key& key) {
        int h = hash(key) % M;
        iter p = find(key, t[h]);
        if (p != t[h].end()) {
            t[h].erase(p);
            --n;
        }
    }

    // -----------------------------------------------------------------------
    // Devuelve una referencia a la informacion asociada a key. Lanza una
    // excepcion de precondicion si la clave no pertenece al diccionario.
    // Coste en el caso peor:  Theta(n).
    // Coste en el caso medio: Theta(1 + n/M).
    // -----------------------------------------------------------------------
    Info& query (const Key& key) {
        int h = hash(key) % M;
        iter p = find(key, t[h]);
        if (p != t[h].end()) {
            return p->second;
        } else {
            throw "Key does not exist";
        }
    }

    // -----------------------------------------------------------------------
    // Indica si el diccionario contiene key.
    // Coste en el caso peor:  Theta(n).
    // Coste en el caso medio: Theta(1 + n/M).
    // -----------------------------------------------------------------------
    bool contains (const Key& key) {
        int h = hash(key) % M;
        iter p = find(key, t[h]);
        return p != t[h].end();
    }

    // -----------------------------------------------------------------------
    // Devuelve la talla (numero de claves) del diccionario.
    // Coste en el caso peor: Theta(1). Coste en el caso medio: Theta(1).
    // -----------------------------------------------------------------------
    int size () {
        return n;
    }

private:
    // -----------------------------------------------------------------------
    // Busca key en la lista y devuelve un iterador que apunta al elemento, o a
    // end() si no esta.
    // -----------------------------------------------------------------------
    static iter find (const Key& key, list<Pair>& L) {
        iter p = L.begin();
        while (p != L.end() and p->first != key) ++p;
        return p;
    }

    // Funcion de hash (no aparece en el PDF; se delega en la de la STL).
    static size_t hash (const Key& key) {
        return std::hash<Key>()(key);
    }
};

// ------------------------------------------------------------------- demo
int main() {
    Dictionary<string, int> d(101);
    d.assign("hola", 1);
    d.assign("adeu", 2);
    d.assign("hola", 42);
    cout << "size      = " << d.size() << endl;
    cout << "hola      = " << d.query("hola") << endl;
    cout << "contains? = " << d.contains("adeu") << endl;
    d.erase("adeu");
    cout << "size      = " << d.size() << endl;
}
