#ifndef PLOT_H
#define PLOT_H

#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Graph.h"

using namespace std;

void graphicsInit (int argc, char **argv, int wsize, int linewidth, 
		   float pointsize);
void menuInit ();

void menu (int value);

//Point point (int x, int y);

void readMap(vector<Vertex *> &inpoints);

void display ();

void clearScreen (float *color);

void drawPoints (vector<Vertex *> pts);

void drawLines (vector<Vertex *> pts);

void glVertex (const Vertex * p);

#endif
