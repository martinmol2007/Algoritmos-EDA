# Mergesort (ordenación por fusión)

**PDF:** secciones 2.6, 2.7, 2.8 · **Ficheros:** `merge_sort_1.cc`,
`merge_sort_2.cc`, `merge_sort_3_bottom_up.cc`

## En qué consiste

Divide y vencerás puro:

1. **Divide** el vector por la mitad.
2. **Vence**: ordena cada mitad recursivamente.
3. **Combina**: fusiona las dos mitades ordenadas (`merge`) en un vector auxiliar
   y lo copia de vuelta.

El trabajo de verdad está en el paso 3, no en el 1 (al revés que quicksort).

```
        [5 3 9 1 | 7 2 8 0]
       /                   \
   [5 3 | 9 1]          [7 2 | 8 0]
    ...                     ...
   [1 3 5 9]            [0 2 7 8]
       \                   /
        [0 1 2 3 5 7 8 9]      <- merge
```

### `merge(v, l, m, r)`

Fusiona `v[l..m]` y `v[m+1..r]`, ya ordenados. Usa dos índices que avanzan y
vuelca el menor de los dos en un vector auxiliar `b`. Cuando uno se agota, copia
la cola del otro. Coste **Θ(r-l+1)** y **Θ(r-l+1)** de memoria auxiliar.

El `<=` en `if (v[i] <= v[j])` es lo que hace mergesort **estable**: ante un
empate coge antes el de la mitad izquierda.

## Las tres versiones

| Versión | Idea | Coste |
|---|---|---|
| **1** (2.6) | Recursiva clásica, se parte hasta trozos de 1 elemento | Θ(n log n) |
| **2** (2.7) | Corta la recursión cuando el trozo tiene < 50 elementos y ahí llama a insertion sort | Θ(n log n), mejores constantes |
| **3** (2.8) | **Bottom-up**: sin recursión. Fusiona bloques de tamaño 1, luego 2, luego 4… | Θ(n log n) |

La versión 2 funciona porque el árbol de recursión tiene la mayoría de sus nodos
en las hojas: cortar los últimos niveles elimina muchísimas llamadas, y sobre
trozos de ≤ 50 elementos insertion sort es más rápido que seguir partiendo.

La versión 3 evita la pila de recursión, lo cual la hace apta para ordenar listas
enlazadas (donde además el merge no necesita memoria extra).

## Coste

| | |
|---|---|
| Recurrencia | T(n) = 2·T(n/2) + Θ(n) |
| Mejor / medio / peor | **Θ(n log n)** en los tres casos |
| Memoria extra | **Θ(n)** (el vector auxiliar del merge) |
| Estable | **Sí** |
| In-place | No |

Por el teorema maestro, caso 2: a = 2, b = 2, f(n) = n, n^(log_b a) = n ⟹
T(n) = Θ(n log n).

Que el coste sea el mismo en los tres casos es su gran ventaja frente a
quicksort: **no tiene caso peor patológico**.

## Cuándo tiene sentido

- Cuando necesitas **garantía** de Θ(n log n) (quicksort no la da).
- Cuando necesitas **estabilidad** (`stable_sort` de la STL es mergesort).
- Para **listas enlazadas**: es el mejor algoritmo, y ahí sí es in-place.
- Para **ordenación externa** (datos que no caben en memoria): el merge lee
  secuencialmente, que es justo lo que le gusta al disco.

El inconveniente es la memoria: Θ(n) extra.

## Detalles de implementación

- En el PDF `merge_sort_1` llama a `merge` antes de definirla; en el fichero se
  ha añadido la declaración previa para que compile.
- `merge_sort_2` y `quick_sort_3` usan una función `ins_sort(v, l, r)` que el PDF
  menciona pero no lista. Está implementada en los ficheros.
- `merge_sort_1(v)` hace `v.size() - 1` sobre un `unsigned`: con el vector vacío
  eso da un número enorme. Los `main` de demostración comprueban `not v.empty()`.

## Probarlo

```bash
g++ -std=c++17 merge_sort_1.cc -o ms
echo "5 3 9 1 7 7 2 8 0 4" | ./ms    # -> 0 1 2 3 4 5 7 7 8 9
```
