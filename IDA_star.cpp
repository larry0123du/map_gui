#include "Astar.h"

using namespace std;

double Graph::search_b(Vertex *node, Vertex *end, double g_cost, double bound, bool *found) {
	//node->h_cost = heuristic(node, end);
	//node->f_cost = node->g_cost + node->h_cost;
    //cout<<"Exploring node "<<node->nodeID<<endl;

	double f_cost = g_cost + heuristic(node, end);

    //cout<<"G: "<<g_cost<<", H: "<<heuristic(node, end)<<", F: "<<f_cost<<", bound: "<<bound<<endl;
	//if (node->f_cost > bound) return node->f_cost;
	
	if (node->nodeID == end->nodeID) {
		//reconstruct_path(node);
		//exit(0);
        //cout<<"found it"<<endl;
		*found = true;
		return -1;
	}
    //node->discovered = true;
    if (f_cost > bound) {
        //cout<<"do not expand"<<endl<<endl;
        //erase_path(node);   
        return f_cost;
    }
    node->discovered = true;
	double min = numeric_limits<double>::max();
	//vector<Vertex *> neighbours = findNeighbours(node);
	for (vector<Edge *>::iterator it = (node->edges).begin(); it != (node->edges).end(); it++) {
        Vertex *neighbor;
        if (((*it)->vertices)[0]->nodeID == node->nodeID) {
            neighbor = ((*it)->vertices)[1];
        }
        else {
            neighbor = ((*it)->vertices)[0];
        }

        if (neighbor->discovered == true) continue;
		neighbor->parent = node;
        //cout<<"Node "<<(*it)->nodeID<<" Parent "<<node->nodeID<<endl;
		double t = search_b(neighbor, end, g_cost + (*it)->weight, bound, found);
        if (*found) {
            return -1;
        }
		if (min - t > 0.000001) {
			min = t;
		}
	}
    //erase_path(node);
    node->discovered = false;
	return min;
}

void Graph::ida_star(int start_v, int end_v) {
	
    bool found = false;
    Vertex *start = findVertex(start_v);
    Vertex *end = findVertex(end_v);
    if (start == NULL || end == NULL) {
        cout << "Cannot find vertex" << endl;
        exit(1);
    }
    start->g_cost = 0;

    double bound = heuristic(start, end);

    //start->parent = NULL;

    while (true) {
        //cout<<"trace: "<<endl;
        double t = search_b(start, end, 0, bound, &found);
        //cout<<"out of search_b"<<endl;
        if (t == numeric_limits<double>::max()) {
            cout << "Path not found" << endl;
            return;
        }
        /*if (abs(t + 1) < 0.0000001) {
          reconstruct_path(end);
          return;
          }*/
        if (found) {
            //cout<<"Found it"<<endl;
            reconstruct_path(end, start);
            return;
        }
        bound = t;
        //cout<<bound<<endl;
        //start->parent = NULL;
    }
}

/*int main() {
  Graph g;
  g.parseDataFromFile("mymap.cedge");
  g.readCoordinates("mynodes.cedge");
  g.ida_star(0,4);
  }*/
