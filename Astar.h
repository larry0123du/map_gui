#ifndef ASTAR_H
#define ASTAR_H
#include "Graph.h"
bool compare_a(Vertex *a, Vertex *b);

double heuristic(Vertex *a, Vertex *b);

void upheap(vector<Vertex *> &v, int index);

void down(vector<Vertex *> &v);

void update(vector<Vertex *> &v, Vertex *vt);

#endif
