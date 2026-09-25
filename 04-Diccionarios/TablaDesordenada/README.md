# Diccionario con tabla desordenada

**PDF:** sección 3.1 · **Fichero:** `diccionario_tabla.cc`

## En qué consiste

Un `vector<pair<Key, Info>>` sin ningún orden. Todas las operaciones se apoyan en
un `find` privado que recorre la tabla de principio a fin (búsqueda lineal).

El único truco está en `erase`: en vez de desplazar todos los elementos
posteriores (Θ(n) de movimientos), **mueve el último elemento al hueco** y hace
`pop_back()`. Como la tabla no tiene orden, da igual romperlo.

```cpp
t[i] = t[t.size() - 1];
t.pop_back();
```

## Coste

| Operación | Caso peor |
|---|---|
| `assign` | Θ(n) (hay que mirar si la clave ya está) |
| `erase` | Θ(n) |
| `query` / `contains` | Θ(n) |
| `size` | Θ(1) |
| Constructor | Θ(1) |
| Constructor por copia / asignación / destructor | Θ(n) |

Todo es lineal porque todo pasa por `find`, que es una búsqueda lineal.

## Por qué no hacen falta constructor por copia, asignación ni destructor

Porque el único atributo es un `vector`, y el `vector` de la STL ya los
implementa correctamente. Los generados por el compilador llaman a los del
`vector` y ya está. Esto **deja de ser cierto** en cuanto aparecen punteros
crudos: en el ABB y el AVL sí hay que escribirlos (regla del tres).

## Cuándo tiene sentido

Con n muy pequeño (digamos < 20) es perfectamente razonable: sin punteros, sin
hash, memoria contigua y por tanto muy amigable con la caché. Para todo lo demás,
no.

## Detalle de implementación

El PDF compara `int i` con `t.size()`, que es `unsigned`. El fichero añade
`int(...)` para evitar el aviso del compilador; el resto es literal.

## Probarlo

```bash
g++ -std=c++17 diccionario_tabla.cc -o dt && ./dt
```
