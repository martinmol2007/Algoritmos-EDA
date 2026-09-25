# Floyd-Warshall · Caminos mínimos entre todos los pares · EXTRA

> No está en el PDF. Resuelve un problema distinto: no "desde un origen", sino
> "entre todos los pares a la vez".

**Fichero:** `floyd_warshall.cc`

## En qué consiste

Es **programación dinámica** sobre los vértices intermedios permitidos.

Define `d[k][i][j]` = longitud del camino mínimo de `i` a `j` usando como
vértices **intermedios** solo los de `{0, 1, …, k-1}`.

La recurrencia es preciosa: para añadir el vértice `k` al conjunto permitido, o
bien el camino mínimo no lo usa (y no cambia), o bien lo usa exactamente una vez
(y entonces se parte en `i → k` y `k → j`):

```
d[k+1][i][j] = min( d[k][i][j],  d[k][i][k] + d[k][k][j] )
```

Y como los términos del lado derecho con índice `k` no cambian al actualizar, se
puede aplicar **sobre la misma matriz**, sin la dimensión `k`:

```cpp
for (int k = 0; k < n; ++k)          // ¡k es el bucle EXTERNO!
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
```

**El error clásico es poner `k` en el bucle interno.** El orden de los bucles no
es una elección de estilo: `k` tiene que ir fuera, porque la dimensión que se
está eliminando es la suya.

Cinco líneas para resolver todos los pares. Es de los algoritmos con mejor
relación potencia/líneas de código que existen.

## Coste

| | |
|---|---|
| Tiempo | **Θ(\|V\|³)** siempre (tres bucles anidados, sin condiciones) |
| Memoria | **Θ(\|V\|²)** (la matriz) |

Usa **matriz de adyacencia**, no listas. Por eso es apropiado para grafos
**densos**.

## Cuándo usarlo en vez de |V| Dijkstras

| | Floyd-Warshall | \|V\| × Dijkstra |
|---|---|---|
| Coste | Θ(\|V\|³) | Θ(\|V\|·(\|V\|+\|E\|)·log\|V\|) |
| Grafo denso (\|E\| ≈ \|V\|²) | **mejor** | Θ(\|V\|³ log\|V\|) |
| Grafo disperso (\|E\| ≈ \|V\|) | Θ(\|V\|³) | **mejor**: Θ(\|V\|² log\|V\|) |
| Pesos negativos | **sí** | no |
| Código | 5 líneas | bastante más |

En la práctica, para |V| ≲ 400 Floyd-Warshall es la opción cómoda casi siempre.

## Detección de ciclos negativos

Admite pesos negativos, pero **no ciclos negativos**. Se detectan mirando la
diagonal: si al acabar algún `d[i][i] < 0`, es que `i` está en un ciclo de peso
negativo.

## Variantes con la misma estructura

El esqueleto de tres bucles sirve para más cosas cambiando la operación:

| Problema | `min`/`+` se cambia por |
|---|---|
| Caminos mínimos | `min`, `+` |
| **Cierre transitivo** (¿hay camino de i a j?) | `or`, `and` |
| Camino de **capacidad máxima** (cuello de botella) | `max`, `min` |
| Contar caminos | `+`, `×` |

Es el mismo álgebra con distintos semianillos.

## Reconstruir los caminos

Si además del coste quieres el camino, se guarda una matriz `next[i][j]` con el
siguiente vértice del camino de `i` a `j`, y se actualiza cuando se mejora
`d[i][j]`. El fichero solo calcula las distancias.

## Probarlo

```bash
g++ -std=c++17 floyd_warshall.cc -o fw
printf '4 5\n0 1 5\n0 3 10\n1 2 3\n2 3 1\n3 0 2\n' | ./fw
```
