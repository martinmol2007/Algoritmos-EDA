# Counting Sort (ordenación por conteo) · EXTRA

> No está en el PDF. Se añade porque es el ejemplo canónico de ordenación **sin
> comparaciones** y aparece siempre que se habla de la cota Ω(n log n).

**Fichero:** `counting_sort.cc`

## En qué consiste

No compara elementos: usa el **valor** de cada clave como índice de un vector de
contadores.

1. Cuenta cuántas veces aparece cada valor: `cnt[x]++`.
2. Convierte `cnt` en **sumas prefijas**: ahora `cnt[i]` = cuántos elementos son
   ≤ `i`, que es exactamente la posición final (más uno) de ese valor.
3. Recorre el vector **de derecha a izquierda** colocando cada elemento en
   `--cnt[x]`.

El paso 3 hacia atrás es lo que garantiza la **estabilidad**: los elementos con
la misma clave conservan su orden relativo. Si solo quieres ordenar enteros
sueltos puedes saltarte los pasos 2 y 3 y reconstruir el vector directamente
desde los contadores.

```
v    = [2 5 3 2 3]        minv=2, maxv=5, k=4
cnt  = [2 2 0 1]          (cuántos 2,3,4,5)
pref = [2 4 4 5]
salida = [2 2 3 3 5]
```

## Coste

| | |
|---|---|
| Tiempo | **Θ(n + k)**, con k = maxv - minv + 1 |
| Memoria extra | **Θ(n + k)** |
| Estable | Sí |
| In-place | No |

Es **lineal solo si k = O(n)**. Ordenar `{1, 5, 1000000000}` con counting sort
reservaría mil millones de contadores: ahí es un desastre.

## Por qué puede bajar de Ω(n log n)

La cota inferior Ω(n log n) vale para algoritmos que solo pueden **comparar**
elementos entre sí. Counting sort hace algo más fuerte: usa la clave como
dirección de memoria. Al salirse del modelo, la cota no le aplica.

## Cuándo tiene sentido

- Notas de 0 a 10, edades, días del año, bytes, caracteres…
- Como **subrutina de radix sort** (ahí k = base, que es una constante).
- Cuando hay muchísimos duplicados.

## Probarlo

```bash
g++ -std=c++17 counting_sort.cc -o cs
echo "5 -3 9 1 7 7 -2 8 0 4" | ./cs     # -> -3 -2 0 1 4 5 7 7 8 9
```
