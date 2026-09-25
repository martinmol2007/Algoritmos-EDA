# Saltos de caballo (recorrido del caballo)

**PDF:** sección 6.5 · **Fichero:** `saltos_caballo.cc`

## El problema

Un caballo se coloca en una casilla dada de un tablero `n × n`. ¿Hay forma de
visitar **todas** las casillas moviéndolo `n² - 1` veces, sin repetir ninguna?

Es el clásico *knight's tour*. Un caballo tiene 8 movimientos posibles:

```
. X . X .
X . . . X
. . K . .
X . . . X
. X . X .
```

## El algoritmo

Backtracking puro. `M[x][y]` guarda **en qué paso** se visitó la casilla, o `-1`
si está libre.

```cpp
void recursive(int step, int x, int y) {
    if (step == n*n-1) { found = true; S = M; }
    else {
        try_it(step, x+2, y-1);  try_it(step, x+2, y+1);
        try_it(step, x+1, y+2);  try_it(step, x-1, y+2);
        try_it(step, x-2, y+1);  try_it(step, x-2, y-1);
        try_it(step, x-1, y-2);  try_it(step, x+1, y-2);
    }
}
```

`try_it` concentra las tres comprobaciones en una sola condición:

```cpp
if (not found          // poda por parada: ya hay solución
    and x >= 0 and x < n and y >= 0 and y < n   // dentro del tablero
    and M[x][y] == -1) {                        // casilla libre
    M[x][y] = step + 1;
    recursive(step + 1, x, y);
    M[x][y] = -1;                               // deshacer
}
```

Comprobar los límites **dentro** de `try_it` en vez de antes de llamarla hace el
código mucho más corto: los 8 saltos se escriben en dos líneas.

## Coste

Sin podar, el espacio de búsqueda es **8^(n²)**: astronómico. La poda por casilla
ocupada lo reduce muchísimo, pero sigue siendo exponencial.

| Tablero | Tiempo |
|---|---|
| 5×5 desde (0,0) | instantáneo |
| 6×6 desde (0,1) | tarda un rato (el PDF lo avisa) |
| 8×8 | inviable con esta versión |

Y hay un detalle importante: **el orden en que se prueban los 8 saltos afecta
brutalmente al tiempo**. Con este orden fijo, 6×6 ya cuesta.

## La regla de Warnsdorff

La solución clásica para hacerlo viable: en cada paso, probar primero el salto
que lleva a la casilla con **menos salidas libres**. La intuición es visitar
pronto las casillas difíciles (esquinas, bordes) y dejar para el final las
fáciles.

Es una **heurística de ordenación**, no una poda: no elimina ramas, solo cambia
el orden en que se exploran. Pero en la práctica resuelve tableros de 100×100 casi
sin retroceder. Añadirla a este código es un ejercicio excelente.

## Detalle del `main`

El `main` del PDF escribe `kj.has_a_solution()` — es decir, un `1` — cuando hay
solución, lo cual no aporta nada. En el fichero se escribe el tablero con el
orden de los saltos:

```
0 15 10 19 2
9 20 1 16 11
14 23 18 3 6
21 8 5 12 17
24 13 22 7 4
```

(Recuerda que `matrix::operator<<` imprime la traspuesta.)

## Probarlo

```bash
g++ -std=c++17 saltos_caballo.cc -o kj
echo "5 0 0" | ./kj     # instantáneo
echo "6 0 1" | ./kj     # tarda
```
