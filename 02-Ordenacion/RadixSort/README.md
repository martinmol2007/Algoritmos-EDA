# Radix Sort (ordenación por dígitos) · EXTRA

> No está en el PDF. Es la forma de aplicar counting sort cuando el rango de
> valores es grande.

**Fichero:** `radix_sort.cc`

## En qué consiste

Ordena los números **dígito a dígito**, usando en cada pasada un algoritmo
estable (aquí, counting sort sobre ese dígito).

La versión implementada es **LSD** (*least significant digit first*): empieza por
el dígito menos significativo y acaba por el más significativo.

```
entrada:  170 045 075 090 802 024 002 066
dígito 1: 170 090 802 002 024 045 075 066
dígito 2: 802 002 024 045 066 170 075 090
dígito 3: 002 024 045 066 075 090 170 802
```

**La estabilidad es imprescindible**: cuando ordenas por el dígito `k`, el orden
que habías conseguido con los dígitos `0..k-1` tiene que sobrevivir a los
empates. Si usas un algoritmo no estable, radix sort no funciona.

El fichero trabaja en **base 256** (8 bits por pasada), así que un `int` de 32
bits necesita 4 pasadas. Los negativos se tratan aparte: se separan, se ordenan
en valor absoluto y se vuelven a poner al principio en orden inverso.

## Coste

| | |
|---|---|
| Tiempo | **Θ(d · (n + b))**, con d = nº de dígitos y b = base |
| Con enteros de 32 bits en base 256 | d = 4, b = 256 ⟹ **Θ(n)** en la práctica |
| Memoria extra | Θ(n + b) |
| Estable | Sí |
| In-place | No |

Hay un compromiso en la elección de la base: más base ⟹ menos pasadas pero más
memoria para los contadores. La base 256 suele ser el punto dulce.

## Cuándo tiene sentido

- Enteros de tamaño fijo, cadenas de longitud acotada, fechas, IPs.
- Cuando n es muy grande: para n ≳ 10⁶ suele ganar a `sort`.
- No sirve para tipos con un orden arbitrario definido por el usuario: necesitas
  poder descomponer la clave en dígitos.

## Probarlo

```bash
g++ -std=c++17 radix_sort.cc -o rs
echo "170 45 75 90 802 24 2 66" | ./rs    # -> 2 24 45 66 75 90 170 802
```
