# 01 · Uso de la STL

Capítulo 1 del PDF (`STL Usage Examples`). No son algoritmos, sino **ejemplos de
uso** de los contenedores de la librería estándar. Cada fichero es un programa
completo que lee de la entrada estándar.

## Contenido

| Fichero | Sección | Qué hace |
|---|---|---|
| `01-lectura-linea-a-linea.cc` | 1.1 | `istringstream`: leer línea a línea y procesar cada una |
| `02-stack.cc` | 1.2 | `stack`: escribe una secuencia al revés |
| `03-queue.cc` | 1.3 | `queue`: escribe una secuencia en el mismo orden |
| `04-priority_queue.cc` | 1.4 | `priority_queue`: orden decreciente |
| `05-priority_queue-invertida.cc` | 1.5 | `priority_queue` de **mínimos** |
| `06-set.cc` | 1.6 | `set`: intersección de dos secuencias |
| `07-map.cc` | 1.7 | `map`: contar palabras en orden alfabético |
| `08-cpp11.cc` | 1.8 | novedades de C++11: `auto`, `for` sobre colecciones, listas de inicialización |
| `09-unordered_set.cc` | 1.9 | `unordered_set` |
| `10-unordered_map.cc` | 1.10 | `unordered_map` |
| `11-hash-propio.cc` | 1.11 | definir una función de hash para un tipo propio |

## Chuleta de contenedores

| Contenedor | Implementación interna | Búsqueda | Inserción | ¿Ordenado? |
|---|---|---|---|---|
| `vector` | array dinámico | Θ(n) | Θ(1) amortizado al final | no |
| `list` | lista doblemente enlazada | Θ(n) | Θ(1) con iterador | no |
| `set` / `map` | **árbol rojinegro** | Θ(log n) | Θ(log n) | **sí** |
| `unordered_set` / `unordered_map` | **tabla de hash** | Θ(1) medio | Θ(1) medio | no |
| `stack` | adaptador (sobre `deque`) | — | Θ(1) | LIFO |
| `queue` | adaptador (sobre `deque`) | — | Θ(1) | FIFO |
| `priority_queue` | adaptador: **heap** sobre `vector` | `top()` Θ(1) | Θ(log n) | solo el extremo |

Los capítulos 04 y 05 implementan a mano lo que hay detrás de `map`,
`unordered_map` y `priority_queue`.

## Dos detalles que se preguntan mucho

### `priority_queue` es de MÁXIMOS

```cpp
priority_queue<int> pq;                                  // máximos
priority_queue<int, vector<int>, greater<int>> pq;       // mínimos
```

El parámetro importante es el **tercero**, pero hay que dar también el segundo
(sección 1.5). La alternativa es insertar los valores con el signo cambiado, que
es lo que hace Prim en `06-Grafos/Prim/`.

### `m[clave]` en un `map` INSERTA

```cpp
while (cin >> x) ++m[x];     // si x no está, crea m[x] = 0 y luego lo incrementa
```

Eso es muy cómodo para contar, pero cuidado: `if (m[k] == 0)` **crea** la entrada
`k`. Para consultar sin insertar, usa `m.find(k)` o `m.count(k)`.

## Funciones de hash propias (1.11)

Para meter un tipo propio en un `unordered_set`/`unordered_map` hacen falta
**dos** cosas:

1. `operator==` para comparar por igualdad.
2. Un functor de hash (una `struct` con `size_t operator()(const T&) const`).

```cpp
unordered_set<Point, Point::Hash> cloud;
```

Nota: la función de hash del ejemplo (`hash(x) + hash(y) + hash(z)`) es sencilla
pero **floja**: los puntos `(1,2,3)` y `(3,2,1)` colisionan. En código real se
combinan con desplazamientos y números primos:

```cpp
size_t h = hash<int>()(p.x);
h ^= hash<int>()(p.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
h ^= hash<int>()(p.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
```

## Compilar

```bash
g++ -std=c++17 02-stack.cc -o stack
echo "1 2 3 4 5" | ./stack
```

Los ficheros 1.8 a 1.11 necesitan **C++11 como mínimo** (`-std=c++11`). Con
`-std=c++17` funcionan todos.
