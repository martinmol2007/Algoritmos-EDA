// 3.1 --- Dictionary with a table (unordered)
// Diccionario implementado con una tabla (vector) de pares clave/valor SIN
// ningun orden.
//
// Aqui n denota la talla (numero de claves) del diccionario. El constructor
// implicito, el constructor por copia, el operador de asignacion y el destructor
// hacen ya su trabajo; no hace falta implementarlos. El coste en el caso peor
// del constructor es Theta(1); el del constructor por copia, el operador de
// asignacion y el destructor es Theta(n).

#include <utility>
#include <vector>
#include <iostream>
using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
    typedef pair<Key, Info> Pair;
    vector<Pair> t;

public:
    // -----------------------------------------------------------------------
    // Asigna info a key. Si la clave ya pertenece al diccionario, se modifica la
    // informacion asociada.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    void assign (const Key& key, const Info& info) {
        int i = find(key);
        if (i < int(t.size())) {
            t[i].second = info;
        } else {
            t.push_back(Pair(key, info));
    }   }

    // -----------------------------------------------------------------------
    // Borra key y su informacion asociada. Si la clave no pertenece al
    // diccionario, este no cambia.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    void erase (const Key& key) {
        int i = find(key);
        if (i < int(t.size())) {
            t[i] = t[t.size() - 1];
            t.pop_back();
    }   }

    // -----------------------------------------------------------------------
    // Devuelve una referencia a la informacion asociada a key. Lanza una
    // excepcion de precondicion si la clave no pertenece al diccionario.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    Info& query (const Key& key) {
        int i = find(key);
        if (i < int(t.size())) {
            return t[i].second;
        } else {
            throw "Key does not exist.";
    }   }

    // -----------------------------------------------------------------------
    // Indica si el diccionario contiene key.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    bool contains (const Key& key) {
        return find(key) < int(t.size());
    }

    // -----------------------------------------------------------------------
    // Devuelve la talla del diccionario (numero de claves que contiene).
    // Coste en el caso peor: Theta(1).
    // -----------------------------------------------------------------------
    int size() {
        return t.size();
    }

private:
    // -----------------------------------------------------------------------
    // Devuelve la posicion de key en la tabla, o t.size() si no esta.
    // Coste en el caso peor: Theta(n).
    // -----------------------------------------------------------------------
    int find (const Key& key) {
        int i = 0;
        while (i < int(t.size()) and t[i].first != key) ++i;
        return i;
    }
};

// ------------------------------------------------------------------- demo
int main() {
    Dictionary<string, int> d;
    d.assign("hola", 1);
    d.assign("adeu", 2);
    d.assign("hola", 42);          // sobreescribe
    cout << "size      = " << d.size() << endl;
    cout << "hola      = " << d.query("hola") << endl;
    cout << "contains? = " << d.contains("adeu") << endl;
    d.erase("adeu");
    cout << "size      = " << d.size() << endl;
}
