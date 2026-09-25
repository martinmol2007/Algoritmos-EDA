# 00 · Común

Ficheros de apoyo que usan los códigos de los capítulos 06 (Grafos) y 07
(Backtracking).

## `eda.hh`

Es el **apéndice A.1 del PDF**, tal cual (con los comentarios traducidos). El
propio PDF lo describe como *"non-polished code"*. Contiene:

| Qué | Para qué |
|---|---|
| `typedef int boolean;` | vectores de booleanos **rápidos** |
| `#define null 0` | puntero nulo estilo C++98 |
| `template class matrix<T>` | tablas bidimensionales de talla fija |
| `operator<<` para `vector` y `matrix` | escribirlos con `cout <<` |
| `readint()`, `readchar()`, `readbool()`, `readdouble()` | lectura de tipos básicos |
| `infinity`, `maxint` | constantes |
| `randdouble()`, `randint()`, `randvector()`, `randmatrix()` | números aleatorios |
| `now()` | tiempo de CPU consumido (solo Linux) |
| `foreach(it, c)` | macro de iteración pre-C++11 |
| `Error`, `ErrorPrec`, `ErrorImpl` | excepciones (el único sitio del curso con herencia) |

### ¿Por qué `typedef int boolean`?

Porque **`vector<bool>` es lento**. La STL lo especializa para guardar un bit por
elemento, así que cada acceso implica operaciones de máscara y desplazamiento, y
además no se comporta como un `vector` normal (`operator[]` no devuelve una
referencia de verdad). Con `vector<boolean>` cada elemento es un `int` completo:
gasta 32 veces más memoria, pero es mucho más rápido.

En código moderno se suele usar `vector<char>` o `vector<uint8_t>` para lo mismo.

### `matrix<T>` imprime la traspuesta

Su `operator<<` recorre `j` por fuera e `i` por dentro:

```cpp
for (int j = 0; j < m.c; ++j)
    for (int i = 0; i < m.r; ++i)
        s << m.t[i][j] << " ";
```

Es decir, **escribe la traspuesta**. No afecta a la corrección de ningún
algoritmo, pero conviene saberlo al leer las salidas de
`07-Backtracking/CuadradosLatinos/` y `07-Backtracking/SaltosCaballo/`.

### Cambios respecto al PDF

- Se ha añadido `#include <string>` (lo necesita la clase `Error`).
- `randmatrix` y `randvector` llevan `inline` para poder incluir el fichero
  desde varias unidades de compilación sin errores de símbolo duplicado.
- Comentarios traducidos al castellano.

## `graph.hh`

Es la **sección 5.1** del PDF:

```cpp
typedef vector<vector<int>> graph;
```

Grafos como tabla de listas de adyacencia, con los vértices numerados de `0` a
`|V|-1`. Dirigidos; un grafo no dirigido se representa poniendo cada arista como
dos arcos.

## Cómo se incluyen

En el PDF los códigos ponen `#include "eda.hh"`. Aquí los ficheros usan rutas
relativas (`#include "../../00-Comun/eda.hh"`) para que compilen sin flags:

```bash
g++ -std=c++17 fichero.cc -o programa
```

Si prefieres el include corto del PDF, compila con `-I`:

```bash
g++ -std=c++17 -I../../00-Comun fichero.cc -o programa
```
