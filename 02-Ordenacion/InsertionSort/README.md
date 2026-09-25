# Insertion Sort (ordenación por inserción)

**PDF:** secciones 2.2, 2.3, 2.4 · **Ficheros:** `insertion_sort_1.cc`,
`insertion_sort_2.cc`, `insertion_sort_3.cc`

## En qué consiste

Es como ordenar cartas en la mano. En la iteración `i`, `v[0..i-1]` ya está
ordenado (pero **no** en su posición definitiva) y se coge `v[i]` y se inserta en
el lugar que le toca dentro de esa parte, desplazando los mayores una posición a
la derecha.

```
[ ordenado entre sí | por mirar ]
              ^ aquí entra v[i]
```

## Las tres versiones

| Versión | Idea | Qué mejora |
|---|---|---|
| **1** (2.2) | Va haciendo `swap(v[j-1], v[j])` hasta que encaja | La más simple |
| **2** (2.3) | Guarda `x = v[i]`, **desplaza** en vez de intercambiar y escribe `x` al final | Un `swap` son 3 asignaciones; desplazar es 1. Aprox. 3× menos escrituras |
| **3** (2.4) | Pone primero el mínimo en `v[0]` (centinela) y así el bucle interno no necesita comprobar `j > 0` | Quita una comparación por iteración del bucle interno |

Las tres hacen exactamente el mismo número de comparaciones de elementos; lo que
cambia son las constantes.

## Coste

| | |
|---|---|
| Mejor caso (vector ya ordenado) | **Θ(n)** — el bucle interno no entra nunca |
| Caso medio | **Θ(n²)** (≈ n²/4 comparaciones) |
| Peor caso (orden inverso) | **Θ(n²)** (≈ n²/2 comparaciones) |
| Memoria extra | Θ(1) |
| Estable | **Sí** (solo desplaza cuando es estrictamente mayor) |

El coste es proporcional al número de **inversiones** de la entrada (parejas
`i < j` con `v[i] > v[j]`). Por eso es lineal cuando el vector ya está casi
ordenado.

## Cuándo tiene sentido

- Vectores **pequeños** (n ≲ 50): gana a mergesort y quicksort por constantes.
  Por eso mergesort v2 y quicksort v3 del PDF lo usan como caso base.
- Vectores **casi ordenados**: es lineal.
- Ordenación **online**: puedes insertar elementos que van llegando.

## Detalle de implementación

- La versión 3 **supone que el vector no está vacío** (accede a `v[0]`). En el
  `main` de demostración se comprueba antes de llamar.
- La versión 3 arranca el bucle en `i = 2` en lugar de `i = 1`: da igual, porque
  con el mínimo en `v[0]` la iteración `i = 1` no haría nada.

## Probarlo

```bash
g++ -std=c++17 insertion_sort_2.cc -o ins
echo "5 3 9 1 7 2" | ./ins      # -> 1 2 3 5 7 9
```
