# 04 · Diccionarios

Capítulo 3 del PDF (`Dictionaries`). Cinco implementaciones **del mismo TAD**,
con la misma interfaz pública, para comparar costes:

```cpp
void  assign   (const Key& key, const Info& info);  // insertar / modificar
void  erase    (const Key& key);                    // borrar
Info& query    (const Key& key);                    // consultar
bool  contains (const Key& key);                    // pertenece?
int   size     ();                                  // número de claves
```

## Tabla comparativa

| Implementación | `assign` | `erase` | `query` / `contains` | `size` | Claves ordenadas |
|---|---|---|---|---|---|
| Tabla desordenada (3.1) | Θ(n) | Θ(n) | Θ(n) | Θ(1) | No |
| Lista desordenada (3.2) | Θ(n) | Θ(n) | Θ(n) | Θ(1) | No |
| Tabla de hash (3.3) | Θ(n) peor / **Θ(1+n/M) medio** | ídem | ídem | Θ(1) | No |
| ABB (3.4) | Θ(h) | Θ(h) | Θ(h) | Θ(1) | **Sí** |
| AVL (3.5) | **Θ(log n) garantizado** | Θ(log n) | Θ(log n) | Θ(1) | **Sí** |

`h` = altura del árbol. En un ABB: **Θ(log n) en el caso medio** (con claves
insertadas en orden aleatorio) pero **Θ(n) en el peor** (claves insertadas ya
ordenadas → el árbol degenera en una lista). El AVL elimina ese caso peor.

`M` = número de cubetas de la tabla de hash, `n/M` = factor de carga.

## Cómo elegir

```
¿Necesitas las claves EN ORDEN (recorrer ordenado, mínimo, rango, sucesor)?
├── Sí  → árbol equilibrado    → std::map / std::set        Θ(log n)
└── No  → tabla de hash        → std::unordered_map/set     Θ(1) medio
```

- **Tabla / lista desordenada**: solo valen para n muy pequeño. Están en el curso
  para tener una referencia contra la que comparar.
- **Tabla de hash**: la más rápida en la práctica, pero Θ(n) en el caso peor (si
  todas las claves colisionan), no da orden y necesita una buena función de hash.
- **ABB**: la idea base. Su problema es que se degrada.
- **AVL**: el ABB con garantías. Es lo que hay (en espíritu) detrás de `std::map`
  — la STL usa árboles rojinegros, que equilibran algo menos pero rotan menos al
  borrar.

## Contenido

| Carpeta | Sección | Fichero |
|---|---|---|
| `TablaDesordenada/` | 3.1 | `diccionario_tabla.cc` |
| `ListaDesordenada/` | 3.2 | `diccionario_lista.cc` |
| `TablaHash/` | 3.3 | `diccionario_hash.cc` |
| `ABB/` | 3.4 | `diccionario_abb.cc` + `recorridos.cc` (extra) |
| `AVL/` | 3.5 | `diccionario_avl.cc` |
