# Algoritmos y Estructuras de Datos (EDA) · FIB-UPC

Códigos de los algoritmos de la asignatura **EDA**, organizados por carpetas, con
una explicación propia de cada uno: en qué consiste, cuál es su coste, cuándo
usarlo y qué errores tiene la versión del PDF.

La fuente es **`eda-codis.pdf`** — *Data Structures and Algorithms / Algorithms in
C++*, de Jordi Petit, Salvador Roura y Albert Atserias (Departament de
Llenguatges i Sistemes Informàtics, UPC, 15 de febrer de 2017). Los códigos del
PDF se han transcrito **fielmente**; lo que se ha añadido va siempre marcado como
`EXTRA`.

---

## Índice

| Carpeta | Contenido | Origen |
|---|---|---|
| [`00-Comun/`](00-Comun/) | `eda.hh`, `graph.hh` — macros y tipos que usan los demás | Apéndice A.1 y sección 5.1 |
| [`01-STL/`](01-STL/) | Ejemplos de uso de la STL (11 programas) | Capítulo 1 |
| [`02-Ordenacion/`](02-Ordenacion/) | Selection, insertion, bubble, merge, quick, heap + counting, radix, quickselect | Capítulo 2 + extras |
| [`03-Busqueda/`](03-Busqueda/) | Búsqueda lineal, **binaria** (4 variantes), ternaria | **Todo extra** |
| [`04-Diccionarios/`](04-Diccionarios/) | Tabla, lista, hash, ABB, AVL + recorridos de árbol | Capítulo 3 + extra |
| [`05-ColasPrioridad/`](05-ColasPrioridad/) | Heap recursivo e iterativo | Capítulo 4 |
| [`06-Grafos/`](06-Grafos/) | DFS, BFS, topológico, Dijkstra, Prim + Union-Find, Kruskal, Bellman-Ford, Floyd-Warshall | Capítulo 5 + extras |
| [`07-Backtracking/`](07-Backtracking/) | n reinas, cuadrados latinos, saltos de caballo, asignación, hamiltoniano, TSP, mochila | Capítulo 6 |
| [`08-ProgramacionDinamica/`](08-ProgramacionDinamica/) | Mochila DP, LCS | **Todo extra** |

**62 programas**, cada uno con su `main` y compilable por separado.

---

## Cómo está organizado

Cada algoritmo tiene **su propia carpeta** con:

- Los **ficheros de código** — uno por variante. Por ejemplo,
  `02-Ordenacion/Mergesort/` contiene `merge_sort_1.cc`, `merge_sort_2.cc` y
  `merge_sort_3_bottom_up.cc`.
- Un **`README.md`** con la explicación: la idea, un diagrama, el análisis de
  coste, cuándo usarlo y los detalles de implementación.

Cada carpeta de capítulo tiene además un `README.md` con una **tabla comparativa**
de todos los algoritmos que contiene.

---

## Cómo compilar y ejecutar

Todos los ficheros son **programas completos e independientes**, con un `main` de
demostración que lee de la entrada estándar.

### Uno suelto

```bash
g++ -std=c++17 02-Ordenacion/Mergesort/merge_sort_1.cc -o ms
echo "5 3 9 1 7 7 2 8 0 4" | ./ms
# 0 1 2 3 4 5 7 7 8 9
```

### Todos a la vez

```bash
make            # compila los 62 programas en bin/
make list       # lista los ejecutables
make clean      # borra bin/
```

Los ejecutables se llaman `bin/<Carpeta>-<fichero>`, por ejemplo
`bin/Mergesort-merge_sort_1`.

### Requisitos

`g++` con soporte de **C++17** (vale cualquier versión moderna; con `-std=c++11`
también compila casi todo). Los capítulos 06 y 07 usan `00-Comun/eda.hh`, que
incluye `<sys/resource.h>` — es decir, **funcionan en Linux/WSL y macOS**, no en
Windows nativo.

---

## Chuleta rápida de costes

### Ordenación

| Algoritmo | Medio | Peor | Memoria | Estable |
|---|---|---|---|---|
| Selection | Θ(n²) | Θ(n²) | Θ(1) | No |
| Insertion | Θ(n²) | Θ(n²) | Θ(1) | Sí |
| Bubble | Θ(n²) | Θ(n²) | Θ(1) | Sí |
| **Merge** | **Θ(n log n)** | **Θ(n log n)** | Θ(n) | **Sí** |
| **Quick** | **Θ(n log n)** | Θ(n²) | Θ(log n) | No |
| **Heap** | **Θ(n log n)** | **Θ(n log n)** | **Θ(1)** | No |
| Counting | Θ(n+k) | Θ(n+k) | Θ(n+k) | Sí |
| Radix | Θ(d(n+b)) | Θ(d(n+b)) | Θ(n+b) | Sí |

### Diccionarios

| Estructura | Búsqueda | Inserción | Borrado | ¿Ordenado? |
|---|---|---|---|---|
| Tabla / lista desordenada | Θ(n) | Θ(n) | Θ(n) | No |
| Tabla de hash | **Θ(1)** medio | Θ(1) medio | Θ(1) medio | No |
| ABB | Θ(h) | Θ(h) | Θ(h) | Sí |
| **AVL** | **Θ(log n)** | **Θ(log n)** | **Θ(log n)** | **Sí** |

### Grafos

| Algoritmo | Coste | Para qué |
|---|---|---|
| DFS / BFS | Θ(\|V\|+\|E\|) | recorrido; BFS da caminos mínimos **sin pesos** |
| Ordenación topológica | Θ(\|V\|+\|E\|) | ordenar un DAG por dependencias |
| Dijkstra | Θ((\|V\|+\|E\|)·log\|V\|) | caminos mínimos, pesos **≥ 0** |
| Bellman-Ford | Θ(\|V\|·\|E\|) | caminos mínimos con pesos **negativos** |
| Floyd-Warshall | Θ(\|V\|³) | caminos mínimos **entre todos los pares** |
| Prim / Kruskal | Θ((\|V\|+\|E\|)·log\|V\|) / Θ(\|E\|·log\|E\|) | árbol de expansión mínimo |
| Union-Find | Θ(α(n)) ≈ Θ(1) | conjuntos disjuntos |

---

## Qué es extra y qué viene del PDF

Los códigos del PDF están transcritos tal cual (mismo estilo, mismos nombres,
mismo `}   }`), con los comentarios traducidos y ampliados.

Todo lo añadido lleva la marca `EXTRA (no esta en el PDF)` en la cabecera del
fichero y `· EXTRA` en el título de su README:

- **Capítulo 03 completo**: búsqueda lineal, binaria (iterativa, recursiva,
  `lower/upper_bound`, sobre la respuesta) y ternaria.
- **Capítulo 08 completo**: mochila por programación dinámica y LCS.
- Ordenación: counting sort, radix sort, quickselect.
- Diccionarios: recorridos de árbol binario.
- Grafos: Union-Find, Kruskal, Bellman-Ford, Floyd-Warshall, BFS con distancias.

### Erratas del PDF corregidas

| Dónde | Errata | Corrección |
|---|---|---|
| 4.1 Cola de prioridad | El constructor se llama `CuaPrio()` dentro de `class PriorityQueue` | `PriorityQueue()` |
| 5.5 Dijkstra | Usa `infinit` (catalán) | `infinity` (el nombre real en `eda.hh`) |
| 5.6 Prim | `Q.push({0.0, {0, 0}));` — paréntesis mal cerrados | `Q.push({0.0, {0, 0}});` |
| 2.1, 2.6 | Se llama a `pos_min` / `merge` antes de declararlas | declaración previa añadida |
| 2.7, 2.11 | Usan `ins_sort(v, l, r)`, que el PDF no lista | implementada |
| 3.3 Tabla de hash | Usa `hash(key)` sin definirla | método privado que delega en `std::hash<Key>` |
| 6.5 Saltos de caballo | El `main` escribe `has_a_solution()` (un `1`) | escribe el tablero con el recorrido |

Cada corrección está anotada en el fichero correspondiente y explicada en su
README.

---

## Enlaces entre capítulos

Los algoritmos no son islas; los READMEs cruzan referencias donde toca:

- El **heap** del capítulo 05 es lo que hace funcionar al heapsort (02) y a
  Dijkstra y Prim (06).
- El **Union-Find** (06) es lo que hace viable a Kruskal (06).
- La **mochila** aparece dos veces: Θ(2ⁿ) por backtracking (07) y Θ(n·C) por
  programación dinámica (08).
- El **backtracking** (07) es un DFS (06) sobre el árbol de soluciones.
- Los capítulos 04 y 05 implementan a mano lo que hay dentro de `map`,
  `unordered_map` y `priority_queue` (01).
- **Floyd-Warshall** está en Grafos (06) pero es programación dinámica pura (08).

---

## Créditos

- **Códigos originales**: Jordi Petit, Salvador Roura y Albert Atserias —
  *Data Structures and Algorithms / Algorithms in C++*, Departament de
  Llenguatges i Sistemes Informàtics, Universitat Politècnica de Catalunya
  (15 de febrer de 2017). Fichero `eda-codis.pdf`.
- **Organización, explicaciones, correcciones y algoritmos extra**: este
  repositorio, hecho con ayuda de Claude.
