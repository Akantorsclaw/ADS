#pragma once
#include <vector>

using namespace std;

struct edge 
{
	int Weight=0;
	int startNodeID=0;
	int endNodeID=0;
	//constructor
	edge(int startNode,int endNode,int weight)
	{
		startNodeID = startNode;
		endNodeID = endNode;
		Weight = weight;
	}
};

class graphNode {
private:
	int key = 0;
	vector<edge> edges;
	bool visited;
	int component;			// Nummer (Bezeichnung) des Knotens

public:
	//constructor
	graphNode(int value);

	//getter-setter
	int getKey();
	void setKey(int value);

	bool getVisited();
	void setVisited(bool value);

	void addEdge(edge value);
	edge * getEdge(unsigned int value);

	int getNumberOfEdges();

	int getComponent();
	void setComponent(int value);
};
