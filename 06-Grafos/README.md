# 06 · Grafos

Capítulo 5 del PDF (`Graphs`) más cuatro algoritmos extra.

## Representación (sección 5.1)

El tipo está en `00-Comun/graph.hh`:

```cpp
typedef vector<vector<int>> graph;
```

Es una **tabla de listas de adyacencia**: `G[u]` es el vector de vecinos de `u`.
Los vértices son los enteros de `0` a `|V|-1`. El tipo es para grafos
**dirigidos**; para uno no dirigido, cada arista se guarda como **dos arcos**.

### Listas vs. matriz de adyacencia

| | Listas `vector<vector<int>>` | Matriz `bool[n][n]` |
|---|---|---|
| Memoria | Θ(\|V\| + \|E\|) | Θ(\|V\|²) |
| ¿Existe el arco (u,v)? | Θ(grado(u)) | **Θ(1)** |
| Recorrer los vecinos de u | **Θ(grado(u))** | Θ(\|V\|) |
| Buena para | grafos **dispersos** | grafos **densos** |

Casi todos los grafos reales son dispersos (|E| ≈ |V|, no |V|²), así que las
listas ganan. La excepción es Floyd-Warshall, que trabaja con la matriz.

## Tabla comparativa

| Algoritmo | Sección | Para qué | Coste |
|---|---|---|---|
| DFS | 5.2 | recorrido en profundidad | Θ(\|V\| + \|E\|) |
| BFS | 5.3 | recorrido en anchura, **caminos mínimos sin pesos** | Θ(\|V\| + \|E\|) |
| Ordenación topológica | 5.4 | ordenar un DAG por dependencias | Θ(\|V\| + \|E\|) |
| Dijkstra | 5.5 | caminos mínimos desde un origen, **pesos ≥ 0** | Θ((\|V\|+\|E\|)·log\|V\|) |
| Prim | 5.6 | árbol de expansión mínimo | Θ((\|V\|+\|E\|)·log\|V\|) |
| Union-Find | extra | conjuntos disjuntos | Θ(α(n)) ≈ Θ(1) amortizado |
| Kruskal | extra | árbol de expansión mínimo | Θ(\|E\|·log\|E\|) |
| Bellman-Ford | extra | caminos mínimos con **pesos negativos** | Θ(\|V\|·\|E\|) |
| Floyd-Warshall | extra | caminos mínimos entre **todos los pares** | Θ(\|V\|³) |

## Cómo elegir el algoritmo de caminos mínimos

```
¿El grafo tiene pesos?
├── No                          -> BFS                  Θ(V+E)
└── Sí
    ├── ¿Todos los pesos >= 0?
    │   ├── Sí                  -> Dijkstra             Θ((V+E) log V)
    │   └── No                  -> Bellman-Ford         Θ(V·E)
    └── ¿Necesitas TODOS los pares?
        ├── grafo denso         -> Floyd-Warshall       Θ(V³)
        └── grafo disperso      -> V veces Dijkstra     Θ(V·(V+E) log V)
```

## MST: Prim vs. Kruskal

Los dos son **voraces** y los dos dan un árbol de expansión de peso mínimo. La
diferencia es qué invariante mantienen:

| | Prim | Kruskal |
|---|---|---|
| Invariante | un **único árbol** que crece | un **bosque** de árboles que se fusionan |
| Estructura auxiliar | cola de prioridad | ordenación + **Union-Find** |
| Coste | Θ((\|V\|+\|E\|)·log\|V\|) | Θ(\|E\|·log\|E\|) |
| Mejor para | grafos densos | grafos dispersos, o aristas ya ordenadas |
| Grafo no conexo | solo da el árbol de su componente | da el **bosque** de expansión mínimo |

## Formato de entrada de las demos

Todos los `main` de este capítulo leen:

```
n m            (número de vértices y de arcos)
u v            (m líneas; para los con pesos: u v peso)
```

Salvo Dijkstra y Bellman-Ford, que leen `n m s` con `s` = vértice origen.

## Contenido

| Carpeta | Sección | Fichero |
|---|---|---|
| `DFS/` | 5.2 | `dfs.cc` (recursivo + iterativo) |
| `BFS/` | 5.3 | `bfs.cc` (2 versiones + distancias) |
| `OrdenacionTopologica/` | 5.4 | `topological_sort.cc` |
| `Dijkstra/` | 5.5 | `dijkstra.cc` |
| `Prim/` | 5.6 | `prim.cc` |
| `UnionFind/` | extra | `union_find.cc` |
| `Kruskal/` | extra | `kruskal.cc` |
| `BellmanFord/` | extra | `bellman_ford.cc` |
| `FloydWarshall/` | extra | `floyd_warshall.cc` |
