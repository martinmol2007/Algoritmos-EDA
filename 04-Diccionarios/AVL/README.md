# AVL · Árbol de Adelson-Velskii y Landis

**PDF:** sección 3.5 · **Fichero:** `diccionario_avl.cc`

> El PDF no documenta esta sección ("This implementation contains no
> documentation yet"). Lo que sigue es explicación añadida.

## En qué consiste

Un AVL es **un ABB que se reequilibra solo**. Mantiene esta invariante:

> para todo nodo, `|altura(izquierdo) - altura(derecho)| ≤ 1`

A ese número se le llama **factor de equilibrio**, y solo puede valer -1, 0 o +1.
Cada nodo guarda su altura en un campo `height` para poder comprobarlo en Θ(1).
Convenio: **altura(nullptr) = -1**, altura de una hoja = 0.

La consecuencia es la que buscábamos: un AVL con n nodos tiene altura
**h ≤ 1.44·log₂(n+2)**, es decir **h = Θ(log n) SIEMPRE**. Desaparece el caso
peor Θ(n) del ABB.

## Coste

| Operación | Coste |
|---|---|
| `assign`, `erase`, `query`, `contains` | **Θ(log n) garantizado** |
| `size` | Θ(1) |
| Constructor por copia, destructor | Θ(n) |

Comparado con el ABB: mismas operaciones, mismo Θ(log n) *en el caso medio*, pero
el AVL lo garantiza también en el **caso peor**. El precio es guardar una altura
por nodo y hacer rotaciones.

## Las rotaciones

Una rotación reorganiza tres nodos manteniendo la invariante del ABB y reduciendo
la altura. Hay dos simples y dos dobles:

### LL — rotación simple a la derecha

Se aplica cuando el desequilibrio viene del **hijo izquierdo del hijo izquierdo**.

```
        p                q
       / \              / \
      q   C    --->    A   p
     / \                  / \
    A   B                B   C
```

### RR — rotación simple a la izquierda
Simétrica de LL: desequilibrio en el **hijo derecho del hijo derecho**.

### LR — rotación doble
Desequilibrio en el **hijo derecho del hijo izquierdo**. Una rotación simple no
lo arregla (el árbol se queda igual de desequilibrado por el otro lado). Se hace
`RR(p->left)` y después `LL(p)`.

### RL — rotación doble
Simétrica: `LL(p->right)` y después `RR(p)`.

Cada rotación cuesta **Θ(1)** (solo mueve punteros y actualiza dos alturas).

## Inserción

Igual que en un ABB, pero **al volver de la recursión** se comprueba si ese nodo
ha quedado con factor de equilibrio ±2 y se rota si hace falta.

```cpp
assign(p->left, key, info);
if (height(p->left) - height(p->right) == 2) {
    if (key < p->left->key) LL(p);   // caso izquierda-izquierda
    else                    LR(p);   // caso izquierda-derecha
}
update_height(p);
```

Dato importante: **tras una inserción basta con UNA rotación** (simple o doble)
para reequilibrar todo el árbol. La rotación devuelve el subárbol a su altura
original, así que los ancestros dejan de estar desequilibrados.

## Borrado

Es el `erase_3` del ABB (con `extract_minimum`) más una llamada a
`rebalance_left` / `rebalance_right` al volver de cada nivel.

Y aquí está la diferencia importante con la inserción: **tras un borrado puede
hacer falta rotar en todos los niveles del camino**, hasta Θ(log n) rotaciones.
Por eso las bibliotecas reales (incluida la STL) suelen preferir **árboles
rojinegros**: equilibran algo peor (altura hasta 2·log n en vez de 1.44·log n)
pero garantizan un número **constante** de rotaciones por borrado.

`rebalance_left` se llama cuando el subárbol **izquierdo ha menguado** (y por
tanto puede haberse desequilibrado hacia la derecha). Ojo con los nombres: son
al revés de lo que uno esperaría.

## Cuándo tiene sentido

Cuando necesitas un diccionario **ordenado** con garantías de peor caso: `map`,
`set`, `multimap`, `multiset` de la STL (con árboles rojinegros en vez de AVL) y
cualquier índice de base de datos (con B-árboles, que es la misma idea adaptada a
disco).

Si no necesitas orden, una tabla de hash es más rápida.

## La demostración del fichero

El `main` inserta las claves **1..1000 en orden**, que es justo el caso que
destroza a un ABB (altura 999). El AVL se queda en altura 9. Después borra 500
claves y vuelve a comprobar que la invariante se mantiene, con los métodos extra
`altura()` y `es_avl()` (añadidos, no están en el PDF).

```bash
g++ -std=c++17 diccionario_avl.cc -o avl && ./avl
# size        = 1000
# altura      = 9  (log2(1000) ~ 10)
# es AVL?     = 1
```

## Detalle de implementación

El constructor por copia del PDF es `Dictionary (Dictionary& d)` — sin `const`.
Se ha dejado tal cual; en código propio habría que ponerle `const`, como en el
ABB.
