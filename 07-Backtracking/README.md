# 07 · Backtracking

Capítulo 6 del PDF (`Backtracking`).

## Qué es el backtracking

Es la estrategia para problemas en los que hay que **construir una solución
tomando decisiones sucesivas** y no existe una fórmula directa: se prueba una
decisión, se sigue en profundidad, y si no lleva a nada **se deshace** y se
prueba la siguiente.

Es un **DFS sobre el árbol de soluciones parciales**:

```
                    ()
             /      |      \
          (0)      (1)      (2)         <- decisión 1
         /  \      /  \     /  \
     (0,1)(0,2)  ...  ...  ...  ...     <- decisión 2
```

## El esquema

Todos los algoritmos del capítulo tienen la misma forma:

```cpp
void recursive(int i) {
    if (i == n) {                  // 1. ¿solución completa?
        tratar_solucion();
    } else {
        for (cada opción j) {      // 2. probar todas las opciones
            if (es_valida(i, j)) { //    (poda por validez)
                marcar(i, j);      // 3. MARCAR
                recursive(i+1);    // 4. seguir
                desmarcar(i, j);   // 5. DESMARCAR  <- el "backtrack"
            }
        }
    }
}
```

**El paso 5 es la clave.** Deshacer el marcaje al volver es lo que da nombre a la
técnica y lo que permite reutilizar la misma estructura de datos para todo el
árbol, en vez de copiarla en cada nodo.

## Las tres formas de podar

| Tipo de poda | Qué hace | Dónde se ve |
|---|---|---|
| **Por validez** | descarta opciones que violan una restricción | n reinas, cuadrados latinos |
| **Por optimalidad (bound)** | descarta ramas que no pueden mejorar la mejor solución conocida | asignación de tareas, TSP, mochila v2 |
| **Por parada** | corta en cuanto se encuentra **una** solución | n reinas v3, saltos de caballo, hamiltoniano |

La poda por optimalidad con cota se llama **branch and bound**. Para que sea
correcta, la cota tiene que ser **optimista**: nunca puede sobreestimar lo bueno
que puede llegar a ser una rama, o descartarías el óptimo.

## Marcaje incremental

La otra idea que recorre todo el capítulo: en vez de comprobar la validez
recorriendo todo lo hecho hasta ahora (Θ(i) por comprobación), se mantienen
**marcas** que permiten comprobarla en **Θ(1)**.

Es exactamente lo que diferencia `n_reinas_1.cc` de `n_reinas_2.cc`.

## Coste

El backtracking es **exponencial** en el caso peor, casi siempre. Muchos de estos
problemas son **NP-completos** o **NP-difíciles** (TSP, mochila, ciclo
hamiltoniano): no se conoce ningún algoritmo polinómico, y se conjetura que no
existe.

Las podas no cambian el orden asintótico, pero **sí cambian por completo la
usabilidad**: pueden ser la diferencia entre resolver n = 10 y resolver n = 30.

| Problema | Espacio de búsqueda |
|---|---|
| n reinas | n! (con marcaje) |
| Cuadrados latinos | crece brutalmente: 1, 2, 12, 576, 161280, 812851200… |
| Saltos del caballo | 8^(n²) sin podar |
| Asignación de tareas | n! |
| TSP | (n-1)! |
| Mochila | 2ⁿ |

## Contenido

| Carpeta | Sección | Ficheros |
|---|---|---|
| `NReinas/` | 6.1, 6.2, 6.3 | `n_reinas_1.cc`, `n_reinas_2.cc`, `n_reinas_3.cc` |
| `CuadradosLatinos/` | 6.4 | `cuadrados_latinos.cc` |
| `SaltosCaballo/` | 6.5 | `saltos_caballo.cc` |
| `AsignacionTareas/` | 6.6 | `asignacion_tareas.cc` |
| `GrafoHamiltoniano/` | 6.7 | `grafo_hamiltoniano.cc` |
| `TSP/` | 6.8 | `tsp.cc` |
| `Mochila/` | 6.9, 6.10 | `mochila_1.cc`, `mochila_2.cc` |

Todos usan `00-Comun/eda.hh` (tipo `matrix`, `boolean`, `readint()`,
`infinity`, `randvector`, `randmatrix`, `now()`).

## Y cuando el backtracking no basta

Si el problema tiene **subproblemas que se repiten**, la programación dinámica
puede convertir un exponencial en un polinómico. La mochila es el ejemplo
perfecto: aquí es Θ(2ⁿ) y en `08-ProgramacionDinamica/MochilaDP/` es Θ(n·C).
