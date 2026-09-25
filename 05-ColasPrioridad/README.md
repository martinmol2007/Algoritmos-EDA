# 05 · Colas de prioridad (heaps)

**PDF:** capítulo 4 (`Priority Queues`) · **Ficheros:**
`cola_prioridad_recursiva.cc` (4.1), `cola_prioridad_iterativa.cc` (4.2)

## Qué es el TAD

Una cola de prioridad es una colección donde siempre puedes sacar el **mínimo**
(o el máximo, según el convenio) de forma eficiente. Aquí son colas de
**mínimos**.

```cpp
void insert     (const Elem& x);   // Θ(log n)
Elem remove_min ();                // Θ(log n)
Elem minimum    ();                // Θ(1)
int  size       ();                // Θ(1)
bool empty      ();                // Θ(1)
```

## En qué consiste la implementación: el heap

Un **heap** (montículo) es un árbol binario **completo** (todos los niveles
llenos menos posiblemente el último, que se llena de izquierda a derecha) con la
**propiedad de orden del heap**:

> el valor de cada nodo es ≤ que los valores de sus dos hijos

Ojo: **no** es un ABB. No hay relación de orden entre hermanos, y un recorrido
inorden no da nada ordenado. Lo único que se garantiza es que **la raíz es el
mínimo**.

### Por qué se guarda en un vector

Porque un árbol completo no tiene huecos, así que se puede numerar por niveles y
guardar en un vector **sin un solo puntero**:

```
índice:   1    2    3    4    5    6    7
         [5]  [8]  [7] [12] [10] [9] [15]

              5(1)
            /      \
         8(2)      7(3)
        /   \      /   \
     12(4) 10(5) 9(6) 15(7)
```

Con la posición 0 sin usar (el convenio del capítulo 4), las fórmulas salen
limpias:

| | |
|---|---|
| hijo izquierdo de `i` | `2i` |
| hijo derecho de `i` | `2i + 1` |
| padre de `i` | `i / 2` (división entera) |

(El heapsort del capítulo 2 indexa desde 0 y entonces son `2i+1`, `2i+2` y
`(i-1)/2`. Son el mismo árbol, distinto desplazamiento.)

Ventajas: cero memoria de punteros y localidad de caché excelente.

## Las dos operaciones internas

### `shift_up(i)` — usada por `insert`
El elemento nuevo se pone **al final** del vector (que es la primera posición
libre del último nivel) y **sube** mientras sea menor que su padre. Como mucho
sube hasta la raíz: **Θ(log n)**.

### `shift_down(i)` — usada por `remove_min`
La raíz es el mínimo, así que se devuelve. Para no dejar un hueco, se pone el
**último** elemento en la raíz y se **hunde** intercambiándolo con el **menor de
sus dos hijos** mientras haga falta. Como mucho baja hasta una hoja:
**Θ(log n)**.

Detalle importante de `shift_down`: hay que bajar por el **menor** de los dos
hijos. Si bajas por el mayor, rompes la propiedad del heap en el otro lado.

## Coste

| Operación | Coste |
|---|---|
| `insert` | **Θ(log n)** |
| `remove_min` | **Θ(log n)** |
| `minimum` | **Θ(1)** |
| `size`, `empty` | Θ(1) |
| Construir un heap desde n elementos sueltos | Θ(n log n) insertando uno a uno, **Θ(n)** con `make_heap` (ver `02-Ordenacion/Heapsort/`) |
| Memoria | Θ(n), sin punteros |

Todo Θ(log n) porque la altura de un árbol binario completo de n nodos es
exactamente ⌊log₂ n⌋.

## Las dos versiones

| Versión | Diferencia |
|---|---|
| **4.1 recursiva** | `shift_up` y `shift_down` son recursivas y usan `swap` |
| **4.2 iterativa** | Bucles `while` y, sobre todo, **desplaza en vez de intercambiar**: guarda `x`, mueve los elementos una posición y escribe `x` al final |

Un `swap` son 3 asignaciones; un desplazamiento es 1. Con log n niveles eso es
≈3× menos escrituras. Es exactamente la misma optimización que insertion sort v2
(`02-Ordenacion/InsertionSort/`) y que el `sink` de heapsort.

Asintóticamente son idénticas: Θ(log n) las dos.

## Erratas del PDF

En la sección 4.1 el constructor aparece como **`CuaPrio()`** dentro de la clase
`PriorityQueue` — es el nombre catalán de una versión anterior del documento y
así no compila. En el fichero está corregido a `PriorityQueue()`.

## Comparación con otras estructuras

| | Vector ordenado | Lista ordenada | **Heap** | AVL |
|---|---|---|---|---|
| `insert` | Θ(n) | Θ(n) | **Θ(log n)** | Θ(log n) |
| `minimum` | Θ(1) | Θ(1) | **Θ(1)** | Θ(log n) |
| `remove_min` | Θ(n) | Θ(1) | **Θ(log n)** | Θ(log n) |
| Memoria extra | — | punteros | **ninguna** | punteros + alturas |

El heap es el punto dulce cuando solo necesitas el extremo. Si además necesitas
buscar claves arbitrarias, necesitas un árbol.

## Para qué se usa

- **Heapsort** (capítulo 2).
- **Dijkstra** y **Prim** (capítulo 6): sacar repetidamente el vértice/arista de
  coste mínimo. Ahí está el `log` de su coste Θ((|V|+|E|)·log|V|).
- Planificadores de procesos, simulación de eventos discretos, algoritmos A*,
  "los k mejores" de un flujo de datos.

En la STL: **`priority_queue`**, que por defecto es de **máximos**. Para tenerla
de mínimos: `priority_queue<int, vector<int>, greater<int>>`
(ver `01-STL/05-priority_queue-invertida.cc`).

## Probarlo

```bash
g++ -std=c++17 cola_prioridad_iterativa.cc -o cp
echo "5 3 9 1 7 7 2 8 0 4" | ./cp    # -> 0 1 2 3 4 5 7 7 8 9
```
