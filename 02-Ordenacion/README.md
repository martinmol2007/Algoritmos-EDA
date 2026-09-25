# 02 · Ordenación

Capítulo 2 del PDF (`Sorting`) más tres algoritmos extra que no aparecen en él.

## Tabla comparativa

| Algoritmo | Mejor caso | Caso medio | Peor caso | Memoria extra | Estable | In-place |
|---|---|---|---|---|---|---|
| Selection sort | Θ(n²) | Θ(n²) | Θ(n²) | Θ(1) | No | Sí |
| Insertion sort | Θ(n) | Θ(n²) | Θ(n²) | Θ(1) | Sí | Sí |
| Bubblesort | Θ(n²)\* | Θ(n²) | Θ(n²) | Θ(1) | Sí | Sí |
| Mergesort | Θ(n log n) | Θ(n log n) | Θ(n log n) | Θ(n) | Sí | No |
| Quicksort | Θ(n log n) | Θ(n log n) | Θ(n²) | Θ(log n) pila | No | Sí |
| Heapsort | Θ(n log n) | Θ(n log n) | Θ(n log n) | Θ(1) | No | Sí |
| Counting sort | Θ(n+k) | Θ(n+k) | Θ(n+k) | Θ(n+k) | Sí | No |
| Radix sort | Θ(d(n+b)) | Θ(d(n+b)) | Θ(d(n+b)) | Θ(n+b) | Sí | No |
| Quickselect | Θ(n) | Θ(n) | Θ(n²) | Θ(1) | — | Sí |

\* La versión del PDF no detecta que el vector ya esté ordenado, así que su mejor
caso también es Θ(n²). Con un flag de "no ha habido intercambios" bajaría a Θ(n).

k = rango de valores, d = número de dígitos, b = base.

## Cota inferior

Cualquier algoritmo de ordenación **basado en comparaciones** necesita Ω(n log n)
comparaciones en el caso peor. La demostración es el árbol de decisión: hay n!
permutaciones posibles, un árbol binario con n! hojas tiene altura ≥ log₂(n!) =
Θ(n log n).

Counting sort y radix sort escapan a esta cota porque **no comparan**: usan el
valor de la clave como índice. Por eso solo funcionan con claves enteras (o
mapeables a enteros) de rango acotado.

## Qué usar en la práctica

- En un examen/entrega normal: `sort` de la STL (introsort: quicksort + heapsort
  + insertion sort). Θ(n log n) garantizado.
- Si necesitas estabilidad: `stable_sort` (mergesort).
- Si solo necesitas el k-ésimo o la mediana: `nth_element` (quickselect).
- Si las claves son enteros pequeños: counting sort gana con diferencia.

## Contenido

| Carpeta | Secciones del PDF |
|---|---|
| `SelectionSort/` | 2.1 |
| `InsertionSort/` | 2.2, 2.3, 2.4 |
| `Bubblesort/` | 2.5 |
| `Mergesort/` | 2.6, 2.7, 2.8 |
| `Quicksort/` | 2.9, 2.10, 2.11 |
| `Heapsort/` | 2.12, 2.13 |
| `CountingSort/` | extra |
| `RadixSort/` | extra |
| `QuickSelect/` | extra |
