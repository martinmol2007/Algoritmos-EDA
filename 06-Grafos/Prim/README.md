# Prim · Árbol de expansión mínimo

**PDF:** sección 5.6 · **Fichero:** `prim.cc`

## En qué consiste

Un **árbol de expansión mínimo** (MST) de un grafo no dirigido, conexo y con
pesos es un subconjunto de aristas que conecta todos los vértices, sin ciclos, y
con el **peso total mínimo** posible. Tiene siempre exactamente |V|-1 aristas.

Prim es **voraz** y funciona así: mantiene **un único árbol** que va creciendo.
En cada paso añade la **arista más barata que sale del árbol** hacia un vértice
que aún no está dentro.

```
 {0}                           coge la más barata que sale de {0}
 {0,1}                         coge la más barata que sale de {0,1}
 {0,1,2}                       ...
```

Es casi idéntico a Dijkstra. La única diferencia:

| | Dijkstra | Prim |
|---|---|---|
| Prioridad de `v` | `d[u] + peso(u,v)` — coste **desde el origen** | `peso(u,v)` — coste de **la arista sola** |

## El truco del signo cambiado

`priority_queue` es de **máximos** por defecto. En vez de redefinir el
comparador, el PDF **inserta los pesos con el signo cambiado**:

```cpp
Q.push({-p, {v, w}});
```

Así el máximo de los `-p` es el mínimo de los `p`. Funciona, pero es confuso —
como dice el propio PDF, "alternativamente podríamos haber redefinido el orden de
la cola de prioridad", que es lo que hace Dijkstra con `greater<WArc>`.

La arista ficticia inicial `{0.0, {0, 0}}` mete el vértice 0 en el árbol para
arrancar. Como su prioridad es 0.0 y todas las demás son negativas, sale la
primera.

## Coste

| | |
|---|---|
| Con cola de prioridad | **Θ((\|V\| + \|E\|)·log\|V\|)** |
| Con matriz de adyacencia y búsqueda lineal | Θ(\|V\|²) — mejor en grafos densos |
| Memoria | Θ(\|V\| + \|E\|) |

Igual que en Dijkstra, el `log` viene de la cola, y las entradas obsoletas se
descartan con `if (not used[v])`.

## Prim vs. Kruskal

| | Prim | Kruskal (extra, en `../Kruskal/`) |
|---|---|---|
| Invariante | **un árbol** que crece | un **bosque** que se fusiona |
| Auxiliar | cola de prioridad | ordenación + Union-Find |
| Coste | Θ((\|V\|+\|E\|)·log\|V\|) | Θ(\|E\|·log\|E\|) |
| Grafos densos | mejor | peor |
| Grafo no conexo | solo la componente del vértice 0 | el **bosque** de expansión mínimo completo |

Los dos son correctos por la misma razón (**propiedad del corte**): para
cualquier partición de los vértices en dos, la arista más barata que cruza la
partición está en algún MST.

## Erratas del PDF

1. `Q.push({0.0, {0, 0}));` — paréntesis mal cerrados, no compila. Corregido a
   `Q.push({0.0, {0, 0}});`.
2. `double p = Q.top().first;` no se usa para nada (y la variable se vuelve a
   declarar dentro del bucle interno). Se ha dejado con un `(void)p;` para
   silenciar el aviso.
3. `MST` escribe en `parent` sin redimensionarlo: el llamador tiene que crear el
   vector con talla |V|. El `main` del fichero lo hace.

## Probarlo

```bash
g++ -std=c++17 prim.cc -o prim
printf '5 7\n0 1 2\n0 3 6\n1 2 3\n1 3 8\n1 4 5\n2 4 7\n3 4 9\n' | ./prim
# peso total del MST = 16
```
