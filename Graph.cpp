#include "Graph.h"

void swap(vector<Vertex *> &v, int a, int b) {
	Vertex *temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

void Graph::parseDataFromFile(string filename) {
		ifstream fin(filename, ios::in);

		if (!fin) {
			cout << "Cannot open file" << endl;
			exit(1);
		}

		string buffer;
		int startNode, endNode, edgeID;
		double weight;

		while (getline(fin, buffer)/*fin>>edgeID>>startNode>>endNode>>weight*/) {
            //cout<<"reading......"<<endl;
            //cout<<buffer<<endl;
		    if (sscanf(buffer.c_str(), "%d %d %d %lf", &edgeID, &startNode, &endNode, &weight) != 4){
                cout<<"Invalid input"<<endl;
                exit(1);
            }
            //cout<<edgeID<<" "<<startNode<<" "<<endNode<<" "<<weight<<endl;
            if (weight < 0) {
                cout<<"Invalid edge weight: cannot be negative"<<endl;
                exit(1);
            }

            int tabl_size = max(startNode, endNode) + 1;
            if (tabl_size > mappings.size()) {
                mappings.resize(tabl_size, -1);
            }

			Edge *edge = new Edge(edgeID, weight);

            Vertex *v1;
            Vertex *v2;

            if (!hasVertex(startNode)) {
                v1 = new Vertex(startNode);
                v.push_back(v1);
                mappings[startNode] = v.size() - 1;
            }
            else {
                v1 = findVertex(startNode);
            }
            //v1->neighbors.push_back(endNode);

            v1->edges.push_back(edge);

            if (!hasVertex(endNode)) {
                v2 = new Vertex(endNode);
                v.push_back(v2);
                mappings[endNode] = v.size() - 1;
            }
            else {
                v2 = findVertex(endNode);
            }
            //v2->neighbors.push_back(startNode);

            v2->edges.push_back(edge);

            edge->vertices.push_back(v1);
            //cout<<v1->nodeID<<" ";
            edge->vertices.push_back(v2);
            //cout<<v2->nodeID<<endl;
            e.push_back(edge);

            //cout<<(edge->vertices)[0]->nodeID<<endl<<(edge->vertices)[1]->nodeID<<endl;
        }

        cout<<"done parsing"<<endl;
        fin.close();
}

