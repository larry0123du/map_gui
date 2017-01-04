#include <iostream>
#include "dijkstra.h"

int main() {
    Graph g;
    g.parseDataFromFile("mygraph.cedge");
    g.printGraph();
    return 0;
}
