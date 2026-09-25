// 3.5 --- Dictionary with an Adelson-Velskii-Landis tree (AVL)
// Diccionario implementado con un arbol AVL: un ABB que se mantiene equilibrado.
//
// Invariante AVL: para todo nodo, las alturas de sus dos subarboles difieren
// como mucho en 1. Eso garantiza h = Theta(log n) SIEMPRE, no solo en el caso
// medio como en un ABB normal.
//
// La altura del puntero nulo es -1 y la altura de una hoja es 0.
//
// (El PDF no documenta esta seccion; ver la documentacion de los ABB.)

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
    struct Node {
        Key key;
        Info info;
        Node* left;     // Pointer to left child
        Node* right;    // Pointer to right child
        int height;     // Height of the tree
        Node (const Key& c, const Info& i, Node* l, Node* r, int h)
        :   key(c), info(i), left(l), right(r), height(h)
        { }
    };

    int n;          // Number of keys
    Node* root;     // Pointer to the root of the AVL

public:
    Dictionary () {
        n = 0;
        root = nullptr;
    }

    Dictionary (Dictionary& d) {
        n = d.n;
        root = copy(d.root);
    }

    Dictionary& operator= (const Dictionary& d) {
        if (&d != this) {
            free(root);
            n = d.n;
            root = copy(d.root);
        }
        return *this;
    }

    ~Dictionary () {
        free(root);
    }

    // Coste: Theta(log n) garantizado.
    void assign (const Key& key, const Info& info) {
        assign(root, key, info);
    }

    // Coste: Theta(log n) garantizado.
    void erase (const Key& key) {
        delete_avl(root, key);
    }

    // Coste: Theta(log n) garantizado.
    Info& query (const Key& key) {
        if (Node* p=find(root, key)) {
            return p->info;
        } else {
            throw "Key does not exist";
    }   }

    // Coste: Theta(log n) garantizado.
    bool contains (const Key& key) {
        return find(root, key);
    }

    // Coste: Theta(1).
    int size() {
        return n;
    }

private:
    static void free (Node* p) {
        if (p) {
            free(p->left);
            free(p->right);
            delete p;
    }   }

    static Node* copy (Node* p) {
        return p ? new Node(p->key, p->info, copy(p->left), copy(p->right), p->height)
                 : nullptr;
    }

    static Node* find (Node* p, const Key& key) {
        if (p) {
            if (key < p->key) {
                return find(p->left, key);
            } else if (key > p->key) {
                return find(p->right, key);
        }   }
        return p;
    }

    // Altura del arbol apuntado por p (-1 si es vacio).
    static int height (Node* p) {
        return p ? p->height : -1;
    }

    static void update_height (Node* p) {
        p->height = 1 + max(height(p->left), height(p->right));
    }

    // ------------------------------------------------------- ROTACIONES
    // LL: rotacion simple a la derecha.
    //
    /*        p                q
             / \              / \
            q   C    --->    A   p
           / \                  / \
          A   B                B   C                                        */
    static void LL (Node*& p) {
        Node* q = p;
        p = p->left;
        q->left = p->right;
        p->right = q;
        update_height(q);
        update_height(p);
    }

    // RR: rotacion simple a la izquierda (simetrica de LL).
    static void RR (Node*& p) {
        Node* q = p;
        p = p->right;
        q->right = p->left;
        p->left = q;
        update_height(q);
        update_height(p);
    }

    // LR: rotacion doble = RR sobre el hijo izquierdo, despues LL sobre p.
    static void LR (Node*& p) {
        RR(p->left);
        LL(p);
    }

    // RL: rotacion doble = LL sobre el hijo derecho, despues RR sobre p.
    static void RL (Node*& p) {
        LL(p->right);
        RR(p);
    }

    // ------------------------------------------------------- INSERCION
    // Como en un ABB, pero al volver de la recursion se comprueba el desequilibrio
    // y se aplica la rotacion que toca. Una sola rotacion basta tras una insercion.
    void assign (Node*& p, const Key& key, const Info& info) {
        if (p) {
            if (key < p->key) {
                assign(p->left, key, info);
                if (height(p->left)-height(p->right) == 2) {
                    if (key < p->left->key) LL(p);
                    else LR(p);
                }
                update_height(p);
            } else if (key > p->key) {
                assign(p->right, key, info);
                if (height(p->right)-height(p->left) == 2) {
                    if (key > p->right->key) RR(p);
                    else RL(p);
                }
                update_height(p);
            } else {
                p->info = info;
            }
        } else {
            p = new Node(key, info, nullptr, nullptr, 0);
            ++n;
    }   }

    // ------------------------------------------------------- BORRADO
    // Como el erase_3 del ABB, pero reequilibrando al volver de la recursion.
    // Tras un borrado puede hacer falta mas de una rotacion (hasta log n).
    void delete_avl (Node*& p, const Key& key) {
        if (p) {
            if (key < p->key) {
                delete_avl(p->left, key);
                rebalance_left(p);
            } else if (key > p->key) {
                delete_avl(p->right, key);
                rebalance_right(p);
            } else {
                Node* old = p;
                if (p->height == 0) {
                    p = 0;
                } else if (!p->left) {
                    p = p->right;
                } else if (!p->right) {
                    p = p->left;
                } else {
                    Node* q = extract_minimum(p->right);
                    q->left = p->left;  q->right = p->right;
                    p = q;
                    rebalance_right(p);
                }
                delete old; --n;
    }   }   }

    // Reequilibra despues de que el subarbol IZQUIERDO haya menguado.
    void rebalance_left (Node*& p) {
        if (height(p->right)-height(p->left)==2) {
            if (height(p->right->left) - height(p->right->right) == 1) {
                RL(p);
            } else {
                RR(p);
            }
        } else {
            update_height(p);
    }   }

    // Reequilibra despues de que el subarbol DERECHO haya menguado.
    void rebalance_right (Node*& p) {
        if (height(p->left)-height(p->right)==2) {
            if (height(p->left->right) - height(p->left->left) == 1) {
                LR(p);
            } else {
                LL(p);
            }
        } else {
            update_height(p);
    }   }

    Node* extract_minimum (Node*& p) {
        if (p->left) {
            Node* q = extract_minimum(p->left);
            rebalance_left(p);
            return q;
        } else {
            Node* q = p;
            p = p->right;
            return q;
    }   }

// ---- Solo para la demostracion: comprueba el invariante y da la altura ----
public:
    int altura () { return height(root); }

    bool es_avl () { return es_avl(root); }

private:
    static bool es_avl (Node* p) {
        if (not p) return true;
        int b = height(p->left) - height(p->right);
        if (b < -1 or b > 1) return false;
        if (p->height != 1 + max(height(p->left), height(p->right))) return false;
        return es_avl(p->left) and es_avl(p->right);
    }
};

// ------------------------------------------------------------------- demo
// Inserta 1..1000 EN ORDEN: en un ABB normal eso daria una lista de altura 999.
// En un AVL la altura se queda en ~10.
int main() {
    Dictionary<int, int> d;
    for (int i = 1; i <= 1000; ++i) d.assign(i, i*i);

    cout << "size        = " << d.size() << endl;
    cout << "altura      = " << d.altura() << "  (log2(1000) ~ 10)" << endl;
    cout << "es AVL?     = " << d.es_avl() << endl;
    cout << "query(500)  = " << d.query(500) << endl;

    for (int i = 1; i <= 500; ++i) d.erase(i);
    cout << "tras borrar 500: size = " << d.size()
         << ", altura = " << d.altura()
         << ", es AVL? = " << d.es_avl() << endl;
}
