# Búsqueda lineal (secuencial) · EXTRA

**Fichero:** `busqueda_lineal.cc`

## En qué consiste

Recorrer el vector de principio a fin comparando con el elemento buscado. Se para
al encontrarlo.

Es el **único método posible si el vector no está ordenado**, y ese es todo su
mérito: no tiene precondiciones.

## Coste

| | |
|---|---|
| Mejor caso | Θ(1) (está el primero) |
| Caso medio (si está) | n/2 comparaciones = **Θ(n)** |
| Peor caso (no está) | n comparaciones = **Θ(n)** |
| Memoria extra | Θ(1) |

## La variante con centinela

```cpp
v.push_back(x);          // centinela
int i = 0;
while (v[i] != x) ++i;   // seguro que para
```

El bucle normal comprueba dos cosas por vuelta: `i < n` y `v[i] != x`. Poniendo
una copia de `x` al final del vector garantizas que el bucle acaba, así que te
puedes quitar la comprobación del límite: **la mitad de comparaciones por
iteración**.

Asintóticamente es lo mismo (Θ(n)), pero en la práctica es casi el doble de
rápido. Es el ejemplo típico de "mejorar las constantes sin cambiar el orden".

Inconveniente: necesitas poder escribir en el vector (en el fichero se pasa por
valor, que es una copia Θ(n) y por tanto no compensa; en código real reservarías
el hueco de antemano).

## Cuándo tiene sentido

- Datos desordenados.
- n pequeño: para n < 30 la lineal puede ganar a la binaria por constantes y por
  localidad de caché.
- Una única búsqueda sobre datos que tendrías que ordenar primero.

## Probarlo

```bash
g++ -std=c++17 busqueda_lineal.cc -o bl
echo "7 1 3 5 7 9" | ./bl      # -> 3 (dos veces, una por versión)
```
