#include "Astar.h"
using namespace std;
bool compare_a(Vertex *a, Vertex *b) {
	if (a->f_cost - b->f_cost > 0.0000001) {
		return true;
	}
	else if (fabs(a->f_cost - b->f_cost) < 0.0000001) {
		if (a->h_cost - b->h_cost > 0.0000001) {
			return true;
		}
	}
	return false;
}

void Graph::readCoordinates(string filename) {
	ifstream fin(filename, ios::in);

	if (!fin) {
		cout << "Cannot open file" << endl;
		exit(1);
	}

	string buffer;
	double x, y;
	int nodeID;

	while (/*getline(fin, buffer)*/fin>>nodeID>>x>>y) {
		//sscanf(buffer.c_str(), "%d %lf %lf", &nodeID, &x, &y);
		//cout<<edgeID<<" "<<startNode<<" "<<endNode<<" "<<weight<<endl;

		Vertex *vert = findVertex(nodeID);
        if (vert == NULL) {

            if (nodeID >= mappings.size()) {
                mappings.resize(nodeID + 1, -1);
            }
            mappings[nodeID] = v.size();

            vert = new Vertex(nodeID);
		    vert->x_coor = x;
		    vert->y_coor = y;
            v.push_back(vert);
        }
        else {
            vert->x_coor = x;
            vert->y_coor = y;
        }
	}

	fin.close();
}

/*Edge *Graph::search_edge(Vertex *a, Vertex *b) {
	for (vector<Edge *>::iterator it = (a->edges).begin(); it != (a->edges).end(); it++) {
		if (b->nodeID == antiVertex(a, (*it))->nodeID) {
			return (*it);
		}
	}
	return NULL;
}*/

double heuristic(Vertex *a, Vertex* b) {
	return sqrt((a->x_coor - b->x_coor)*(a->x_coor - b->x_coor)
		+ (a->y_coor - b->y_coor)*(a->y_coor - b->y_coor));
}

void upheap(vector<Vertex *> &v, int index) {
	int start = index;
	while (start > 0 && compare_a(v[start], v[(start - 1) / 2]) == false) {
		Vertex *temp = v[(start - 1) / 2];
		v[(start - 1) / 2] = v[start];
		v[start] = temp;
		start = (start - 1) / 2;
	}
}

void down(vector<Vertex *> &v) {
	int start = 0;
	int to_swap = start;
	while ((start * 2 + 1) < v.size()) {
		if (compare_a(v[start], v[start * 2 + 1])) {
			to_swap = start * 2 + 1;
		}
		if ((start * 2 + 2) < v.size() && compare_a(v[to_swap], v[start * 2 + 2])) {
			to_swap = start * 2 + 2;
		}
		/*Vertex *temp = v[start];
		v[start] = v[swap];
		v[swap] = temp;
*/
        if (!(start == to_swap))
            swap(v, start, to_swap);
        else
            return;
        start = to_swap;
	}
}

void update(vector<Vertex *> &v, Vertex *vt) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->nodeID == vt->nodeID) {
			upheap(v, i);
		}
	}
}

void Graph::reconstruct_path(Vertex *v, Vertex *start) {
	vector<Edge *> path;
	Vertex *p = v;
	double length = 0;
	while (p->nodeID != start->nodeID) {
        //cout<<p->nodeID<<endl;
		//path.push_back(p->parent);
		for (vector<Edge *>::iterator it = (p->edges).begin(); it != (p->edges).end(); it++) {
			if (p->parent->nodeID == antiVertex(p, (*it))->nodeID) {
				path.push_back((*it));
				length += (*it)->weight;
			}
		}
		p = p->parent;
	}
	//cout << length << endl;
    printf("%.6lf\n", length);
	for (vector<Edge *>::reverse_iterator it = path.rbegin(); it != path.rend(); it++) {
		cout << (*it)->edgeID << endl;
	}
}


vector<Vertex *> Graph::findNeighbours(Vertex *vert) {
    vector<Vertex *> neighbours;
    for (vector<Edge *>::iterator it = (vert->edges).begin(); it != (vert->edges).end();
            it++) {
        Vertex *a = antiVertex(vert, (*it));
            a->distance = (*it)->weight;
            neighbours.push_back(a);
    }
    return neighbours;
}

void Graph::a_star(int start_v, int end_v) {
    Vertex *start = findVertex(start_v);

    Vertex *end = findVertex(end_v);
    if (start == NULL || end == NULL) {
        cout << "Cannot find vertex" << endl;
        exit(1);
    }
    start->g_cost = 0;
    start->h_cost = heuristic(start, end);
    start->f_cost = start->g_cost + start->h_cost;

    //priority_queue<Vertex *, vector<Vertex *>, compare_a> open;
    vector<Vertex *> open;
    //vector<Vertex *> closed;
    vector<Vertex *> neighbours;
    open.push_back(start);

    while (!open.empty()) {
        Vertex *current = open[0];
        if (current->nodeID == end->nodeID) {
            reconstruct_path(current, start);
            return;
        }
        /*for (vector<Edge *>::iterator it = (current->edges).begin(); it != (current->edges).end();
          it++) {
          Vertex *a = antiVertex(current, (*it));
          a->distance = (*it)->weight;
          neighbours.push_back(a);
          }
          */
        neighbours = findNeighbours(current);
        open[0]->discovered = true;
        open[0] = open.back();
        open.pop_back();
        down(open);

        //closed.push_back(current);
        for (vector<Vertex *>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
            if ((*it)->discovered) {
                continue;
            }
            double temp = current->g_cost + (*it)->distance;
            if (!(*it)->tbd) {
                open.push_back((*it));
                (*it)->tbd = true;
                upheap(open, open.size() - 1);
            }
            else if (temp >= (*it)->g_cost) {
                continue;
            }
            (*it)->parent = current;
            (*it)->g_cost = temp;
            (*it)->h_cost = heuristic((*it), end);
            (*it)->f_cost = (*it)->g_cost + (*it)->h_cost;
            update(open, (*it));
        }
        neighbours.clear();
    }
    cout << "Cannot find a path" << endl;
}

/*int main() {
  Graph g;
  g.parseDataFromFile("mytest2.cedge");
  g.readCoordinates("mytestnode2.cedge");
  g.a_star(4, 6);
  }*/
