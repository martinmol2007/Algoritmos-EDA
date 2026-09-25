# LCS · Subsecuencia común más larga · EXTRA

**Fichero:** `lcs.cc`

## El problema

Dadas dos cadenas, encontrar la **subsecuencia** más larga que aparece en las
dos.

**Subsecuencia ≠ subcadena**: una subsecuencia no tiene por qué ser contigua,
solo tiene que conservar el orden.

```
A = AGGTAB
B = GXTXAYB
LCS = GTAB   (longitud 4)
```

`GTAB` aparece en las dos en ese orden, aunque con letras intercaladas.

## La formulación

**Subproblema:**

> `dp[i][j]` = longitud de la LCS de los prefijos `A[0..i-1]` y `B[0..j-1]`

**Recurrencia:** se mira el último carácter de cada prefijo.

```
si A[i-1] == B[j-1]:   dp[i][j] = dp[i-1][j-1] + 1
si no:                 dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

- Si los últimos caracteres **coinciden**, forman parte de la LCS: se suma 1 al
  resultado de los dos prefijos sin ellos.
- Si **no coinciden**, al menos uno de los dos sobra, así que se prueban las dos
  opciones y se coge la mejor.

**Caso base:** `dp[0][j] = dp[i][0] = 0` (con una cadena vacía, la LCS es vacía).

**Respuesta:** `dp[n][m]`.

## Reconstrucción

La tabla da la longitud. Para recuperar la cadena, se va hacia atrás desde
`dp[n][m]` repitiendo el razonamiento de la recurrencia:

```cpp
while (i > 0 and j > 0) {
    if (A[i-1] == B[j-1])              { sub += A[i-1]; --i; --j; }
    else if (dp[i-1][j] >= dp[i][j-1])   --i;
    else                                 --j;
}
reverse(sub.begin(), sub.end());   // se construyó al revés
```

Nota: la LCS **no tiene por qué ser única**. Con `AGCAT` y `GAC` hay tres LCS de
longitud 2 (`AC`, `GA`, `GC`). Este código devuelve una cualquiera; cuál depende
del desempate `>=`.

## Coste

| | Tabla completa | Memoria lineal |
|---|---|---|
| Tiempo | **Θ(n·m)** | Θ(n·m) |
| Memoria | Θ(n·m) | **Θ(min(n,m))** |
| Reconstruye la cadena | **sí** | no |

Igual que en la mochila, `dp[i][·]` solo depende de `dp[i-1][·]`, así que con dos
filas basta si solo quieres la longitud.

(Existe el algoritmo de **Hirschberg**, que reconstruye la LCS completa usando
solo Θ(min(n,m)) de memoria, a base de divide y vencerás sobre la tabla. Sigue
siendo Θ(n·m) de tiempo.)

## Para qué sirve

- **`diff`**: las líneas que *no* están en la LCS de los dos ficheros son
  exactamente las que hay que añadir o borrar. Git, `svn diff` y las herramientas
  de *merge* viven de esto.
- **Bioinformática**: comparar secuencias de ADN o proteínas.
- **Control de plagio** y detección de similitud entre textos.
- Variantes cercanas: la **distancia de edición** (Levenshtein) es la misma idea
  con tres operaciones en vez de dos, y la **subcadena común más larga** (la
  contigua) tiene una recurrencia aún más simple.

## Probarlo

```bash
g++ -std=c++17 lcs.cc -o lcs
echo "AGGTAB GXTXAYB" | ./lcs
# LCS = GTAB  (longitud 4)
```
