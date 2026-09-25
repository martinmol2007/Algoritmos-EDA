# Mochila 0/1 por programación dinámica · EXTRA

**Fichero:** `mochila_dp.cc` · **Compárese con:** `07-Backtracking/Mochila/`

## El problema

El mismo que en el capítulo 07: mochila de capacidad `C`, objetos con peso `p[i]`
y valor `v[i]`, maximizar el valor sin pasarse del peso, sin partir objetos.

**La diferencia clave: aquí los pesos tienen que ser ENTEROS.** En el PDF son
`double`, y con reales esta técnica no se puede aplicar directamente (la tabla se
indexa por peso).

## La formulación

**Subproblema:**

> `dp[i][c]` = valor máximo alcanzable usando solo los objetos `0..i-1` con una
> capacidad de `c`

**Recurrencia:** para cada objeto solo hay dos opciones, y la tabla se queda con
la mejor:

```
dp[i][c] = max( dp[i-1][c],                      // no coger el objeto i-1
                dp[i-1][c - p[i-1]] + v[i-1] )   // cogerlo, si cabe
```

**Caso base:** `dp[0][c] = 0` para todo `c` (sin objetos, valor 0).

**Respuesta:** `dp[n][C]`.

Fíjate en que la recurrencia es *literalmente* las dos ramas del árbol de
backtracking. La única diferencia es que aquí cada subproblema `(i, c)` se
resuelve **una sola vez**.

## Reconstruir qué objetos se cogen

La tabla da el valor óptimo, no la selección. Se recupera yendo hacia atrás:

```cpp
int c = C;
for (int i = n; i >= 1; --i) {
    if (dp[i][c] != dp[i-1][c]) {   // el valor cambió -> se cogió el objeto i-1
        cogidos[i-1] = true;
        c -= p[i-1];
    }
}
```

Si `dp[i][c] == dp[i-1][c]`, el objeto `i-1` no aportó nada y no se cogió.

## La versión de memoria lineal

Como `dp[i][·]` solo depende de `dp[i-1][·]`, basta con una fila:

```cpp
for (int i = 0; i < n; ++i)
    for (int c = C; c >= p[i]; --c)         // ¡HACIA ATRÁS!
        dp[c] = max(dp[c], dp[c - p[i]] + v[i]);
```

**El bucle de `c` tiene que ir hacia atrás.** Si fuera hacia delante, al calcular
`dp[c]` usarías un `dp[c - p[i]]` que ya se actualizó **en esta misma iteración
de `i`**, es decir, que ya incluye el objeto `i`. Estarías permitiendo coger el
mismo objeto varias veces.

Curiosamente, esa "equivocación" resuelve otro problema: el bucle **hacia
delante** es exactamente la **mochila con repeticiones** (*unbounded knapsack*).
Un solo signo distingue los dos problemas.

Inconveniente: con una sola fila ya no se puede reconstruir la selección, solo se
obtiene el valor.

## Coste

| | Tabla completa | Memoria lineal |
|---|---|---|
| Tiempo | **Θ(n·C)** | Θ(n·C) |
| Memoria | Θ(n·C) | **Θ(C)** |
| Reconstruye la solución | **sí** | no |

## Cuidado: pseudopolinómico ≠ polinómico

Θ(n·C) *parece* polinómico, pero no lo es en el **tamaño de la entrada**: el
número `C` se escribe con `log C` bits, así que Θ(n·C) = Θ(n·2^(log C)) es
**exponencial** en el tamaño de la entrada.

A eso se le llama **pseudopolinómico**. La mochila 0/1 sigue siendo NP-difícil;
lo que ocurre es que es tratable cuando `C` es pequeño.

Ejemplo práctico: con n = 100 y C = 1000 la DP es instantánea. Con n = 100 y
C = 10⁹ necesitarías 10¹¹ celdas — inviable, y ahí el backtracking con buenas
podas puede ser mejor.

## Cuándo usar cada enfoque

| | Backtracking (cap. 07) | DP (este) |
|---|---|---|
| Pesos reales | **sí** | no |
| C enorme | **mejor** | inviable |
| n grande, C pequeño | inviable | **mejor** |
| Coste | Θ(2ⁿ) | Θ(n·C) |

## Probarlo

```bash
g++ -std=c++17 mochila_dp.cc -o mdp
printf '4 10\n5 10\n4 40\n6 30\n3 50\n' | ./mdp
# valor maximo = 90
# objetos      = 1 3      (pesos 4+3=7 <= 10, valores 40+50=90)
```
