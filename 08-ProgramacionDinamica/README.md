# 08 · Programación dinámica · EXTRA

> Este capítulo entero es **añadido**: el PDF no lo cubre. Se incluye porque es
> la continuación natural del capítulo de backtracking — convierte algunos de
> esos algoritmos exponenciales en polinómicos.

## Qué es

La programación dinámica sirve cuando un problema cumple dos condiciones:

1. **Subestructura óptima**: la solución óptima se construye a partir de
   soluciones óptimas de subproblemas.
2. **Subproblemas solapados**: los mismos subproblemas aparecen una y otra vez.

La condición 2 es la que marca la diferencia con **divide y vencerás**. En
mergesort los subproblemas son **disjuntos** (las dos mitades no comparten nada),
así que no hay nada que reaprovechar. En Fibonacci recursivo, en cambio,
`fib(n-2)` se calcula un número exponencial de veces:

```
              fib(5)
           /          \
      fib(4)          fib(3)      <- fib(3) aparece 2 veces
      /    \          /    \
  fib(3)  fib(2)  fib(2)  fib(1)  <- fib(2) aparece 3 veces
```

Guardar cada resultado y reutilizarlo convierte Θ(φⁿ) en Θ(n).

## Los dos estilos

| | Top-down (memoización) | Bottom-up (tabulación) |
|---|---|---|
| Cómo | recursión + tabla de resultados ya calculados | bucles que rellenan la tabla en orden |
| Ventaja | se escribe casi solo desde la recursión | sin pila de recursión, permite optimizar memoria |
| Inconveniente | pila, y overhead de las llamadas | hay que pensar el orden de llenado |

Los ficheros de aquí son **bottom-up**.

## La receta

1. Define el **subproblema** con precisión (`dp[i][j] = …`). Este es el paso
   difícil; el resto sale solo.
2. Escribe la **recurrencia**.
3. Fija los **casos base**.
4. Decide el **orden de llenado** (cada celda tiene que calcularse después de
   aquellas de las que depende).
5. Si además necesitas la solución y no solo su valor, **reconstruye** recorriendo
   la tabla hacia atrás.

## Backtracking vs. programación dinámica

| | Backtracking | Programación dinámica |
|---|---|---|
| Explora | el árbol de decisiones entero | cada subproblema **una vez** |
| Coste | típicamente exponencial | polinómico (o pseudopolinómico) |
| Requiere | nada especial | subproblemas **solapados** |
| Memoria | Θ(profundidad) | Θ(tamaño de la tabla) |

La mochila es el ejemplo perfecto del contraste: Θ(2ⁿ) en
`07-Backtracking/Mochila/` y Θ(n·C) aquí.

## Contenido

| Carpeta | Problema | Coste |
|---|---|---|
| `MochilaDP/` | mochila 0/1 con pesos enteros | Θ(n·C) |
| `LCS/` | subsecuencia común más larga | Θ(n·m) |

## Otros problemas clásicos (no implementados aquí)

| Problema | Coste |
|---|---|
| Cambio de monedas | Θ(n·C) |
| Subsecuencia creciente más larga | Θ(n·log n) |
| Distancia de edición (Levenshtein) | Θ(n·m) |
| Multiplicación encadenada de matrices | Θ(n³) |
| Floyd-Warshall (¡está en `06-Grafos/`!) | Θ(\|V\|³) |
| TSP con Held-Karp | Θ(n²·2ⁿ) |
