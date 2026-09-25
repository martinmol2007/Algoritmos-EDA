# Quicksort

**PDF:** secciones 2.9, 2.10, 2.11 · **Ficheros:** `quick_sort_1.cc`,
`quick_sort_2.cc`, `quick_sort_3.cc`

## En qué consiste

Divide y vencerás, pero al revés que mergesort: el trabajo está en **partir**, no
en combinar.

1. Escoge un **pivote**.
2. **Particiona**: reordena el vector de forma que a la izquierda queden los
   elementos ≤ pivote y a la derecha los ≥ pivote.
3. Ordena recursivamente las dos partes. No hace falta combinar nada.

```
[5 3 9 1 7 2]   pivote = 5
      |
[3 1 2 | 5 9 7]      <- partición
   ↓        ↓
recursión  recursión
```

### La partición de Hoare

```cpp
elem x = v[l];              // pivote: el primer elemento
int i = l - 1, j = r + 1;
for (;;) {
    while (x < v[--j]);     // baja j hasta un elemento <= pivote
    while (v[++i] < x);     // sube i hasta un elemento >= pivote
    if (i >= j) return j;
    swap(v[i], v[j]);
}
```

Devuelve `q` tal que todo `v[l..q]` ≤ todo `v[q+1..r]`. **El pivote no acaba
necesariamente en su posición final**, por eso las llamadas recursivas son
`(l, q)` y `(q+1, r)` y no `(l, q-1)`. Es un error clásico confundirla con la
partición de Lomuto, donde sí se hace `(l, q-1)` y `(q+1, r)`.

Los `while` sin cuerpo funcionan porque el pivote actúa de centinela por los dos
lados: los índices nunca se salen del rango.

## Las tres versiones

| Versión | Idea |
|---|---|
| **1** (2.9) | Pivote = primer elemento. Simple, pero con un vector ya ordenado degenera a Θ(n²) |
| **2** (2.10) | **Pivote aleatorio**, que se lleva a la primera posición con un swap. El caso peor deja de depender de la entrada |
| **3** (2.11) | Deja de partir cuando el trozo tiene < 100 elementos; al final hace **una sola pasada** de insertion sort sobre todo el vector |

La versión 3 es más lista de lo que parece: al terminar las particiones, ningún
elemento está a más de `critical_size` posiciones de su sitio, así que la pasada
final de insertion sort cuesta Θ(n·critical_size) = **Θ(n)**.

Otras estrategias habituales de pivote (no están en el PDF): mediana de tres
(`v[l]`, `v[m]`, `v[r]`) y *median of medians* (garantiza Θ(n log n) pero con
constantes malísimas).

## Coste

| | |
|---|---|
| Mejor caso (particiones equilibradas) | T(n) = 2T(n/2) + Θ(n) ⟹ **Θ(n log n)** |
| Caso medio | **Θ(n log n)** (≈ 1.39 n log₂ n comparaciones) |
| Peor caso (particiones 1 vs n-1) | T(n) = T(n-1) + Θ(n) ⟹ **Θ(n²)** |
| Memoria extra | Θ(log n) de pila en el caso medio, Θ(n) en el peor |
| Estable | **No** |
| In-place | Sí |

Cuándo ocurre el caso peor en la versión 1: vector ya ordenado, ordenado al
revés, o con todos los elementos iguales. Justo las entradas más habituales en la
vida real — de ahí la versión 2.

## Cuándo tiene sentido

Es **el** algoritmo de ordenación de propósito general: in-place, con muy buenas
constantes y muy amigable con la caché (accesos secuenciales). El `sort` de la
STL es *introsort*: quicksort que se pasa a heapsort si la profundidad de
recursión supera 2·log n, y a insertion sort en los trozos pequeños. Es decir,
las tres ideas de este capítulo juntas.

## Probarlo

```bash
g++ -std=c++17 quick_sort_2.cc -o qs
echo "5 3 9 1 7 7 2 8 0 4" | ./qs     # -> 0 1 2 3 4 5 7 7 8 9
```
