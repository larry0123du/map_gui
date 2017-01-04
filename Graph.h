#ifndef GRAPH_H
#define GRAPH_H 1
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
#include <queue>

using namespace std;

class Edge;

class Vertex {

public:
	int nodeID;
	vector<Edge *> edges;
	Vertex *parent;

    //vector<int> neighbors;

	double distance;

	double g_cost;
	double h_cost;
	double f_cost;

	double x_coor;
	double y_coor;

	bool discovered;
	bool tbd;
	/*for gl*/
	bool draw;

	//friend class Edge;
	//friend class Graph;
	Vertex(int id) : nodeID(id), parent(NULL), distance(numeric_limits<double>::max()) {
		g_cost = numeric_limits<double>::max();
		h_cost = numeric_limits<double>::max();
		f_cost = numeric_limits<double>::max();
		discovered = false;
		tbd = false;
		draw = false;
	};

};

class Edge {
public:
	int edgeID;
	double weight;
	vector<Vertex *> vertices;

	//friend class Vertex;
	//friend class Graph;
	Edge(int id, double w) : edgeID(id), weight(w) {};
};

class Graph {
public:
	vector<Vertex *> v;
	vector<Edge *> e;

    vector<int> mappings;
	//friend class Vertex;
	//friend class Edge;

	Graph() {};

	bool hasVertex(int nodeID) {
		/*for (vector<Vertex *>::iterator it = v.begin(); it != v.end(); it++) {
			if ((*it)->nodeID == nodeID)
				return true;
		}*/
        if (nodeID >= mappings.size()) {
            return false;
        }
        if (mappings[nodeID] == -1) {
		    return false;
        }
        return true;
	}

	Vertex *findVertex(int nodeID) {
		/*for (vector<Vertex *>::iterator it = v.begin(); it != v.end(); it++) {
			if ((*it)->nodeID == nodeID)
				return *it;
		}*/
        if (!hasVertex(nodeID))
		    return NULL;
        return v[mappings[nodeID]];
	}

	Vertex *antiVertex(Vertex *vert, Edge *edge) {
		if ((edge->vertices)[0]->nodeID == vert->nodeID) {
			return (edge->vertices)[1];
		}
		return (edge->vertices)[0];
            void updateIncident(Vertex *vert, int end);
	}

	//Edge *search_edge(Vertex *a, Vertex *b);

    //void updateIncident(Vertex *vert, int end);
	void parseDataFromFile(string filename);

	void readCoordinates(string filename);

	void dijkstra(int start_v, int end_v);

    vector<Vertex *> findNeighbours(Vertex *vert);

	void a_star(int start_v, int end_v);

    void ida_star(int start_v, int end_v);

	double search_b(Vertex *node, Vertex *end, double g_cost, double bound, bool *found);

	void printGraph() {
		for (unsigned int i = 0; i < v.size(); i++) {
			cout << "Vertex: " << v[i]->nodeID << endl;
			for (vector<Edge *>::iterator it = (v[i]->edges).begin(); it != (v[i]->edges).end(); it++) {
				cout << "Thru edge " << (*it)->edgeID << " to vertex ";
				if (((*it)->vertices)[0]->nodeID == v[i]->nodeID) {
					cout << ((*it)->vertices)[1]->nodeID;
				}
				else {
					cout << ((*it)->vertices)[0]->nodeID;
				}
				cout << endl;
			}
			cout << endl;
		}
	};

	void printEdges() {
		for (vector<Edge *>::iterator it = e.begin(); it != e.end(); it++) {
			cout << "connecting " << ((*it)->vertices)[0]->nodeID << " " << ((*it)->vertices)[1]->nodeID << endl;
			cout << "distance: " << (*it)->weight << endl;
		}
	};

	void reconstruct_path(Vertex *v, Vertex *start);

	~Graph() {
        for (vector<Vertex *>::iterator it = v.begin(); it != v.end(); it++) {
            delete *it;
        }
        for (vector<Edge *>::iterator it = e.begin(); it != e.end(); it++) {
            delete *it;
        }

    };

};

void swap(vector<Vertex *> &v, int a, int b) ;

#endif
