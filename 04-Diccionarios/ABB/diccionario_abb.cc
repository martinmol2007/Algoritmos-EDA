// 3.4 --- Dictionary with a binary search tree (BST)
// Diccionario implementado con un arbol binario de busqueda (ABB).
// Supone que Key es un tipo comparable.
//
// Un ABB es un arbol binario cuyos nodos guardan pares clave/info y que cumple
// la propiedad de que, para cada nodo u, la clave de u es mayor que todas las
// claves del subarbol izquierdo de u y menor que todas las del subarbol derecho.
//
// Esta implementacion representa el ABB mediante un puntero root a un Node que
// contiene: una clave, la informacion asociada, un puntero a la raiz del
// subarbol izquierdo y un puntero a la raiz del subarbol derecho. Los arboles
// vacios se representan con el puntero nulo. Se mantiene un contador n con el
// numero de claves del diccionario. Usamos h para la altura del ABB y damos los
// costes en funcion de h siempre que se pueda.
//
// En un ABB generado aleatoriamente (claves insertadas en posiciones elegidas
// uniformemente y nunca borradas) tenemos h = Theta(log n) en esperanza. Asi, un
// coste Theta(h) en el caso peor se traduce en un coste Theta(log n) en el caso
// medio (bajo este modelo aleatorio). En el caso peor tenemos h = n.

#include <iostream>
#include <string>
using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
    struct Node {
        Key key;
        Info info;
        Node* left;      // Pointer to left child
        Node* right;     // Pointer to right child
        Node (const Key& k, const Info& i, Node* l, Node* r)
        :   key(k), info(i), left(l), right(r) { }
    };

    int n;          // Number of keys
    Node* root;     // Pointer to the root of the BST

public:
    // ----------------------------------------- Constructor. Coste: Theta(1).
    Dictionary () {
        n = 0;
        root = nullptr;
    }

    // ------------------------------- Constructor por copia. Coste: Theta(n).
    Dictionary (const Dictionary& d) {
        n = d.n;
        root = copy(d.root);
    }

    // ------------------------ Operador de asignacion. Coste: Theta(n + d.n).
    Dictionary& operator= (const Dictionary& d) {
        if (&d != this) {
            free(root);
            n = d.n;
            root = copy(d.root);
        }
        return *this;
    }

    // ------------------------------------------- Destructor. Coste: Theta(n).
    ~Dictionary () {
        free(root);
    }

    // ---------------------------------- Asigna info a key. Coste: Theta(h).
    void assign (const Key& key, const Info& info) {
        assign(root, key, info);
    }

    // -----------------------------------------------------------------------
    // Borra key y su informacion asociada. Si la clave no pertenece al
    // diccionario, no cambia nada. Coste en el caso peor: Theta(h).
    // -----------------------------------------------------------------------
    void erase (const Key& key) {
        erase_3(root, key);
    }

    // -----------------------------------------------------------------------
    // Devuelve una referencia a la informacion asociada a key. Lanza una
    // excepcion de precondicion si la clave no esta. Coste: Theta(h).
    // -----------------------------------------------------------------------
    Info& query (const Key& key) {
        if (Node* p = find(root, key)) {
            return p->info;
        } else {
            throw "Key does not exist";
    }   }

    // ------------------------ Indica si el diccionario contiene key. Theta(h).
    bool contains (const Key& key) {
        return find(root, key);
    }

    // ---------------------------------- Talla del diccionario. Coste: Theta(1).
    int size () {
        return n;
    }

private:
    // -----------------------------------------------------------------------
    // Destruye el arbol apuntado por p.
    // Coste en el caso peor: Theta(s), s = numero de nodos del arbol.
    // -----------------------------------------------------------------------
    static void free (Node* p) {
        if (p) {
            free(p->left);
            free(p->right);
            delete p;
    }   }

    // -----------------------------------------------------------------------
    // Devuelve un puntero a una copia del arbol apuntado por p.
    // Coste en el caso peor: Theta(s).
    // -----------------------------------------------------------------------
    static Node* copy (Node* p) {
        return p ? new Node(p->key, p->info, copy(p->left), copy(p->right)) : nullptr;
    }

    // -----------------------------------------------------------------------
    // Devuelve un puntero al nodo del arbol apuntado por p que contiene key, o
    // nullptr si la clave no esta.
    // Coste en el caso peor: Theta(t), t = altura del arbol apuntado por p.
    // -----------------------------------------------------------------------
    static Node* find (Node* p, const Key& key) {
        if (p) {
            if (key < p->key) {
                return find(p->left, key);
            } else if (key > p->key) {
                return find(p->right, key);
        }   }
        return p;
    }

    // -----------------------------------------------------------------------
    // Asigna info a key si la clave pertenece al arbol apuntado por p. Si no,
    // anyade un nodo nuevo con la clave y la informacion asociada.
    // Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    void assign (Node*& p, const Key& key, const Info& info) {
        if (p) {
            if (key < p->key) {
                assign(p->left, key, info);
            } else if (key > p->key) {
                assign(p->right, key, info);
            } else {
                p->info = info;
            }
        } else {
            p = new Node(key, info, nullptr, nullptr);
            ++n;
    }   }

    // -----------------------------------------------------------------------
    // Devuelve un puntero al nodo con la clave minima del arbol de raiz p.
    // Supone que p no es nullptr. Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    static Node* minimum (Node* p) {
        return p->left ? minimum(p->left) : p;
    }

    // -----------------------------------------------------------------------
    // Devuelve un puntero al nodo con la clave maxima del arbol de raiz p.
    // Supone que p no es nullptr. Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    static Node* maximum (Node* p) {
        return p->right ? maximum(p->right) : p;
    }

    // -----------------------------------------------------------------------
    // BORRADO version 1: borrar un nodo con al menos un hijo vacio es facil.
    // Cuando los dos hijos son no vacios, cuelga el hijo izquierdo como nuevo
    // hijo izquierdo del minimo del hijo derecho.
    // Inconveniente: el arbol se degrada rapidamente.
    // Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    void erase_1 (Node*& p, const Key& key) {
        if (p) {
            if (key < p->key) {
                erase_1(p->left, key);
            } else if (key > p->key) {
                erase_1(p->right, key);
            } else {
                Node* q = p;
                if (!p->left) p = p->right;
                else if (!p->right) p = p->left;
                else {
                    Node* m = minimum(p->right);
                    m->left = p->left;
                    p = p->right;
                }
                delete q; --n;
    }   }   }

    // -----------------------------------------------------------------------
    // BORRADO version 2: cuando los dos hijos son no vacios, copia el minimo del
    // hijo derecho en el nodo que deberia desaparecer y procede a borrar ese
    // minimo (que seguro que no tiene hijo izquierdo).
    // Inconveniente: copia claves e informaciones, no punteros.
    // Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    void erase_2 (Node*& p, const Key& key) {
        if (p) {
            if (key < p->key) {
                erase_2(p->left, key);
            } else if (key > p->key) {
                erase_2(p->right, key);
            } else if (!p->left) {
                Node* q = p;  p = p->right;
                delete q; --n;
            } else if (!p->right) {
                Node* q = p;  p = p->left;
                delete q; --n;
            } else {
                Node* m = minimum(p->right);
                p->key = m->key; p->info = m->info;
                erase_2(p->right, m->key);
    }   }   }

    // -----------------------------------------------------------------------
    // BORRADO version 3: cuando los dos hijos son no vacios, llama a
    // extract_minimum, que extrae el minimo del hijo derecho y devuelve un
    // puntero a ese nodo. Ese nodo se pone donde estaba el que debe desaparecer,
    // que finalmente se borra.  <-- es la que usa erase() publico.
    // Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    void erase_3 (Node*& p, const Key& key) {
        if (p) {
            if (key < p->key) {
                erase_3(p->left, key);
            } else if (key > p->key) {
                erase_3(p->right, key);
            } else {
                Node* q = p;
                if (!p->left) p = p->right;
                else if (!p->right) p = p->left;
                else {
                    Node* m = extract_minimum(p->right);
                    m->left = p->left;  m->right = p->right;
                    p = m;
                }
                delete q; --n;
    }   }   }

    // -----------------------------------------------------------------------
    // Extrae del arbol apuntado por p el nodo que contiene el minimo y devuelve
    // un puntero a ese nodo. Coste en el caso peor: Theta(t).
    // -----------------------------------------------------------------------
    Node* extract_minimum (Node*& p) {
        if (p->left) {
            return extract_minimum(p->left);
        } else {
            Node* q = p;
            p = p->right;
            return q;
    }   }
};

// ------------------------------------------------------------------- demo
int main() {
    Dictionary<int, string> d;
    int claves[] = {50, 30, 70, 20, 40, 60, 80};
    for (int k : claves) d.assign(k, "v" + to_string(k));

    cout << "size       = " << d.size() << endl;
    cout << "query(40)  = " << d.query(40) << endl;
    cout << "contains 60= " << d.contains(60) << endl;

    d.erase(30);                       // nodo con dos hijos
    cout << "tras borrar 30, size = " << d.size()
         << ", contains(30) = " << d.contains(30) << endl;

    Dictionary<int, string> copia = d; // constructor por copia
    cout << "copia size = " << copia.size() << endl;
}
