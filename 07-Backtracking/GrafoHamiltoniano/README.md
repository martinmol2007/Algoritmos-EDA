# Grafo hamiltoniano

**PDF:** sección 6.7 · **Fichero:** `grafo_hamiltoniano.cc`

## El problema

Un **ciclo hamiltoniano** es un ciclo que pasa **exactamente una vez por cada
vértice** del grafo. Un grafo es *hamiltoniano* si tiene alguno.

Se supone que el grafo es conexo y que las listas de adyacencia están ordenadas.

## Hamiltoniano vs. euleriano — no los confundas

| | Euleriano | Hamiltoniano |
|---|---|---|
| Pasa una vez por cada… | **arista** | **vértice** |
| ¿Cómo se decide? | **Θ(\|V\|+\|E\|)**: todos los grados pares (y conexo) | **NP-completo** |

Que dos problemas tan parecidos tengan complejidades tan distintas es uno de los
hechos más llamativos de la teoría de grafos. Para el euleriano hay una
caracterización local trivial (los grados); para el hamiltoniano no se conoce
ninguna, y se conjetura que no existe.

## El algoritmo

Backtracking construyendo el camino vértice a vértice desde el 0.

La representación es lo interesante: en vez de guardar el camino como una lista,
se guarda **por sucesores**:

```cpp
vector<int> s;   // s[v] = siguiente vértice de v en el camino (-1 si no usado)
```

Con esto, `s[u] == -1` responde a la vez a "¿está `u` sin usar?" en Θ(1), y
deshacer es una sola asignación.

```cpp
for (int u : G[v]) {
    if (s[u] == -1) {
        s[v] = u;
        recursive(u, t+1);
        s[v] = -1;              // deshacer
        if (found) return;      // poda por parada
    }
}
```

## Cerrar el ciclo

Cuando el camino tiene `n` vértices (`t == n`), falta comprobar que se puede
**volver al 0**:

```cpp
if (not G[v].empty() and G[v][0] == 0) { ... }
```

Aquí es donde importa que **las listas de adyacencia estén ordenadas**: si lo
están y el 0 es vecino de `v`, tiene que ser el **primero** de la lista, así que
basta con mirar `G[v][0]`. Es un Θ(1) en vez de un Θ(grado(v)).

Por eso `read_graph()` hace `sort(G[u].begin(), G[u].end())`. Si te saltas ese
`sort`, el algoritmo falla silenciosamente.

## Coste

| | |
|---|---|
| Caso peor | **exponencial** (el problema es NP-completo) |
| En la práctica | depende muchísimo del grafo: en grafos densos encuentra ciclo enseguida; en grafos que *no* son hamiltonianos hay que explorarlo casi todo |

Demostrar que un grafo **no** es hamiltoniano es el caso caro: no hay poda que
valga, hay que agotar el espacio.

## Formato de entrada

```
n                       número de vértices
d  v1 v2 ... vd         para cada vértice: su grado y sus vecinos
...
```

Ejemplo (un ciclo de 5 vértices):

```
5
2 1 4
2 0 2
2 1 3
2 2 4
2 3 0
```

## Relación con el TSP

El TSP (sección 6.8) es la versión **de optimización** de esto: en vez de
preguntar si existe un ciclo hamiltoniano, pregunta cuál es el **más barato**.
De hecho, la NP-dificultad del TSP se demuestra reduciendo el ciclo hamiltoniano
a él.

## Probarlo

```bash
g++ -std=c++17 grafo_hamiltoniano.cc -o hm
printf '5\n2 1 4\n2 0 2\n2 1 3\n2 2 4\n2 3 0\n' | ./hm
# 0 1 2 3 4
```
