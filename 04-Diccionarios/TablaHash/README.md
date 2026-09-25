# Diccionario con tabla de hash

**PDF:** sección 3.3 · **Fichero:** `diccionario_hash.cc`

## En qué consiste

En vez de buscar la clave, se **calcula dónde debería estar**. Una función de
hash convierte la clave en un número, y ese número (módulo M) es la posición en
una tabla de M cubetas.

Como dos claves distintas pueden dar el mismo índice (**colisión**), cada cubeta
guarda una **lista** con todos los pares que caen ahí. Es el método de
**encadenamiento** (*chaining*).

```
hash("hola") % 7 = 3
hash("adeu") % 7 = 3     <- colisión

t[0] -> ()
t[1] -> ()
t[2] -> ()
t[3] -> (hola,1) -> (adeu,2)
t[4] -> ()
...
```

Todas las operaciones hacen lo mismo: calcular `h = hash(key) % M` y luego
búsqueda lineal **dentro de esa lista**, que es corta.

## Coste

Bajo dos hipótesis: (1) `hash` devuelve un natural en tiempo Θ(1), y (2) `hash`
**reparte uniformemente**.

| Operación | Caso medio | Caso peor |
|---|---|---|
| `assign` | **Θ(1 + n/M)** | Θ(n) |
| `erase` | Θ(1 + n/M) | Θ(n) |
| `query` / `contains` | Θ(1 + n/M) | Θ(n) |
| `size` | Θ(1) | Θ(1) |
| Constructor | Θ(M) | Θ(M) |

**α = n/M** es el **factor de carga**: la longitud media de una lista. Si
mantienes α acotado (por ejemplo, α ≤ 1 redimensionando la tabla cuando crece),
todas las operaciones son **Θ(1) en el caso medio**.

El caso peor Θ(n) ocurre cuando todas las claves colisionan y acaban en la misma
lista: la tabla degenera en una lista desordenada.

## El valor por defecto M = 1009

No es casualidad: **1009 es primo**. Si M tiene factores comunes con los valores
típicos de las claves, el `%` reparte mal. Por ejemplo, con M = 1000 y claves que
acaban todas en 0, solo se usaría una décima parte de la tabla. Con M primo eso
no pasa.

## Redimensionado (no está en el PDF)

Esta implementación tiene M **fijo**. Las tablas de hash reales duplican M y
**rehashean** todo cuando α supera un umbral. Cada rehash cuesta Θ(n), pero como
solo ocurre tras Θ(n) inserciones, el **coste amortizado** sigue siendo Θ(1).
Es el mismo argumento que el `push_back` del `vector`.

## Detalle de implementación

El PDF escribe `int h = hash(key) % M;` sin decir qué es `hash`. El fichero
define un método privado que delega en `std::hash<Key>`:

```cpp
static size_t hash (const Key& key) { return std::hash<Key>()(key); }
```

Para tipos propios hay que escribirla a mano — eso es exactamente lo que enseña
la sección 1.11 (`01-STL/11-hash-propio.cc`).

## Cuándo tiene sentido

Siempre que **no** necesites las claves en orden. Es la estructura más rápida
para "¿está esto?" y "dame el valor de esto". En la STL: `unordered_map` y
`unordered_set` (que usan exactamente encadenamiento con listas).

No sirve para: recorrer en orden, mínimo/máximo, consultas por rango, sucesor.
Para eso, `map`/`set` (árboles).

## Probarlo

```bash
g++ -std=c++17 diccionario_hash.cc -o dh && ./dh
```
