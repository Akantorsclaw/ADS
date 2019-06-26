#pragma once
#include "graphNode.h"

using namespace std;

class Graph {
private:
	int anzKnoten = 0;
	bool ger = false;
	bool gew = false;
	vector<graphNode*> nodes;
	graphNode * getNodeByKey(int key);
	void setAllUnvisited();
	bool checkVisited();
	void startDepthSearchRek(graphNode * Node);
	bool testChildComponent(graphNode * Node);

public:
	Graph();
	~Graph();
	bool init(const string& file);
	bool printAll();
	bool depthSearchRek(int startKey);
	bool breadthSearchIter(int startKey);
	double prim(int startKey);
	double kruskal();
	int getAnzKnoten();
};