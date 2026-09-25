# n reinas

**PDF:** secciones 6.1, 6.2, 6.3 · **Ficheros:** `n_reinas_1.cc`,
`n_reinas_2.cc`, `n_reinas_3.cc`

## El problema

Colocar `n` reinas en un tablero de `n × n` de forma que **ninguna amenace a
otra**: ni dos en la misma fila, ni en la misma columna, ni en la misma diagonal.

```
* O * * * *
* * * O * *
* * * * * O
O * * * * *
* * O * * *
* * * * O *
```

## La primera decisión de modelado

Como no puede haber dos reinas en la misma fila, **hay exactamente una reina por
fila**. Eso permite representar una configuración con un simple vector:

```cpp
vector<int> T;   // T[i] = columna de la reina de la fila i
```

Así las restricciones de fila desaparecen gratis, y el espacio de búsqueda baja
de C(n², n) a nⁿ. Un buen modelado vale más que muchas optimizaciones.

## Las tres versiones

### Versión 1 (6.1) — ingenua

Coloca `T[i] = j` y llama a `legal(i)`, que comprueba **contra todas las reinas
anteriores**:

```cpp
if (T[k]==T[i] or T[i]-i==T[k]-k or T[i]+i==T[k]+k) return false;
```

Las tres condiciones son: misma columna, misma diagonal `\`, misma diagonal `/`.
(Dos casillas están en la misma diagonal `\` si `fila - columna` coincide, y en la
misma `/` si `fila + columna` coincide.)

Coste de `legal(i)`: **Θ(i)**.

### Versión 2 (6.2) — con marcaje

En vez de recorrer, mantiene tres vectores de marcas:

| Vector | Talla | Qué marca |
|---|---|---|
| `mc[j]` | n | columna j ocupada |
| `md1[diag1(i,j)]` | 2n-1 | diagonal `/` ocupada |
| `md2[diag2(i,j)]` | 2n-1 | diagonal `\` ocupada |

con `diag1(i,j) = n-j-1+i` y `diag2(i,j) = i+j`. (Hay 2n-1 diagonales de cada
tipo, y estas fórmulas las numeran de 0 a 2n-2.)

Comprobar si una casilla es válida pasa a costar **Θ(1)**:

```cpp
if (not mc[j] and not md1[diag1(i,j)] and not md2[diag2(i,j)]) {
    ...marcar... recursive(i+1); ...desmarcar...
}
```

Ese marcar-recursión-desmarcar es el patrón central del backtracking.

### Versión 3 (6.3) — una sola solución

Igual que la 2, pero con un flag `found` que corta la búsqueda:

```cpp
for (int j = 0; j < n and not found; ++j) { ... }
```

En cuanto se encuentra una solución, todos los bucles pendientes dejan de iterar
y la recursión se desenrolla sin explorar nada más.

## Coste

| | |
|---|---|
| Espacio de búsqueda sin podar | nⁿ |
| Con marcaje (nunca dos en la misma columna) | n! |
| Con las podas de diagonales | mucho menos, pero sigue siendo exponencial |
| `legal()` v1 | Θ(i) |
| Comprobación v2 | **Θ(1)** |

Número de soluciones: n=4 → 2, n=6 → 4, n=8 → **92**, n=10 → 724, n=12 → 14200.
No existe fórmula cerrada.

En la práctica, la v1 aguanta hasta n ≈ 12-13 y la v2 hasta n ≈ 16-18 si hay que
listarlas todas. Buscando **una sola** (v3), n = 30 es instantáneo.

## Probarlo

```bash
g++ -std=c++17 n_reinas_2.cc -o q2
echo 6 | ./q2          # las 4 soluciones de 6x6

g++ -std=c++17 n_reinas_3.cc -o q3
echo 8 | ./q3          # una sola solución de 8x8
```
