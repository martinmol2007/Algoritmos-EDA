# 03 · Búsqueda · EXTRA

> Este capítulo entero es **añadido**: el PDF no incluye búsqueda binaria como
> algoritmo suelto (solo aparece implícita en los árboles binarios de búsqueda
> del capítulo 3 y en las tablas de hash).

## Tabla comparativa

| Algoritmo | Precondición | Coste | Memoria |
|---|---|---|---|
| Búsqueda lineal | ninguna | Θ(n) | Θ(1) |
| Búsqueda binaria | vector ordenado | **Θ(log n)** | Θ(1) iterativa / Θ(log n) recursiva |
| `lower/upper_bound` | vector ordenado | Θ(log n) | Θ(1) |
| Búsqueda sobre la respuesta | predicado monótono | Θ(log(rango) · coste predicado) | Θ(1) |
| Búsqueda ternaria | función unimodal | Θ(log n) | Θ(1) |

## Lo importante

**Θ(log n) es absurdamente rápido.** Con un vector de mil millones de elementos,
la búsqueda binaria hace 30 comparaciones. La lineal haría mil millones.

Pero ordenar cuesta Θ(n log n). O sea:

- **una sola búsqueda** sobre datos desordenados → lineal (ordenar sale más caro
  que buscar).
- **muchas búsquedas** sobre los mismos datos → ordenas una vez y luego cada
  búsqueda es Θ(log n). Es el patrón "preproceso + consultas".
- **inserciones y búsquedas mezcladas** → no uses un vector ordenado (insertar
  cuesta Θ(n)); usa un árbol equilibrado (`set`/`map`, capítulo 04) o una tabla
  de hash.

## El error clásico

```cpp
int m = (l + r) / 2;        // MAL: l + r puede desbordar el int
int m = l + (r - l) / 2;    // BIEN
```

Con `l` y `r` cercanos a 2³¹ la suma desborda. Es un bug real que estuvo 9 años
en la librería estándar de Java sin que nadie lo notase.

## El otro error clásico

Los bucles de búsqueda binaria se equivocan casi siempre en los bordes. La
receta segura es fijar un **invariante** antes de escribir el `while`:

- `busqueda_binaria`: intervalo **cerrado** `[l, r]`, se sale con `l > r`.
- `lower_bound`: intervalo **semiabierto** `[l, r)`, se sale con `l == r`.

No mezcles las dos convenciones en el mismo fichero y te ahorrarás la mitad de
los bugs.

## Contenido

| Carpeta | Qué hay |
|---|---|
| `BusquedaLineal/` | secuencial y variante con centinela |
| `BusquedaBinaria/` | iterativa, recursiva, `lower/upper_bound`, sobre la respuesta |
| `BusquedaTernaria/` | máximo de una función unimodal |
