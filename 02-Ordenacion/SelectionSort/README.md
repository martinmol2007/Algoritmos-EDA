# Selection Sort (ordenación por selección)

**PDF:** sección 2.1 · **Fichero:** `selection_sort.cc`

## En qué consiste

En la iteración `i` el vector está dividido en dos partes: `v[0..i-1]` ya
contiene los `i` elementos más pequeños **en su sitio definitivo**, y `v[i..n-1]`
es el resto. El algoritmo busca el mínimo de la parte derecha (`pos_min`) y lo
intercambia con `v[i]`. Después de `n-1` pasadas el vector está ordenado.

```
[ ordenado y definitivo | por ordenar ]
                        ^ i
                          busca el mínimo aquí y ponlo en i
```

## Coste

| | |
|---|---|
| Comparaciones | (n-1) + (n-2) + … + 1 = n(n-1)/2 = **Θ(n²)** siempre |
| Intercambios | **Θ(n)** (exactamente n-1) |
| Memoria extra | Θ(1) |
| Estable | No (el swap puede saltarse elementos iguales) |

El número de comparaciones **no depende de la entrada**: mejor caso, caso medio y
peor caso son los tres Θ(n²). Es el único de los cuadráticos que no mejora con
vectores casi ordenados.

## Cuándo tiene sentido

Casi nunca, salvo un detalle: hace **Θ(n) escrituras** en memoria, muchas menos
que insertion o bubble. Si copiar un elemento es carísimo (registros enormes) y
comparar es barato, selection sort puede ganar.

## Detalle de implementación

En el PDF `sel_sort` llama a `pos_min` antes de que esté definida. En C++ eso no
compila tal cual, así que en el fichero se ha añadido una **declaración previa**
de `pos_min`. El cuerpo de las funciones es literalmente el del PDF.

## Probarlo

```bash
g++ -std=c++17 selection_sort.cc -o sel
echo "5 3 9 1 7 2" | ./sel      # -> 1 2 3 5 7 9
```
