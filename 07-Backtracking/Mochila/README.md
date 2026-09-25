# Problema de la mochila (knapsack 0/1)

**PDF:** secciones 6.9, 6.10 · **Ficheros:** `mochila_1.cc`, `mochila_2.cc`

## El problema

Una mochila aguanta hasta `C` unidades de peso. El objeto `i` pesa `p[i]` y vale
`v[i]`. Hay que escoger qué objetos meter para **maximizar el valor total** sin
pasarse de `C`. **Los objetos no se pueden partir** (por eso se llama 0/1: cada
objeto se coge entero o no se coge).

## El árbol de decisiones

Para cada objeto hay dos opciones, así que el árbol es **binario** con 2ⁿ hojas:

```
                objeto 0
              /          \
         cogerlo       no cogerlo
          /    \         /    \
      obj 1  obj 1    obj 1  obj 1
       ...
```

## Versión 1 (6.9) — sin cota

Explora las dos ramas siempre. La única poda es la de **factibilidad**:

```cpp
if (pes+p[i] <= C) {      // solo si cabe
    s[i] = true;
    recursive(i+1, val+v[i], pes+p[i]);
}
s[i] = false;             // no cogerlo siempre es posible
recursive(i+1, val, pes);
```

Coste: **Θ(2ⁿ)**.

## Versión 2 (6.10) — con cota superior

Precalcula las **sumas sufijas** de los valores:

```cpp
sv[i] = v[i] + v[i+1] + ... + v[n-1]
```

`sv[i]` es el **máximo valor que podrían aportar los objetos que quedan**,
ignorando la capacidad. Es optimista, y por tanto una cota superior válida.

```cpp
if (pes+p[i] <= C and val+sv[i] > best) { ...coger... }
if (val+sv[i+1] > best)                 { ...no coger... }
```

Si ni cogiendo **todo** lo que queda se superara `best`, la rama entera sobra.

Precalcular `sv` cuesta Θ(n) una sola vez, y luego la cota es Θ(1) por nodo. Es
la cota con mejor relación coste/beneficio del capítulo.

## La mejora que el PDF sugiere pero no implementa

> *"A clever sorting of the objects might improve the algorithm."*

Si ordenas los objetos por **valor/peso decreciente**, las primeras soluciones
que encuentras ya son buenas, `best` sube pronto y la cota poda muchísimo más.
Es una heurística de ordenación, igual que la regla de Warnsdorff en el caballo:
no cambia qué se explora, cambia **en qué orden**, y eso lo cambia todo.

De hecho, con los objetos ordenados así, la cota clásica es la de la **mochila
fraccionaria** (donde sí puedes partir objetos), que se resuelve de forma voraz
en Θ(n) y es una cota superior mucho más ajustada que `sv`.

## Coste

| Versión | Caso peor | En la práctica |
|---|---|---|
| 1 (sin cota) | Θ(2ⁿ) | n ≈ 25-30 |
| 2 (con cota) | Θ(2ⁿ) | bastante más, según los datos |

## Y la programación dinámica

Si los **pesos son enteros**, la mochila se resuelve en **Θ(n·C)** con
programación dinámica. Ver `08-ProgramacionDinamica/MochilaDP/`.

Cuidado con la trampa clásica: Θ(n·C) **no es polinómico** en el tamaño de la
entrada, porque `C` se codifica con log C bits. Se le llama **pseudopolinómico**.
La mochila 0/1 sigue siendo NP-difícil; lo que pasa es que es "fácil" cuando `C`
es pequeño.

Aquí, además, los pesos son `double`, así que la DP ni siquiera es aplicable
directamente.

| | Backtracking | DP |
|---|---|---|
| Coste | Θ(2ⁿ) | Θ(n·C) |
| Pesos reales | **sí** | no (enteros) |
| C enorme (p.ej. 10⁹) | mejor | inviable (memoria) |
| n grande, C pequeño | inviable | **mejor** |

## Probarlo

```bash
g++ -std=c++17 mochila_2.cc -o m2
echo 20 | ./m2
```

Las dos versiones dan el mismo valor óptimo (el `main` genera pesos y valores con
`randvector` de `eda.hh`, sin semilla, así que son reproducibles).
