#include "Graph.h"
using namespace std;

int compare_d(Vertex *a, Vertex *b) {
    if ((a->distance) - (b->distance) >= 0.0000001) {
        return 1;
    }
    else if (fabs((a->distance) - (b->distance)) < 0.0000001) {
        return 0;
    }
    else {
        return -1;
    }
}

void downheap(vector<Vertex *> &v, int start, int end) {
    int root = start;
    while (root * 2 + 1 <= end) {
        int left = root * 2 + 1;
        int swap_node = root;

        if (compare_d(v[swap_node], v[left]) >= 0) {
            swap_node = left;
        }
        if (left + 1 <= end && compare_d(v[swap_node], v[left + 1]) >= 0) {
            swap_node = left + 1;
        }
        if (swap_node == root) return;
        else {
            swap(v, swap_node, root);
            root = swap_node;
        }
    }
}

void heapify(vector<Vertex *> &v) {
    int start = (v.size() - 2) / 2;
    while (start >= 0) {
        downheap(v, start, v.size() - 1);
        start--;
    }
}

void Graph::dijkstra(int startNode, int endNode) {
    vector<Vertex *> open;
    vector<Vertex *> closed;

    Vertex *start = findVertex(startNode);
    if (start == NULL) {
        cout<<"Cannot find vertex"<<endl;
        exit(1);
    }

    Vertex *end = findVertex(endNode);
    if (end == NULL) {
        cout<<"Cannot find vertex"<<endl;
        exit(1);
    }

    start->distance = 0;
    open.push_back(start);

    while (!open.empty()) {
        heapify(open);
        Vertex *min = open.front();
        Vertex *incident;
        double dist;
        for (vector<Edge *>::iterator it = (min->edges).begin(); it != (min->edges).end(); it++) {
            if (((*it)->vertices)[0]->nodeID == min->nodeID) {
                incident = ((*it)->vertices)[1];
            }
            else {
                incident = ((*it)->vertices)[0];
            }

            if (incident->discovered) continue;

            if ((dist = ((*it)->weight + min->distance)) < incident->distance) {
                incident->distance = dist;
                incident->parent = min;
                open.push_back(incident);
            }
        }
        open[0]->discovered = true;
        closed.push_back(open[0]);
        open[0] = open.back();
        open.pop_back();
    }
    
    if (end->distance >= numeric_limits<double>::max() - 1) {
        cout<<"destination unreachable"<<endl;
        return;
    }

    reconstruct_path(end, start);
    return;
}



        
