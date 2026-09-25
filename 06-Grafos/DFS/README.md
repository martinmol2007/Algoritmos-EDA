# DFS · Recorrido en profundidad

**PDF:** sección 5.2 · **Fichero:** `dfs.cc`

## En qué consiste

"Tira hacia delante todo lo que puedas; cuando no puedas más, retrocede."

Desde un vértice, se visita un vecino, y desde ese vecino otro, y así hasta
llegar a un callejón sin salida. Entonces se retrocede al último vértice con
vecinos sin visitar y se continúa.

Hace falta un vector `vis` de marcas para no visitar dos veces el mismo vértice
(y, en grafos con ciclos, para no dar vueltas para siempre).

El bucle exterior `for (int u = 0; u < n; ++u)` recorre **todos** los vértices,
así que el recorrido cubre el grafo entero aunque no sea conexo.

## Las dos versiones

### Recursiva
La pila de llamadas **es** la estructura de datos. Es la versión natural y la que
se usa para casi todo.

```cpp
void dfs_rec (const graph& G, int u, vector<boolean>& vis, list<int>& L) {
    if (not vis[u]) {
        vis[u] = true;  L.push_back(u);
        for (int v : G[u]) dfs_rec(G, v, vis, L);
    }
}
```

### Iterativa
La misma idea con una **pila explícita** (`stack`). Tal como dice el PDF, **el
orden de visita es distinto**, porque los vecinos salen de la pila en orden
inverso al que se metieron.

Con el grafo de ejemplo:

```
recursivo: 0 1 3 4 5 2
iterativo: 0 2 3 4 5 1
```

Los dos son recorridos en profundidad válidos, simplemente exploran los vecinos
en otro orden.

Otra diferencia: la versión iterativa mete en la pila vértices que quizá ya estén
visitados cuando salgan (por eso comprueba `if (not vis[v])` al sacarlos). La
pila puede llegar a tener Θ(|E|) elementos.

## Coste

| | |
|---|---|
| Tiempo | **Θ(\|V\| + \|E\|)** |
| Memoria | Θ(\|V\|) de marcas + Θ(\|V\|) de pila (recursiva) o Θ(\|E\|) (iterativa) |

Por qué Θ(|V| + |E|): cada vértice se marca una vez (Θ(|V|)) y cada lista de
adyacencia se recorre una vez (la suma de todos los grados es Θ(|E|)).

**Ojo con la recursiva**: en un grafo de 10⁶ vértices en forma de camino, la pila
de llamadas puede desbordar. Ahí hay que usar la iterativa.

## Para qué sirve

- Detectar si el grafo es **conexo** / contar componentes conexas.
- **Detectar ciclos** (si encuentras un vértice que está en la pila actual).
- **Ordenación topológica** (con el postorden invertido; ver sección 5.4 para el
  otro método).
- Componentes fuertemente conexas (Tarjan, Kosaraju).
- Puntos de articulación y puentes.
- Laberintos y backtracking en general (capítulo 07: el backtracking **es** un
  DFS sobre el árbol de soluciones).

## Probarlo

```bash
g++ -std=c++17 dfs.cc -o dfs
printf '6 7\n0 1\n0 2\n1 3\n2 3\n3 4\n4 5\n5 3\n' | ./dfs
```
