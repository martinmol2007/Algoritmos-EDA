# Bellman-Ford · Caminos mínimos con pesos negativos · EXTRA

> No está en el PDF, que solo da Dijkstra. Es la respuesta a "¿y si hay pesos
> negativos?".

**Fichero:** `bellman_ford.cc`

## Por qué hace falta

Dijkstra es voraz: da por **definitivo** el vértice con menor `d[]` y no lo vuelve
a mirar. Ese razonamiento solo vale si las aristas **nunca abaratan** un camino,
es decir, si todos los pesos son ≥ 0.

Con un arco negativo, un camino que parecía caro puede acabar siendo el más
barato, y Dijkstra da resultados **incorrectos** (sin avisar).

## En qué consiste

En vez de ser listo, Bellman-Ford es bruto: **relaja todos los arcos |V|-1
veces**.

```cpp
for (int i = 0; i < n - 1; ++i) {
    for (const Arc& a : arcs) {
        if (d[a.u] + a.w < d[a.v]) {
            d[a.v] = d[a.u] + a.w;
            p[a.v] = a.u;
        }
    }
}
```

### Por qué |V|-1 pasadas

Un camino mínimo no puede repetir vértices (si los repitiera, habría un ciclo, y
quitarlo no lo empeoraría), así que tiene **como mucho |V|-1 aristas**.

La invariante es: **después de la pasada `i`, todas las distancias cuyo camino
mínimo usa ≤ `i` aristas ya son correctas**. Con |V|-1 pasadas, están todas.

La optimización del `bool cambio` corta antes si ya ha convergido — habitual en
la práctica, aunque no cambia el caso peor.

## Detección de ciclos negativos

Si después de las |V|-1 pasadas **todavía se puede relajar algún arco**, es que
hay un **ciclo de peso negativo** alcanzable desde el origen. Y entonces el
problema *no tiene solución*: podrías dar vueltas al ciclo infinitas veces y
bajar la distancia todo lo que quisieras.

```cpp
for (const Arc& a : arcs) {
    if (d[a.u] + a.w < d[a.v]) return false;   // ciclo negativo
}
```

Esta capacidad de **detectar** ciclos negativos es útil por sí misma: es como se
detecta el arbitraje en mercados de divisas (tomando logaritmos de los tipos de
cambio, un ciclo de producto > 1 se convierte en un ciclo de suma < 0).

## Coste

| | |
|---|---|
| Tiempo | **Θ(\|V\|·\|E\|)** |
| Memoria | Θ(\|V\| + \|E\|) |

Mucho peor que Dijkstra (Θ((|V|+|E|)·log|V|)). Úsalo solo si realmente tienes
pesos negativos.

## Comparación

| | BFS | Dijkstra | Bellman-Ford | Floyd-Warshall |
|---|---|---|---|---|
| Pesos | ninguno | ≥ 0 | **cualquiera** | cualquiera |
| Orígenes | uno | uno | uno | **todos** |
| Coste | Θ(V+E) | Θ((V+E)log V) | Θ(V·E) | Θ(V³) |
| Detecta ciclos negativos | — | no | **sí** | sí |

Hay una mejora práctica llamada **SPFA** (*Shortest Path Faster Algorithm*), que
es Bellman-Ford con una cola de vértices "pendientes de relajar": mismo caso peor
Θ(|V|·|E|), pero mucho más rápido en grafos normales.

## Probarlo

```bash
g++ -std=c++17 bellman_ford.cc -o bf
printf '5 8 0\n0 1 -1\n0 2 4\n1 2 3\n1 3 2\n1 4 2\n3 2 5\n3 1 1\n4 3 -3\n' | ./bf
# d[0]=0  d[1]=-1  d[2]=2  d[3]=-2  d[4]=1
```
