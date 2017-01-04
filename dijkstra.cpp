#include "Graph.h"
using namespace std;

int compare_d(Vertex *a, Vertex *b) {
	if ((a->distance) - (b->distance) >= 0.0000001) {
		//a greater than b
		return 1;
	}
	else if ((a->distance) - (b->distance) < 0.0000001 && (a->distance) - (b->distance) > -0.0000001) {
		return 0;
	}
	else {
		return -1;
	}
}

void decrease_key(int index, vector<Vertex *> &v, vector<int> &mappings) {
	//vert->distance = distance;
	int parent = index;
	while ((parent = (parent - 1) / 2) >= 0) {
		if (compare_d(v[index], v[parent]) == -1) {
            mappings[v[index]->nodeID] = parent;
            mappings[v[parent]->nodeID] = index;
			swap(index, parent);
		}
		else {
			break;
		}
	}
}

/*int indexOf(Vertex *vert, vector<Vertex *> &v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i]->nodeID == vert->nodeID) {
			return i;
		}
	}
	return -1;
}*/

void Graph::updateIncident(Vertex *vert, int end) {
	double dist;
	Vertex *incident;
	for (vector<Edge *>::iterator it = (vert->edges).begin(); it != (vert->edges).end(); it++) {
		if (((*it)->vertices)[0]->nodeID == vert->nodeID) {
			incident = ((*it)->vertices)[1];
		}
		else {
			incident = ((*it)->vertices)[0];
		}

		if (mappings[incident->nodeID] > end) {
            //cout<<"out of bound"<<endl;
			continue;
        }

		if ((dist = ((*it)->weight + vert->distance)) < incident->distance) {
			incident->distance = dist;
			int index = mappings[incident->nodeID];
			decrease_key(index, v, mappings);
			incident->parent = vert;
		}
	}
}

void downheap(vector<Vertex *> &v, vector<int> &mappings, int start, int end) {
    int root = start;
    while (root * 2 + 1 <= end) {
        int leftchild = root * 2 + 1;
        int swap_node = root;

        if (compare_d(v[swap_node], v[leftchild]) >= 0) {
            swap_node = leftchild;
        }
        if (leftchild + 1 <= end && compare_d(v[swap_node], v[leftchild + 1]) >= 0) {
            swap_node = leftchild + 1;
        }
        if (swap_node == root)return;
        else {
            mappings[v[swap_node]->nodeID] = root;
            //cout<<"new mapping: "<<v[swap_node]->nodeID<<"->"<<root<<endl;
            mappings[v[root]->nodeID] = swap_node;
            //cout<<"new mapping: "<<v[root]->nodeID<<"->"<<swap_node<<endl;

            swap(v, swap_node, root);
            root = swap_node;
        }
    }
}

void heapify(vector<Vertex *> &v, vector<int> &mappings, int end) {
	int start = (end - 1) / 2;

	while (start >= 0) {
        //cout<<"downheaping"<<endl;

		downheap(v, mappings, start, end);
		start--;
	}
}

void Graph::dijkstra(int start_v, int end_v) {
    //cout<<"in dijkstra"<<endl;

	/*if (start_v >= v.size() || end_v >= v.size()) {
		cout << "Cannot find vertex" << endl;
		exit(1);
	}*/
    Vertex *start = findVertex(start_v);
    if (start == NULL) {
        cout<<"Cannot find vertex"<<endl;
        exit(1);
    }
    //cout<<"Found vertex #"<<start->nodeID<<endl;

    start->distance = 0;
    
    
    int end = v.size() - 1;
    heapify(v, mappings, end);
    //cout<<"done heap"<<endl;



    while (end > 0) {
        /*cout<<end<<endl;
        cout<<"Heap: "<<endl;

        for (int i = 0; i <= end; i++) {
          cout<<v[i]->nodeID;
          if (v[i]->distance < numeric_limits<double>::max() - 1)
          printf(" %.6lf\n", v[i]->distance);
          else
          cout<<" infinity"<<endl;
          }
          cout<<endl;
          cout<<mappings[3]<<endl<<endl;*/

        updateIncident(v[0], end);
        mappings[v[end]->nodeID] = 0;
        mappings[v[0]->nodeID] = end;
        swap(v, 0, end);
        end--;
        //downheap(v, 0, end);
        heapify(v, mappings, end);

        /*cout<<"Heap: "<<endl;

        for (int i = 0; i <= end; i++) {
          cout<<v[i]->nodeID;
          if (v[i]->distance < numeric_limits<double>::max() - 1)
          printf(" %.6lf\n", v[i]->distance);
          else
          cout<<" infinity"<<endl;
          }
          cout<<endl;*/


    }

    cout<<"complete"<<endl;

    Vertex *dest = findVertex(end_v);
    if (dest == NULL) {
        cout<<"Cannot find vertex"<<endl;
        exit(1);
    }

    if (dest->distance >= numeric_limits<double>::max() - 1) {
        cout<<"destination is unreachable"<<endl;
        exit(0);
    }

    //cout<<"parent is "<<dest->parent->nodeID<<endl;
    //cout<<dest->distance<<endl;
    printf("%.6lf\n", dest->distance);

    vector<Edge *> path;
    while (dest->parent != NULL) {
        //cout<<"Im here"<<endl;

        for (vector<Edge *>::iterator it = (dest->parent->edges).begin();
                it != (dest->parent->edges).end(); it++) {
            if (dest->nodeID == antiVertex(dest->parent, *it)->nodeID) {
                path.push_back(*it);
            }
        }
        dest = dest->parent;
    }

    for (vector<Edge *>::reverse_iterator it = path.rbegin(); it != path.rend(); it++)  {
        cout<<(*it)->edgeID<<endl;
    }
}

/*int main() {
  Graph g;
  g.parseDataFromFile("mytest2.cedge");
  g.dijkstra(0,6);

  return 0;
  }*/
