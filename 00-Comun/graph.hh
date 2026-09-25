// graph.hh --- Seccion 5.1 del PDF: definicion del tipo grafo.
//
// Los grafos se representan mediante una tabla de listas de adyacencia,
// suponiendo que los vertices son los enteros entre 0 y |V|-1.
// Estos grafos son dirigidos, pero el tipo tambien sirve para representar
// grafos no dirigidos poniendo cada arista como dos arcos.
// Las listas de adyacencia se implementan con vectores dinamicos.
//
// Este codigo usa C++11.

#ifndef graph_hh
#define graph_hh

#include <vector>
#include <list>
using namespace std;

typedef vector<vector<int>> graph;

#endif
