# Cuadrados latinos

**PDF:** sección 6.4 · **Fichero:** `cuadrados_latinos.cc`

## El problema

Un **cuadrado latino de orden n** es una tabla `n × n` en la que cada casilla
lleva uno de `n` colores, de forma que **ninguna fila ni ninguna columna repite
color**.

```
0 1 2
1 2 0
2 0 1
```

Es el mismo tipo de restricción que un sudoku (que es un cuadrado latino de orden
9 con restricciones adicionales por cajas 3×3).

## El algoritmo

Backtracking **casilla a casilla**, recorriéndolas en orden de lectura:

```cpp
int i = cas/n;     // fila
int j = cas%n;     // columna
```

Ese truco de usar un único contador `cas` de 0 a n²-1 y derivar fila y columna
evita tener que llevar dos índices en la recursión.

Marcaje, igual que en n reinas:

| | |
|---|---|
| `F[i][c]` | el color `c` todavía está libre en la fila `i` |
| `C[j][c]` | el color `c` todavía está libre en la columna `j` |

```cpp
if (F[i][c] and C[j][c]) {      // Θ(1)
    Q[i][j] = c;
    F[i][c] = C[j][c] = false;
    recursive(cas+1);
    F[i][c] = C[j][c] = true;   // deshacer
}
```

## Coste

El número de cuadrados latinos de orden n explota:

| n | cuadrados latinos |
|---|---|
| 1 | 1 |
| 2 | 2 |
| 3 | 12 |
| 4 | 576 |
| 5 | 161 280 |
| 6 | 812 851 200 |
| 7 | 61 479 419 904 000 |

**Con n ≥ 5 ya no acaba en un tiempo razonable si los escribe todos.** Prueba con
n = 3 o n = 4.

(Si solo quisieras **contar** cuántos hay, se puede reducir mucho el trabajo: el
número total es `n!·(n-1)!·L(n)`, donde `L(n)` cuenta solo los *reducidos* —
primera fila y primera columna en orden.)

## Detalle: la matriz sale transpuesta

El `operator<<` de `matrix` en `eda.hh` recorre `j` por fuera e `i` por dentro,
así que **imprime la traspuesta**. Para cuadrados latinos da igual (la traspuesta
de un cuadrado latino también lo es), pero conviene saberlo si reutilizas
`matrix` para otra cosa.

## Probarlo

```bash
g++ -std=c++17 cuadrados_latinos.cc -o cl
echo 3 | ./cl      # los 12 cuadrados latinos de orden 3
echo 4 | ./cl      # los 576 de orden 4
```
