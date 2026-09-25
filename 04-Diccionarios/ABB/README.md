# ABB · Árbol Binario de Búsqueda

**PDF:** sección 3.4 · **Ficheros:** `diccionario_abb.cc`, `recorridos.cc` (extra)

## En qué consiste

Un árbol binario que cumple, **para todo nodo `u`**:

> todas las claves del subárbol izquierdo de `u` < clave de `u` < todas las
> claves del subárbol derecho de `u`

```
         50
       /    \
     30      70
    /  \    /  \
  20   40  60   80
```

Esa invariante es lo que permite buscar como en una búsqueda binaria: comparas
con la raíz y bajas por un lado o por el otro, descartando el subárbol contrario
entero. Cada paso baja un nivel, así que el coste es la **altura** del árbol.

Consecuencia importante: el **recorrido inorden** (izquierdo, raíz, derecho) da
las claves **ordenadas**. Ver `recorridos.cc`.

## Coste

| Operación | Coste |
|---|---|
| `assign`, `erase`, `query`, `contains` | **Θ(h)** |
| `size` | Θ(1) |
| Constructor por copia, destructor | Θ(n) |
| `operator=` | Θ(n + d.n) |

Y ahora la pregunta clave: **¿cuánto vale h?**

| Situación | h |
|---|---|
| Árbol equilibrado | Θ(log n) |
| Árbol construido con claves en **orden aleatorio** | **Θ(log n) en esperanza** |
| Claves insertadas **ya ordenadas** | **n** (el árbol es una lista) |

Ese último caso es el problema: insertar 1, 2, 3, 4, 5… produce un árbol que solo
crece hacia la derecha, y entonces todo cuesta Θ(n). Y las claves ordenadas son
una entrada perfectamente normal en la vida real. **La solución es el AVL.**

Además, los borrados degradan el árbol aunque las inserciones fuesen aleatorias:
el análisis Θ(log n) esperado supone que **nunca se borra**.

## Las tres versiones de borrado

Borrar un nodo con 0 o 1 hijo es trivial: lo sustituyes por su hijo (o por nada).
El caso interesante es el nodo con **dos hijos**, y el PDF da tres soluciones:

| Versión | Qué hace | Problema |
|---|---|---|
| `erase_1` | Cuelga el subárbol izquierdo del **mínimo del subárbol derecho** y sube el derecho | **El árbol se degrada rápido**: la altura crece sin control |
| `erase_2` | **Copia** clave e info del mínimo del subárbol derecho en el nodo, y borra ese mínimo (que no tiene hijo izquierdo) | Copia claves e informaciones, que pueden ser objetos caros |
| `erase_3` | **`extract_minimum`**: extrae el nodo mínimo del subárbol derecho y lo coloca físicamente en el hueco | Ninguno importante — **es la que usa `erase()`** |

Las tres son Θ(h). La diferencia es de calidad (v1) y de constantes (v2 vs v3).

Por qué se usa el **mínimo del subárbol derecho** (o simétricamente el máximo del
izquierdo): es el **sucesor inmediato** de la clave que se borra, así que es el
único que puede ocupar su sitio sin romper la invariante del ABB.

## Regla del tres

Esta clase sí necesita **constructor por copia, `operator=` y destructor**
escritos a mano, porque gestiona memoria con punteros crudos. Si no los
escribieras, copiar un diccionario copiaría el puntero `root` y los dos objetos
compartirían los nodos → doble `delete` y corrupción de memoria.

`copy` y `free` son las dos funciones que los implementan, y ambas son
recorridos: `copy` en **preorden**, `free` en **postorden** (hay que borrar los
hijos antes que el padre).

## `recorridos.cc` (extra)

No está en el PDF. Implementa los cuatro recorridos clásicos sobre un ABB:

| Recorrido | Orden | Para qué sirve |
|---|---|---|
| **Preorden** | raíz, izq, der | copiar / serializar el árbol |
| **Inorden** | izq, raíz, der | **claves ordenadas** |
| **Postorden** | izq, der, raíz | destruir el árbol, calcular alturas/tallas |
| **Por niveles** | nivel a nivel | BFS sobre el árbol; necesita una **cola** |

Más un inorden iterativo con pila explícita, para ver qué hace realmente la
recursión.

Todos cuestan Θ(n).

## Probarlo

```bash
g++ -std=c++17 diccionario_abb.cc -o abb && ./abb
g++ -std=c++17 recorridos.cc -o rec && ./rec
```
