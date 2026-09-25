# BFS · Recorrido en anchura

**PDF:** sección 5.3 · **Fichero:** `bfs.cc`

## En qué consiste

"Visita primero todo lo que está a distancia 1, luego todo lo que está a
distancia 2, etc."

Es exactamente el DFS iterativo **cambiando la pila por una cola**. Ese único
cambio lo convierte de "tira hacia delante" a "explora por capas".

```
capa 0:       0
capa 1:     1   2
capa 2:       3
capa 3:       4
```

## Las versiones del fichero

### `bfs_1` (sección 5.3)
Traducción directa del DFS iterativo: pila → cola. Funciona, pero **encola cada
vértice tantas veces como su grado de entrada**, porque marca al desencolar. La
cola puede crecer hasta Θ(|E|).

### `bfs_2` (sección 5.3) ← la buena
Marca el vértice **al encolarlo**, no al desencolarlo. Así cada vértice entra en
la cola **exactamente una vez** y la cola nunca supera |V| elementos.

Es la diferencia entre "visitado" y "encontrado": un vértice está *encontrado* en
cuanto alguien lo mete en la cola, aunque todavía no se haya procesado.

### `bfs_distancias` (extra, no está en el PDF)
BFS desde un origen `s` calculando `d[v]` = número mínimo de aristas de `s` a `v`.

**Esta es la propiedad importante del BFS**: en un grafo **sin pesos** (o con
todos los pesos iguales), el BFS da los **caminos mínimos**. Es correcto
precisamente porque explora por capas: cuando llegas a un vértice por primera
vez, es por el camino más corto.

Para hacer caminos mínimos con pesos hace falta Dijkstra.

## Coste

| | |
|---|---|
| Tiempo | **Θ(\|V\| + \|E\|)** |
| Memoria | Θ(\|V\|) (con `bfs_2`) |

## DFS vs. BFS

| | DFS | BFS |
|---|---|---|
| Estructura | pila (o recursión) | **cola** |
| Explora | en profundidad | por capas |
| Caminos mínimos sin pesos | **no** | **sí** |
| Memoria típica | Θ(altura) | Θ(anchura) — puede ser mucho mayor |
| Natural para | ciclos, componentes, topológico, backtracking | distancias, "el más cercano", niveles |

El coste asintótico es el mismo. La elección depende de qué necesites.

## Para qué sirve

- Camino más corto en número de pasos (laberintos, movimientos de caballo,
  grados de separación).
- Recorrido **por niveles** de un árbol (ver `04-Diccionarios/ABB/recorridos.cc`).
- Comprobar si un grafo es **bipartito** (coloreando por capas).
- Componentes conexas (igual que DFS).

## Probarlo

```bash
g++ -std=c++17 bfs.cc -o bfs
printf '6 7\n0 1\n0 2\n1 3\n2 3\n3 4\n4 5\n5 3\n' | ./bfs
# distancias desde 0: 0 1 1 2 3 4
```
