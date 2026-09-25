# Bubblesort (ordenación por burbuja)

**PDF:** sección 2.5 · **Fichero:** `bubble_sort.cc`

## En qué consiste

Recorre el vector comparando parejas de elementos **adyacentes** y los
intercambia si están desordenados. En la versión del PDF el recorrido interno va
de derecha a izquierda, así que en cada pasada el elemento más pequeño de la
parte no ordenada "burbujea" hasta la posición `i`.

Después de la pasada `i`, las posiciones `0..i` son definitivas.

## Coste

| | |
|---|---|
| Comparaciones | **Θ(n²)** siempre (esta versión) |
| Intercambios | hasta n(n-1)/2 = Θ(n²) |
| Memoria extra | Θ(1) |
| Estable | Sí (solo intercambia si es estrictamente mayor) |

**Ojo:** la versión del PDF no lleva ningún flag para detectar que ya está
ordenado, así que hace siempre las n-1 pasadas. La variante clásica con un
`bool hubo_cambios` baja el mejor caso a Θ(n):

```cpp
bool cambio = true;
for (int i = 0; i < n - 1 and cambio; ++i) {
    cambio = false;
    for (int j = n - 1; j > i; --j) {
        if (v[j-1] > v[j]) { swap(v[j-1], v[j]); cambio = true; }
    }
}
```

## Cuándo tiene sentido

Nunca, en serio. Insertion sort hace el mismo número de comparaciones, es más
rápido en la práctica y es igual de simple. Bubblesort se estudia porque es el
ejemplo canónico de algoritmo cuadrático y porque aparece en todos los exámenes.

## Probarlo

```bash
g++ -std=c++17 bubble_sort.cc -o bub
echo "5 3 9 1 7 2" | ./bub      # -> 1 2 3 5 7 9
```
