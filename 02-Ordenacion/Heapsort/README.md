# Heapsort (ordenación por montículo)

**PDF:** secciones 2.12, 2.13 · **Ficheros:** `heap_sort_0_con_TAD.cc`,
`heap_sort.cc`

## En qué consiste

Un **heap** (montículo) es un árbol binario *completo* en el que cada nodo es ≥
que sus hijos (max-heap). Un árbol así se guarda en un vector sin punteros: el
hijo izquierdo de `i` es `2i+1`, el derecho `2i+2` y el padre es `(i-1)/2`
(indexando desde 0, que es lo que hace el capítulo 2; el capítulo 4 indexa desde
1 y entonces son `2i`, `2i+1` y `i/2`).

Heapsort tiene dos fases:

1. **`make_heap`**: convierte el vector en un max-heap. Coste **Θ(n)** (no
   Θ(n log n): la mayoría de nodos están cerca de las hojas y se hunden poco).
2. **n-1 iteraciones**: intercambia la raíz (el máximo) con el último elemento
   del heap, reduce el heap en 1 y **hunde** (`sink`) la nueva raíz. Cada `sink`
   cuesta Θ(log n).

```
[9 8 7 3 5 1] heap        ->   swap raíz/último
[1 8 7 3 5 | 9]                sink(1)
[8 5 7 3 1 | 9]                ...
```

Como el máximo se va colocando al final y el heap encoge, el vector queda
ordenado **de menor a mayor** sin memoria extra.

### `sink(v, n, i)`

Hunde `v[i]` dentro del heap `v[0..n-1]`: mientras algún hijo sea mayor,
intercambia con el **mayor de los dos hijos**. Igual que insertion sort v2, no
hace `swap` sino que va desplazando y escribe `x` al final.

## Las dos versiones

| Versión | Idea | Memoria |
|---|---|---|
| **1** (2.12) | Usa el TAD `priority_queue` de la STL: mete los n elementos y los va sacando | Θ(n) extra |
| **2** (2.13) | Construye el heap **dentro del propio vector** | Θ(1) extra |

La versión 1 es trivial de escribir y sirve para entender la idea; la versión 2
es el heapsort de verdad.

## Coste

| | |
|---|---|
| `make_heap` | **Θ(n)** |
| Fase de extracción | n·Θ(log n) = **Θ(n log n)** |
| Total mejor / medio / peor | **Θ(n log n)** en los tres casos |
| Memoria extra | **Θ(1)** (versión 2) |
| Estable | No |
| In-place | Sí (versión 2) |

## Cuándo tiene sentido

Es el único algoritmo de comparación que consigue a la vez **Θ(n log n)
garantizado** y **Θ(1) de memoria**. Mergesort le gana en estabilidad pero gasta
Θ(n); quicksort le gana en constantes pero tiene caso peor Θ(n²).

En la práctica es más lento que quicksort porque sus accesos a memoria saltan
(`i → 2i+1`) y destrozan la caché. Su uso típico es como **red de seguridad**:
introsort empieza con quicksort y se pasa a heapsort si la recursión se va de
madre, para garantizar Θ(n log n) sin renunciar a la velocidad del caso normal.

## Detalle de implementación

El fichero define su propia `make_heap`, que convive con `std::make_heap` gracias
al `using namespace std;`. No hay ambigüedad porque las signaturas son distintas
(la nuestra toma un `vector<elem>&`, la de la STL dos iteradores).

## Probarlo

```bash
g++ -std=c++17 heap_sort.cc -o hs
echo "5 3 9 1 7 7 2 8 0 4" | ./hs     # -> 0 1 2 3 4 5 7 7 8 9
```
