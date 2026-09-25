# Union-Find (Disjoint Set Union) · EXTRA

> No está en el PDF, pero hace falta para Kruskal y es una de las estructuras más
> elegantes que existen.

**Fichero:** `union_find.cc`

## En qué consiste

Mantiene una **partición** de `{0, 1, …, n-1}` en conjuntos disjuntos, con dos
operaciones:

```cpp
int  find  (int x);        // representante del conjunto de x
bool unite (int x, int y); // une los conjuntos de x e y
bool same  (int x, int y); // ¿están en el mismo conjunto?
```

Cada conjunto se representa como un **árbol** donde cada nodo apunta a su padre.
La **raíz** es el representante. `find(x)` sube hasta la raíz; `unite` cuelga una
raíz de la otra.

```
parent: [0, 0, 1, 3]

    0        3
   / \
  1   2
  |
  3?   -> unite(2,3) cuelga 3 de 0
```

## Las dos optimizaciones

Sin optimizar, los árboles pueden degenerar en listas y `find` costaría Θ(n).
Con las dos siguientes, el coste baja a **casi constante**:

### 1. Unión por rango
Al unir, se cuelga el árbol **más bajo** del más alto. Así la altura solo crece
cuando unes dos árboles de la misma altura, y por tanto es O(log n).

```cpp
if (rank_[rx] < rank_[ry]) swap(rx, ry);
parent[ry] = rx;
if (rank_[rx] == rank_[ry]) ++rank_[rx];
```

### 2. Compresión de caminos
Al hacer `find`, se **aplana** el camino: todos los nodos que has visitado pasan
a colgar directamente de la raíz. Las próximas búsquedas serán inmediatas.

```cpp
int find (int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}
```

Son dos líneas y cambian por completo el coste.

## Coste

| | |
|---|---|
| Con las dos optimizaciones | **Θ(α(n)) amortizado** por operación |
| Solo una de las dos | Θ(log n) |
| Ninguna | Θ(n) en el caso peor |
| Memoria | Θ(n) |

**α(n)** es la inversa de la función de Ackermann. Crece tan absurdamente despacio
que **α(n) ≤ 4 para cualquier n que quepa en el universo** (α(2^65536) = 5). A
efectos prácticos, las operaciones son **constantes**.

Es uno de los resultados más bonitos del análisis amortizado (Tarjan, 1975), y
también se demostró que esa cota es óptima: no se puede hacer mejor.

## Para qué sirve

- **Kruskal**: detectar si añadir una arista formaría un ciclo (ver `../Kruskal/`).
- Componentes conexas de un grafo que va recibiendo aristas (*online*, algo que
  el DFS no puede hacer sin recalcular).
- Equivalencias en general: "¿son x e y la misma cosa?" donde la relación se va
  descubriendo poco a poco.
- Detección de ciclos en grafos no dirigidos.
- Problemas de *percolation*, laberintos generados aleatoriamente.

## Probarlo

```bash
g++ -std=c++17 union_find.cc -o uf && ./uf
```
