# TSP · Problema del viajante

**PDF:** sección 6.8 · **Fichero:** `tsp.cc`

## El problema

Un comercial debe visitar `n` ciudades. La distancia entre `i` y `j` es
`D[i][j]`. Quiere **salir de su ciudad, visitar cada una de las demás exactamente
una vez, y volver al punto de partida**, minimizando la distancia total.

Es probablemente el problema de optimización combinatoria más estudiado de la
historia.

## El algoritmo

Backtracking con la misma representación por sucesores que el grafo
hamiltoniano (`s[v]` = siguiente ciudad de `v`), más una poda por coste:

```cpp
for (int u = 0; u < n; ++u) if (u != v and s[u] == -1) {
    if (c + M[v][u] < best) {           // poda
        s[v] = u;
        recursive(u, t+1, c+M[v][u]);
        s[v] = -1;
    }
}
```

La poda es la más sencilla posible: **si el coste acumulado ya supera el del
mejor recorrido conocido, abandona**. Como las distancias son ≥ 0, continuar solo
puede empeorar.

Cuando el camino está completo (`t == n`), se cierra sumando `M[v][0]`.

## Una poda mejor (no está en el PDF)

La poda del PDF solo mira lo ya gastado. Una cota **branch and bound** de verdad
sumaría también una estimación optimista de lo que queda, como hace la asignación
de tareas. Por ejemplo:

```
cota = c + (suma de la arista más barata que sale de cada ciudad no visitada)
```

o, mejor todavía, el peso del **MST** de las ciudades que quedan (que es una cota
inferior clásica y bastante ajustada para el TSP). Implementarlo es un buen
ejercicio: se combina el capítulo 06 (Prim/Kruskal) con este.

## Coste

| | |
|---|---|
| Espacio de búsqueda | **(n-1)!** recorridos distintos |
| Con la poda | exponencial, pero n ≈ 10-12 es instantáneo |
| n = 15 | ya se nota mucho |

El TSP es **NP-difícil**. No se conoce algoritmo polinómico.

Para valores de n mayores, las alternativas reales son:

| Método | Coste | Qué da |
|---|---|---|
| Backtracking (este) | Θ(n!) | óptimo |
| **Held-Karp** (programación dinámica sobre subconjuntos) | Θ(n²·2ⁿ) | óptimo, hasta n ≈ 20-25 |
| Programación lineal entera + planos de corte | — | óptimo, miles de ciudades en la práctica |
| Heurística del **vecino más cercano** | Θ(n²) | ~25% peor que el óptimo |
| **Christofides** (con MST + emparejamiento) | Θ(n³) | garantiza ≤ 1.5× el óptimo, si se cumple la desigualdad triangular |
| 2-opt / Lin-Kernighan | — | muy cerca del óptimo en la práctica |

## El `main`

Genera `n` ciudades con coordenadas aleatorias y construye la matriz de
distancias euclídeas. Mide el tiempo con `now()` de `eda.hh`.

Fíjate en que con distancias euclídeas se cumple la **desigualdad triangular**,
lo que hace que el problema sea algo más tratable (es el caso al que se aplica
Christofides).

## Probarlo

```bash
g++ -std=c++17 tsp.cc -o tsp
echo 9 | ./tsp      # instantáneo
echo 12 | ./tsp     # se nota
```
