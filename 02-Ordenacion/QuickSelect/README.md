# Quickselect (selección del k-ésimo) · EXTRA

> No está en el PDF, pero es la variante natural de quicksort y responde a una
> pregunta muy frecuente: *"¿cuál es la mediana?"* sin ordenar todo el vector.

**Fichero:** `quick_select.cc`

## En qué consiste

Es quicksort, pero **bajando por una sola rama**. Después de particionar sabes en
qué mitad cae la posición `k` que buscas, así que la otra mitad se descarta
entera.

```
buscar k=3 en [5 3 9 1 7 2]
particiona -> [3 1 2 | 5 9 7]   pivote en q=3
k == q  -> ¡lo tenemos!
```

Si `k < q` sigues por la izquierda, si `k > q` por la derecha. La implementación
del fichero es **iterativa** (un `while` que mueve `l` y `r`), así que no gasta
pila.

Usa la partición de **Lomuto** en lugar de la de Hoare porque Lomuto deja el
pivote en su posición **definitiva**, que es justo lo que hace falta para poder
comparar `k == q`. El pivote se escoge al azar.

## Coste

| | |
|---|---|
| Caso medio | **Θ(n)** |
| Peor caso | **Θ(n²)** (improbable con pivote aleatorio) |
| Memoria extra | Θ(1) |

Por qué el caso medio es lineal: cada partición descarta (en media) la mitad del
vector, así que el trabajo total es n + n/2 + n/4 + … = **2n**. Es una serie
geométrica, no un árbol como en quicksort: por eso baja de n log n a n.

Existe el algoritmo *median of medians*, que garantiza Θ(n) incluso en el caso
peor eligiendo el pivote de forma determinista, pero sus constantes son tan malas
que en la práctica no se usa.

## Cuándo tiene sentido

- Mediana, percentiles, "los k mejores".
- En la STL: **`nth_element(v.begin(), v.begin()+k, v.end())`**, que es
  exactamente esto (introselect). Si solo necesitas el k-ésimo, usarlo en vez de
  `sort` te ahorra el factor log n.

## Probarlo

```bash
g++ -std=c++17 quick_select.cc -o qsel
echo "3 5 3 9 1 7 7 2 8 0 4" | ./qsel   # k=3 -> 3
```

(La primera cifra de la entrada es `k`, contando desde 0.)
