# Dijkstra · Caminos mínimos desde un origen

**PDF:** sección 5.5 · **Fichero:** `dijkstra.cc`

## En qué consiste

Calcula la distancia mínima desde un vértice origen `s` a **todos** los demás,
en un grafo dirigido con **pesos no negativos**.

Es un algoritmo **voraz**. Mantiene un conjunto `S` de vértices cuya distancia ya
es **definitiva**, y repite:

1. De los vértices que aún no están en `S`, coge el de **menor `d[]`**.
2. Márcalo como definitivo.
3. **Relaja** todos sus arcos salientes: si ir a `v` pasando por `u` es más
   barato que lo que tenías, actualiza `d[v]` y anota `p[v] = u`.

```cpp
if (d[v] > d[u] + c) {   // relajación del arco (u,v)
    d[v] = d[u] + c;
    p[v] = u;
    Q.push(WArc(d[v], v));
}
```

## Por qué funciona (y por qué necesita pesos ≥ 0)

El paso voraz dice: *"el vértice no definitivo con menor `d[]` ya tiene su
distancia final"*. Eso es cierto porque cualquier otro camino hacia él tendría
que pasar por algún vértice todavía no definitivo, con `d[]` mayor o igual, y
después **sumar** aristas — que solo pueden hacerlo crecer.

Con un **peso negativo** ese razonamiento se rompe: una arista negativa podría
abaratar el camino después. Por eso, con pesos negativos, hay que usar
**Bellman-Ford**.

## El truco de la cola de prioridad

La versión "de libro" necesitaría una operación `decrease_key` para bajar la
prioridad de un vértice ya encolado. La `priority_queue` de la STL no la tiene,
así que el PDF hace lo habitual:

> en vez de disminuir la prioridad de un vértice, **se reinserta** con la nueva
> prioridad

Consecuencia: un vértice puede estar varias veces en la cola (hasta su grado de
entrada). Las entradas obsoletas se descartan con esta línea:

```cpp
if (not S[u]) { ... }      // si ya es definitivo, la entrada está obsoleta
```

Como la cola llega a tener Θ(|E|) elementos, el coste sigue siendo el mismo.

Detalle: `priority_queue<WArc, vector<WArc>, greater<WArc>>` es una cola de
**mínimos** (ver `01-STL/05-priority_queue-invertida.cc`). Y `WArc` es
`pair<double,int>` con el **peso primero**, para que el `pair` se ordene por
peso.

## Coste

| | |
|---|---|
| Con cola de prioridad binaria | **Θ((\|V\| + \|E\|)·log\|V\|)** |
| Con matriz / búsqueda lineal del mínimo | Θ(\|V\|²) — mejor si el grafo es **muy denso** |
| Con heap de Fibonacci | Θ(\|E\| + \|V\|·log\|V\|) — teórico, constantes malas |
| Memoria | Θ(\|V\| + \|E\|) |

El `log` viene de la cola de prioridad: hay Θ(|E|) inserciones y extracciones,
cada una Θ(log |E|) = Θ(log |V|²) = Θ(log |V|).

## Reconstruir el camino, no solo la distancia

El vector `p` guarda el **predecesor** de cada vértice en su camino mínimo. Para
obtener el camino de `s` a `v`, se va hacia atrás desde `v` siguiendo `p` hasta
llegar a `-1`, y se da la vuelta al resultado. El `main` del fichero lo hace.

## Errata del PDF

El código usa `infinit` (catalán, de una versión anterior). En `eda.hh` la
constante se llama **`infinity`**. En el fichero está corregido.

## Probarlo

```bash
g++ -std=c++17 dijkstra.cc -o dij
printf '5 7 0\n0 1 10\n0 3 5\n1 2 1\n3 1 3\n3 2 9\n3 4 2\n4 2 6\n' | ./dij
# d[1] = 8   camino: 0 3 1
# d[2] = 9   camino: 0 3 1 2
```
