# Ordenación topológica

**PDF:** sección 5.4 · **Fichero:** `topological_sort.cc`

## En qué consiste

Dado un **DAG** (grafo dirigido acíclico), ordenar sus vértices de forma que
**un vértice `v` nunca aparezca antes que un vértice `u` si hay un camino de `u`
a `v`**.

Es el problema de "ordenar tareas por dependencias": compilar módulos, planificar
asignaturas con prerrequisitos, resolver un `Makefile`, ordenar la instalación de
paquetes.

## El algoritmo (Kahn)

La versión del PDF usa **grados de entrada**:

1. Calcula `ge[v]` = grado de entrada de cada vértice (cuántas dependencias tiene
   pendientes). Coste Θ(|V| + |E|).
2. Mete en una pila todos los vértices con `ge[v] == 0`: los que no dependen de
   nadie y pueden salir ya.
3. Mientras la pila no esté vacía: saca `u`, añádelo al resultado, y por cada
   vecino `v` decrementa `ge[v]`. Si llega a 0, `v` ya no tiene dependencias
   pendientes → a la pila.

```cpp
for (int v : G[u]) {
    if (--ge[v] == 0) S.push(v);
}
```

La pila se puede cambiar por una cola o por una cola de prioridad sin afectar a
la corrección: solo cambia **cuál** de las ordenaciones válidas obtienes (con una
cola de prioridad obtienes la lexicográficamente menor).

## Coste

| | |
|---|---|
| Tiempo | **Θ(\|V\| + \|E\|)** |
| Memoria | Θ(\|V\|) |

Cada vértice entra y sale de la pila una vez; cada arco se recorre una vez al
decrementar.

## Detección de ciclos

**La ordenación topológica solo existe si el grafo es acíclico.** El algoritmo lo
detecta gratis: si al acabar la lista tiene **menos de |V| vértices**, es que
algunos nunca llegaron a grado de entrada 0, y eso solo puede pasar si están en
un ciclo (o dependen de uno).

El `main` del fichero hace justamente esa comprobación.

## El otro método (DFS)

Hay una segunda forma clásica: hacer un DFS y devolver los vértices en **orden
inverso de finalización** (postorden invertido). También es Θ(|V| + |E|).

La versión de Kahn tiene la ventaja de detectar los ciclos de forma natural y de
no gastar pila de recursión.

## No es única

Un DAG suele admitir **muchas** ordenaciones topológicas válidas. Con el ejemplo
del fichero, `5 2 3 4 1 0` es una, pero `4 5 2 3 1 0` también lo es. Cualquiera
que respete todas las aristas vale.

## Probarlo

```bash
g++ -std=c++17 topological_sort.cc -o ts
printf '6 6\n5 2\n5 0\n4 0\n4 1\n2 3\n3 1\n' | ./ts
# 5 2 3 4 1 0
```
