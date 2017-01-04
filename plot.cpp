#include "plot.h"
#include <assert.h>
#include <string>
#include <math.h>
#include <stdexcept>
int window1;
vector<Vertex *> inpoints;
Graph g;

//window configurations and registering callbacks
void graphicsInit (int argc, char **argv, int wsize, int linewidth, 
		   float pointsize)
{
  glutInit(&argc, argv);
  glutInitWindowSize(wsize, wsize);
  glutInitWindowPosition(50, 50);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  window1 = glutCreateWindow("Map");
  glutMouseFunc(NULL);
  glutDisplayFunc(display);//callback function invoked to refresh window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, wsize, 0, wsize);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLineWidth(linewidth);
  glPointSize(pointsize);
  menuInit();// menu displayed on right-click
  glutMainLoop();
}

void menuInit ()
{
  glutCreateMenu(menu);
  glutAddMenuEntry("clear", 1);
  glutAddMenuEntry("dijkstra", 2);
  glutAddMenuEntry("A*", 3);
  glutAddMenuEntry("IDA*", 4);
  glutAddMenuEntry("exit", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu (int value)
{
  string name;
  switch (value) {
  case 1:
    inpoints.clear();
    glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    break;
  case 2:
    readMap(inpoints);
    glutPostRedisplay();
    break;
  case 3:
    readMap(inpoints);
    glutPostRedisplay();
    break;
  case 4:
    readMap(inpoints);
    glutPostRedisplay();

  case 5:
    exit(0);
  }
}


void readMap(vector<Vertex *> &inpoints) {
  cerr << "Enter edge file name: ";
  string mapfile, nodefile;
  cin >> mapfile;
  cerr << "Enter node file name: ";
  cin >> nodefile;
  inpoints.clear();
  (g.v).clear();
  (g.e).clear();
  (g.mappings).clear();
  g.parseDataFromFile(mapfile);
  g.readCoordinates(nodefile);
  inpoints = g.v;
}

void display ()
{
  float white[3] = {1.0f, 1.0f, 1.0f};
  clearScreen(white);
  glColor3f(1.0f, 0.0f, 0.0f); // red
  //glScaled(5, 5, 5);
  drawPoints(inpoints);
  glColor3f(0.0f, 0.0f, 0.0f); // black
  drawLines(inpoints);

  glFlush();
}

/*Point point (int x, int y)
{
  return Point(x, glutGet(GLUT_WINDOW_WIDTH) - y);
}*/

void clearScreen (float *color)
{
  glClearColor(color[0], color[1], color[2], color[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawPoints (vector<Vertex *> points)
{
  glBegin(GL_POINTS);
  
  //cerr<<points.size()<<endl;
  for(int i = 0; i < points.size(); i++) {
  	glVertex(points[i]);
  }
  
  glEnd();
}

void drawLines (vector<Vertex *> points)
{
  for (vector<Vertex *>::iterator it = points.begin(); it != points.end(); it++) {
    Vertex *vert = (*it);

    vert->draw = true;
    for (vector<Edge *>::iterator t = (vert->edges).begin(); t != (vert->edges).end(); t++) {
        Vertex *incident;
        if (((*t)->vertices)[0]->nodeID == vert->nodeID) {
            incident = ((*t)->vertices)[1];
        }
        else {
            incident = ((*t)->vertices)[0];
        }

        if (incident->draw) continue;

        glBegin(GL_LINES);
        glVertex2d(vert->x_coor /100, (/*glutGet(GLUT_WINDOW_WIDTH) - */vert->y_coor)/100);

        glVertex2d(incident->x_coor/100, (/*glutGet(GLUT_WINDOW_WIDTH) - */incident->y_coor)/100);
        glEnd();
        incident->draw = true;
    }
  }
}

void glVertex (const Vertex * p)
{
    glVertex2d(p->x_coor/100, (/*glutGet(GLUT_WINDOW_WIDTH) - */p->y_coor)/100);
}


int main (int argc, char **argv)
{
    //launch GUI
    int wsize = 900; 
    int linewidth = 1;
    float pointsize = 3.0f;
    graphicsInit(argc, argv, wsize, linewidth, pointsize);
    return 0;
}
