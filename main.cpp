#include <stdlib.h>
#include <cstring>
#include <ctime>
#include "Graph.h"
#include "Astar.h"

using namespace std;

void usage() {
    cout<<"Usage:"<<endl<<"./lab6 algorithm mapfile [coordinate] start end"<<endl;
}

int main(int argc, char**argv) {
    if (argc < 5) {
        usage();
        return 1;
    }
    else if ((strcmp(argv[1], "dijkstra") == 0 && argc > 5)
    || ((strcmp(argv[1], "Astar") == 0 || strcmp(argv[1], "ID") == 0) &&
    argc != 6)) {
        usage();
        return 1;
    }
    string filename(argv[2]);
    Graph g;
    g.parseDataFromFile(filename);
    if (strcmp(argv[1], "dijkstra") == 0) {
        int start = atoi(argv[3]);
        int end = atoi(argv[4]);
        
        clock_t time;
        time = clock();
        //cout<<"start dijkstra"<<endl;

        g.dijkstra(start, end);

        time = clock() - time;
        cout<<"Time elapse: "<<((float) time)/CLOCKS_PER_SEC<<endl;
        return 0;
    }
    else if (strcmp(argv[1], "Astar") == 0 || strcmp(argv[1], "ID") == 0) {
        string coordinate_file(argv[3]);
        g.readCoordinates(coordinate_file);
        int start = atoi(argv[4]);
        int end = atoi(argv[5]);
        if (strcmp(argv[1], "Astar") == 0) {
            clock_t time;
            time = clock();

            g.a_star(start, end);

            time = clock() - time;
            cout<<"Time elapse: "<<((float) time)/CLOCKS_PER_SEC<<endl;
        }
        else {
            clock_t time;
            time = clock();

            g.ida_star(start, end);

            time = clock() - time;
            cout<<"Time elapse: "<<((float) time)/CLOCKS_PER_SEC<<endl;
        }
        return 0;
    }
    return 1;
}

