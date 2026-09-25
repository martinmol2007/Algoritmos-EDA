# Diccionario con lista desordenada

**PDF:** sección 3.2 · **Fichero:** `diccionario_lista.cc`

## En qué consiste

Lo mismo que la tabla desordenada pero con una `list<pair<Key, Info>>` (lista
doblemente enlazada). `find` devuelve un **iterador** en vez de un índice.

Se guarda el número de claves en un atributo `n` explícito. ¿Por qué? Porque en
C++98 `list::size()` era Θ(n) — recorría la lista contando. Guardando `n` a mano,
`size()` es Θ(1). (Desde C++11 el estándar obliga a que `list::size()` sea Θ(1),
así que hoy no haría falta; se mantiene por fidelidad al PDF.)

## Coste

| Operación | Caso peor |
|---|---|
| `assign` | Θ(n) |
| `erase` | Θ(n) para buscar + **Θ(1) para borrar** |
| `query` / `contains` | Θ(n) |
| `size` | Θ(1) |

## Lista vs. tabla

Asintóticamente son idénticas. Las diferencias reales:

| | Tabla (`vector`) | Lista (`list`) |
|---|---|---|
| Borrar teniendo el iterador | Θ(n)\* | **Θ(1)** |
| Memoria por elemento | solo el dato | dato + 2 punteros |
| Localidad de caché | **excelente** (contigua) | mala (nodos dispersos) |
| Iteradores tras modificar | se invalidan | siguen valiendo |

\* Salvo el truco de "mover el último al hueco" de la sección 3.1, que lo hace Θ(1).

En la práctica **el vector gana casi siempre**, incluso cuando la teoría dice que
no: recorrer memoria contigua es mucho más rápido que saltar de nodo en nodo.

## Cuándo tiene sentido

Cuando necesitas insertar y borrar en medio **teniendo ya el iterador**, y no
necesitas acceso por posición. La tabla de hash del apartado 3.3 usa listas por
este motivo.

## Probarlo

```bash
g++ -std=c++17 diccionario_lista.cc -o dl && ./dl
```
