# Asignación de tareas (branch and bound)

**PDF:** sección 6.6 · **Fichero:** `asignacion_tareas.cc`

## El problema

Un jefe tiene `n` trabajadores y `n` tareas. El trabajador `i` tarda `T[i][j]` en
hacer la tarea `j`. Hay que asignar **una tarea a cada trabajador** minimizando
el **tiempo total**.

Es el *assignment problem*. Ojo: aquí es un problema de **optimización**, no de
búsqueda — no basta con encontrar *una* solución, hay que encontrar la **mejor**.

## La diferencia con los anteriores

En n reinas o en el caballo, en cuanto encuentras una solución has terminado.
Aquí **hay que explorar todo el espacio**… salvo que puedas demostrar que una
rama no puede contener el óptimo. Eso es el **branch and bound**.

## La cota (`bound`)

```cpp
double bound(int worker, int task) {
    double f = 0;
    for (int i = worker+1; i < n; ++i) {      // trabajadores que quedan
        double m = infinity;
        for (int j = 0; j < n; ++j) if (not done[j]) {
            m = min(m, T[i][j]);              // su tarea libre más rápida
        }
        f += m;
    }
    return f;
}
```

Para cada trabajador que queda por asignar, coge el **mínimo** de los tiempos de
las tareas todavía libres, y los suma.

**Es optimista**: ignora que dos trabajadores no pueden coger la misma tarea, así
que el tiempo real que falta será **≥** esta cota. Y eso es exactamente lo que la
hace válida:

```cpp
if (t + T[worker][task] + bound(worker, task) < best) {
    recursive(worker+1, t + T[worker][task]);
}
```

Si ni siquiera en el escenario más favorable imaginable se baja de `best`, esa
rama **no puede** contener el óptimo y se descarta entera.

> **La regla de oro del branch and bound**: la cota tiene que ser optimista. Si
> sobreestima (es pesimista), podarías ramas que contenían el óptimo y el
> algoritmo daría una respuesta incorrecta.

## El compromiso

| Cota | Coste de calcularla | Poda |
|---|---|---|
| Muy floja (p.ej. 0) | Θ(1) | casi nada |
| Esta (`bound`) | Θ((n-worker)·n) | buena |
| Muy ajustada (resolver el subproblema) | carísima | máxima |

Hay que encontrar el punto donde el tiempo que ahorras podando compensa el que
gastas calculando la cota. Esta cota cuesta Θ(n²) por nodo, y aun así compensa
mucho.

## Coste

| | |
|---|---|
| Espacio de búsqueda | **n!** |
| Con la poda | exponencial, pero manejable hasta n ≈ 12-15 |

## Dato importante

Este problema concreto **tiene solución polinómica**: el **algoritmo húngaro**
(Kuhn-Munkres) lo resuelve en Θ(n³). No es NP-difícil.

O sea: el backtracking de aquí está como **ejercicio de la técnica**, no porque
sea la mejor forma de resolverlo. Merece la pena tenerlo claro — no todo problema
que "parece" exponencial lo es.

## Probarlo

```bash
g++ -std=c++17 asignacion_tareas.cc -o sc
echo 8 | ./sc
```

El `main` genera la matriz de tiempos al azar con `randmatrix(n)` de `eda.hh`.
Para resultados reproducibles, `rand()` no se siembra, así que siempre sale la
misma matriz.
