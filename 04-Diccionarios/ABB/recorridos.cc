// EXTRA (no esta en el PDF) --- Recorridos de un arbol binario
// Los cuatro recorridos clasicos sobre el mismo ABB.
//
// Coste: Theta(n) en todos ellos (cada nodo se visita una vez).
// Memoria: Theta(h) de pila en los recursivos, Theta(n) en el de niveles.

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node (int k) : key(k), left(nullptr), right(nullptr) { }
};

void insert (Node*& p, int k) {
    if (not p) p = new Node(k);
    else if (k < p->key) insert(p->left, k);
    else if (k > p->key) insert(p->right, k);
}

void free_tree (Node* p) {
    if (p) { free_tree(p->left); free_tree(p->right); delete p; }
}

// --------------------------------------------------------- PREORDEN
// raiz, izquierdo, derecho.
// Util para COPIAR o SERIALIZAR un arbol: si reinsertas las claves en este
// orden, reconstruyes exactamente el mismo arbol.
void preorden (Node* p) {
    if (p) {
        cout << p->key << " ";
        preorden(p->left);
        preorden(p->right);
    }
}

// --------------------------------------------------------- INORDEN
// izquierdo, raiz, derecho.
// En un ABB da las claves ORDENADAS de menor a mayor. Es la propiedad que
// convierte un ABB en un diccionario ordenado.
void inorden (Node* p) {
    if (p) {
        inorden(p->left);
        cout << p->key << " ";
        inorden(p->right);
    }
}

// --------------------------------------------------------- POSTORDEN
// izquierdo, derecho, raiz.
// Util para DESTRUIR un arbol (borras los hijos antes que el padre) o para
// calcular valores que dependen de los subarboles (altura, talla, suma...).
void postorden (Node* p) {
    if (p) {
        postorden(p->left);
        postorden(p->right);
        cout << p->key << " ";
    }
}

// --------------------------------------------------------- POR NIVELES (BFS)
// Visita el arbol nivel a nivel, de izquierda a derecha. No es recursivo:
// necesita una COLA. Es exactamente un BFS sobre el arbol.
void por_niveles (Node* p) {
    if (not p) return;
    queue<Node*> q;
    q.push(p);
    while (not q.empty()) {
        Node* u = q.front(); q.pop();
        cout << u->key << " ";
        if (u->left)  q.push(u->left);
        if (u->right) q.push(u->right);
    }
}

// --------------------------------------- INORDEN ITERATIVO (con pila explicita)
// La misma idea que inorden pero gestionando la pila a mano.
void inorden_iterativo (Node* p) {
    stack<Node*> s;
    while (p or not s.empty()) {
        while (p) { s.push(p); p = p->left; }
        p = s.top(); s.pop();
        cout << p->key << " ";
        p = p->right;
    }
}

// ------------------------------------------------------------------- demo
int main() {
    Node* root = nullptr;
    for (int k : {50, 30, 70, 20, 40, 60, 80}) insert(root, k);

    /*        50
            /    \
          30      70
         /  \    /  \
        20  40  60  80                                                      */

    cout << "preorden   : "; preorden(root);           cout << endl;
    cout << "inorden    : "; inorden(root);            cout << endl;
    cout << "postorden  : "; postorden(root);          cout << endl;
    cout << "por niveles: "; por_niveles(root);        cout << endl;
    cout << "inorden it : "; inorden_iterativo(root);  cout << endl;

    free_tree(root);
}
