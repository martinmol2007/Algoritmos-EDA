// 3.2 --- Dictionary with a list (unordered)
// Diccionario implementado con una lista enlazada de pares clave/valor SIN
// ningun orden. Supone que Key es un tipo comparable.
//
// Aqui n denota la talla (numero de claves) del diccionario y se guarda
// explicitamente para poder implementar size() con coste Theta(1) en el caso
// peor (nota: el size() de las listas de la STL tomaba tiempo lineal en C++98).
// El constructor por copia, el operador de asignacion y el destructor implicitos
// hacen ya su trabajo; no hace falta implementarlos. Su coste en el caso peor es
// Theta(n).

#include <utility>
#include <list>
#include <iostream>
#include <string>
using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
    typedef pair<Key, Info> Pair;
    typedef list<Pair> List;
    typedef typename List::iterator iter;

    List li;            // the list
    int n;              // the number of keys

public:
    // -----------------------------------------------------------------------
    // Constructor. Crea un diccionario vacio.
    // Coste en el caso peor: Theta(1).
    // -----------------------------------------------------------------------
    Dictionary () {
        n = 0;
    }

    // -----------------------------------------------------------------------
    // Asigna info a key. Si la clave ya pertenece al diccionario, se modifica la
    // informacion asociada.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    void assign (const Key& key, const Info& info) {
        iter p = find(key);
        if (p != li.end()) {
            p->second = info;
        } else {
            li.push_back(Pair(key, info));
            ++n;
    }   }

    // -----------------------------------------------------------------------
    // Borra key y su informacion asociada. Si la clave no pertenece al
    // diccionario, este no cambia.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    void erase (const Key& key) {
        iter p = find(key);
        if (p != li.end()) {
            li.erase(p);
            --n;
    }   }

    // -----------------------------------------------------------------------
    // Devuelve una referencia a la informacion asociada a key. Lanza una
    // excepcion de precondicion si la clave no pertenece al diccionario.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    Info& query (const Key& key) {
        iter p = find(key);
        if (p != li.end()) {
            return p->second;
        } else {
            throw "Key does not exist";
    }   }

    // -----------------------------------------------------------------------
    // Indica si el diccionario contiene key.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    bool contains (const Key& key) {
        return find(key) != li.end();
    }

    // -----------------------------------------------------------------------
    // Devuelve la talla (numero de claves) del diccionario.
    // Coste en el caso peor: Theta(1).
    // -----------------------------------------------------------------------
    int size() {
        return n;
    }

private:
    // -----------------------------------------------------------------------
    // Devuelve la posicion de c en la lista, o li.end() si no esta.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    iter find (const Key& c) {
        iter p = li.begin();
        while (p != li.end() and p->first != c) ++p;
        return p;
    }
};

// ------------------------------------------------------------------- demo
int main() {
    Dictionary<string, int> d;
    d.assign("hola", 1);
    d.assign("adeu", 2);
    d.assign("hola", 42);
    cout << "size      = " << d.size() << endl;
    cout << "hola      = " << d.query("hola") << endl;
    cout << "contains? = " << d.contains("adeu") << endl;
    d.erase("adeu");
    cout << "size      = " << d.size() << endl;
}
