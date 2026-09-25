# Búsqueda binaria (dicotómica) · EXTRA

**Ficheros:** `busqueda_binaria_iterativa.cc`, `busqueda_binaria_recursiva.cc`,
`lower_upper_bound.cc`, `busqueda_binaria_respuesta.cc`

## En qué consiste

**Precondición: el vector tiene que estar ordenado.**

Se mira el elemento central. Como el vector está ordenado, con esa única
comparación ya sabes en qué mitad puede estar el elemento, y la otra mitad se
descarta entera. Se repite sobre la mitad que queda.

```
buscar 7 en  [1 3 5 7 9 11 13]
              l     m       r     v[m]=7 -> encontrado

buscar 3 en  [1 3 5 7 9 11 13]
              l     m       r     v[m]=7 > 3 -> a la izquierda
             [1 3 5]
              l m r              v[m]=3 -> encontrado
```

Cada paso divide el problema por 2, así que hacen falta **log₂ n** pasos.

## Coste

| | |
|---|---|
| Recurrencia | T(n) = T(n/2) + Θ(1) |
| Peor caso | **Θ(log n)** (exactamente ⌊log₂ n⌋ + 1 comparaciones) |
| Mejor caso | Θ(1) |
| Memoria extra | Θ(1) iterativa, Θ(log n) de pila la recursiva |

Por el teorema maestro: a = 1, b = 2, f(n) = 1, n^(log₂ 1) = n⁰ = 1 ⟹
T(n) = Θ(log n).

Para hacerse una idea: n = 10⁹ ⟹ 30 comparaciones.

## Las cuatro versiones

### 1. `busqueda_binaria_iterativa.cc`
La de toda la vida. Intervalo **cerrado** `[l, r]`, sale cuando `l > r`.
Devuelve **una** posición de `x` (si hay repetidos, no dice cuál).

### 2. `busqueda_binaria_recursiva.cc`
La misma escrita como divide y vencerás. Se lee mejor y se razona mejor la
recurrencia, pero gasta pila. Es recursión de cola, así que `g++ -O2` la suele
convertir en el bucle de la versión 1.

### 3. `lower_upper_bound.cc` ← **la más útil en la práctica**

| | Devuelve |
|---|---|
| `lower_bound(v, x)` | primera posición `i` con `v[i] >= x` |
| `upper_bound(v, x)` | primera posición `i` con `v[i] > x` |

Con estas dos tienes todo lo demás:

```cpp
apariciones de x      =  upper_bound(x) - lower_bound(x)
x está en el vector   =  lower_bound(x) < n and v[lower_bound(x)] == x
dónde insertar x      =  lower_bound(x)
primer elemento > x   =  upper_bound(x)
```

Usan intervalo **semiabierto** `[l, r)` con `r` inicial = `n`, y salen cuando
`l == r`. Fíjate en que **no hay `return` dentro del bucle**: siempre se hacen
los log n pasos completos. Eso es a propósito — es lo que hace que la frontera
sea exacta.

En la STL son `std::lower_bound` y `std::upper_bound` (`<algorithm>`), y
`equal_range` devuelve las dos a la vez.

### 4. `busqueda_binaria_respuesta.cc` ← **la idea potente**

La búsqueda binaria **no necesita un vector**. Solo necesita un predicado
**monótono**: algo que sea falso hasta cierto punto y cierto a partir de ahí.

```
     F F F F F V V V V V
               ^ buscamos esta frontera
```

Entonces buscas binariamente sobre el **rango de respuestas posibles**. El
ejemplo del fichero es el clásico de los pintores: *"repartir n tablones entre k
pintores minimizando el tiempo del que más tarda"*. Resolverlo directamente es
difícil, pero **"¿se puede hacer en tiempo T?"** es fácil (un recorrido greedy) y
es monótono: si se puede con T, también con T+1.

Coste: Θ(log(rango) · coste de comprobar el predicado).

Este patrón aparece constantemente en problemas de Jutge y de competición:
minimizar el máximo, maximizar el mínimo, "el menor T tal que...".

## Errores típicos

1. **Olvidar la precondición.** Si el vector no está ordenado, el resultado es
   basura silenciosa.
2. `(l + r) / 2` desborda con índices grandes. Usa `l + (r - l) / 2`.
3. Mezclar intervalos cerrados y semiabiertos en el mismo bucle → bucle infinito
   o un elemento que nunca se mira.
4. `v.size()` es **unsigned**: `int(v.size()) - 1` con el vector vacío da -1
   (bien), pero `v.size() - 1` da 18446744073709551615 (mal).

## Probarlo

```bash
g++ -std=c++17 busqueda_binaria_iterativa.cc -o bb
echo "7 1 3 5 7 9 11" | ./bb          # -> posicion 3

g++ -std=c++17 lower_upper_bound.cc -o lu
echo "3 1 3 3 3 5 7" | ./lu           # -> lower=1 upper=4 apariciones=3

g++ -std=c++17 busqueda_binaria_respuesta.cc -o br
echo "3 10 20 30 40 50" | ./br        # -> 60
```
