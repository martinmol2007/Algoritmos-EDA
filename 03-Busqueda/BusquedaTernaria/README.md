# Búsqueda ternaria · EXTRA

**Fichero:** `busqueda_ternaria.cc`

## En qué consiste

La búsqueda binaria encuentra una **frontera** en algo monótono. La ternaria
encuentra el **pico** de algo **unimodal**: una función que crece hasta un máximo
y después decrece (o al revés, para mínimos).

```
        /\
       /  \        unimodal: sirve
      /    \

      /\  /\
     /  \/  \      dos picos: NO sirve
```

Se parten los datos en tres con dos puntos `m1 < m2`:

- si `f(m1) < f(m2)` → el pico está en `[m1, r]`, descartas `[l, m1)`
- si no → el pico está en `[l, m2]`, descartas `(m2, r]`

Cada vuelta descarta **un tercio** del intervalo.

## Coste

| | |
|---|---|
| Tiempo | **Θ(log_{3/2} n) = Θ(log n)** |
| Evaluaciones de f por vuelta | 2 |
| Memoria extra | Θ(1) |

Nota: es asintóticamente igual que la binaria, pero con peores constantes
(descarta 1/3 en vez de 1/2 y evalúa `f` dos veces). Para funciones caras de
evaluar existe la búsqueda por **sección áurea**, que reaprovecha una evaluación
por vuelta.

## Las dos versiones del fichero

- **`ternaria_real`**: sobre reales, para cuando la función es continua. El bucle
  para cuando el intervalo es menor que `eps`. Ojo con pedir `eps` demasiado
  pequeño: con `double` no bajarás de ~1e-15.
- **`ternaria_vector`**: sobre enteros. Aquí hay que tener cuidado con los
  empates (`v[m1] == v[m2]`), así que el bucle para cuando quedan ≤ 3 elementos y
  se revisan a mano.

## Cuándo tiene sentido

- Minimizar una función de coste que tiene forma de U (típico en problemas de
  optimización geométrica: la distancia mínima a una recta, el punto óptimo de
  encuentro…).
- Problemas de competición del estilo "minimiza f(x)" donde f es convexa.

No lo uses si no puedes **demostrar** la unimodalidad: si la función tiene dos
picos, la ternaria devolverá cualquiera de los dos, o ninguno.

## Probarlo

```bash
g++ -std=c++17 busqueda_ternaria.cc -o bt
./bt
# maximo continuo en x = 3
# maximo del vector en la posicion 4 (valor 12)
```
