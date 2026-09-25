# Kruskal · Árbol de expansión mínimo · EXTRA

> No está en el PDF, que solo da Prim. Es el otro algoritmo clásico de MST y el
> uso canónico del Union-Find.

**Fichero:** `kruskal.cc`

## En qué consiste

También es **voraz**, pero con una estrategia distinta a la de Prim:

1. **Ordena todas las aristas** por peso creciente.
2. Recórrelas en ese orden. Coge cada arista **si no forma ciclo** con las ya
   cogidas; si lo forma, descártala.
3. Para cuando tengas |V|-1 aristas.

```
aristas ordenadas: (0,1,2) (1,2,3) (1,4,5) (0,3,6) (2,4,7) (1,3,8) (3,4,9)
coge (0,1,2)  -> {0,1}
coge (1,2,3)  -> {0,1,2}
coge (1,4,5)  -> {0,1,2,4}
coge (0,3,6)  -> {0,1,2,3,4}   ya son 4 = |V|-1, para
descarta (2,4,7): 2 y 4 ya están conectados -> ciclo
```

Mientras Prim hace crecer **un solo árbol**, Kruskal mantiene un **bosque** de
árboles sueltos que se van fusionando.

## El papel del Union-Find

La parte no trivial es *"¿esta arista forma ciclo?"*. La respuesta es sí
exactamente cuando **sus dos extremos ya están en la misma componente**. Un
Union-Find responde a eso en tiempo casi constante:

```cpp
if (uf.unite(e.u, e.v)) {    // devuelve false si ya estaban juntos
    mst.push_back(e);
}
```

`unite` hace las dos cosas a la vez: comprueba y une. Muy limpio.

## Coste

| | |
|---|---|
| Ordenar las aristas | **Θ(\|E\|·log\|E\|)** ← domina |
| Union-Find | Θ(\|E\|·α(\|V\|)) ≈ Θ(\|E\|) |
| **Total** | **Θ(\|E\|·log\|E\|) = Θ(\|E\|·log\|V\|)** |
| Memoria | Θ(\|V\| + \|E\|) |

(`log|E| = Θ(log|V|)` porque `|E| ≤ |V|²` y por tanto `log|E| ≤ 2·log|V|`.)

Si las aristas **ya vienen ordenadas**, o se pueden ordenar en tiempo lineal
(pesos enteros pequeños → counting sort), Kruskal baja a casi Θ(|E|·α(|V|)).

## Prim vs. Kruskal

| | Prim | Kruskal |
|---|---|---|
| Coste | Θ((\|V\|+\|E\|)·log\|V\|) | Θ(\|E\|·log\|E\|) |
| Grafo denso (\|E\| ≈ \|V\|²) | **mejor** | peor |
| Grafo disperso (\|E\| ≈ \|V\|) | similar | **mejor** |
| Aristas ya ordenadas | no ayuda | **mucho mejor** |
| Grafo **no conexo** | solo la componente del vértice inicial | **bosque de expansión mínimo completo** |
| Implementación | cola de prioridad | ordenación + Union-Find |

## Por qué es correcto

Por la **propiedad del corte**: para cualquier partición de los vértices en dos
conjuntos, la arista más barata que cruza la partición pertenece a algún MST.
Cuando Kruskal coge una arista, es la más barata que cruza el corte entre las dos
componentes que une. Prim usa exactamente el mismo argumento, solo que con un
corte fijo (árbol / resto).

## Probarlo

```bash
g++ -std=c++17 kruskal.cc -o kr
printf '5 7\n0 1 2\n0 3 6\n1 2 3\n1 3 8\n1 4 5\n2 4 7\n3 4 9\n' | ./kr
# peso total del MST = 16    (el mismo que Prim)
```
