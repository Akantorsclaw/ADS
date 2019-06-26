#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <queue>
#include <functional>
#include <cassert>
graphNode * Graph::getNodeByKey(int key)
{

	for (const auto& node : nodes)
		if (node->getKey() == key)
			return node;

	return nullptr;
}

void Graph::setAllUnvisited()
{
	for (auto& node : nodes)
		node->setVisited(false);

}

bool Graph::checkVisited() 
{
	for (const auto& node : nodes)
		if (!node->getVisited())
			return false;
		


	
	return true;
}

void Graph::startDepthSearchRek(graphNode * node) 
{
	//does node exist
	assert(node);
	//node visited
	node->setVisited(true);
	int numberOfEdges = node->getNumberOfEdges();

	for (int i = 0; i < numberOfEdges; i++)
	{

		int nextNodeID = node->getEdge(i)->endNodeID;
		graphNode* nextNode = getNodeByKey(nextNodeID);
		assert(nextNode);
		if (!nextNode->getVisited())
		{
			startDepthSearchRek(nextNode);
		}
	}
}

bool Graph::testChildComponent(graphNode * Node) 
{
	for (const auto& node : nodes)
		if (Node->getComponent() != node->getComponent())
			return false;

	return true;
}

Graph::Graph() 
{
	
}

Graph::~Graph() 
{
	//delete all graphNodes in nodes
	for (int i = 0; i < nodes.size(); ++i)
		delete nodes.at(i);
	nodes.clear();
}

bool Graph::init(const std::string& file) 
{
	//make a new file
	std::ifstream f;
	f.open(file, std::ios_base::in);	//string into new file

	//if cant open f
	if (!f)
	{
		std::cout << "Cannot open file!" << std::endl;
		return false;
	}

	else
	{
		std::string line;
		std::getline(f, line);
		std::istringstream iss(line);

		iss >> anzKnoten; //first line

		ger = false; //ungerichtet
		gew = true;	//gewichtet

		//empty vec
		nodes.clear();

		//insert all nodes
		for (int i = 0; i < anzKnoten; i++)
		{
			nodes.push_back(new graphNode(i));
		}

		//all edges
		while (std::getline(f,line))
		{
			std::istringstream iss(line);
			int startNode, endNode, weight;

			iss >> startNode;
			iss >> endNode;
			iss >> weight;

			//check if Nodes exist
			assert(startNode >= 0 && startNode < nodes.size());
			assert(endNode >= 0 && endNode < nodes.size());


			nodes.at(startNode)->addEdge({ startNode,endNode,weight });

			//if ger == false
			if (!ger)
			{
				nodes.at(endNode)->addEdge({ endNode,startNode,weight });
			}

		}
		return true;

	}

	return false;
}

bool Graph::printAll() 
{
	bool done=false;
	for (int i = 0; i < nodes.size(); i++)
	{
		std::cout << i;
		graphNode* ptr = nodes.at(i);
		int numberOfEdges = ptr->getNumberOfEdges();
		for (int j = 0; j < numberOfEdges; j++)
		{
			edge* Edge = ptr->getEdge(j);
			std::cout << " -> " << Edge->endNodeID << " [" << Edge->Weight << "]";
		}
		std::cout << std::endl;
		done = true;
	}

	return done;
}

bool Graph::depthSearchRek(int startKey) 
{
	//all unvisited
	setAllUnvisited();
	//start search
	startDepthSearchRek(getNodeByKey(startKey));

	return checkVisited();
}

bool Graph::breadthSearchIter(int startKey)
{
	setAllUnvisited();
	//use queue
	std::queue<graphNode*> queue;
	graphNode* startNode = getNodeByKey(startKey);
	assert(startNode);

	//first visit
	startNode->setVisited(true);
	queue.push(startNode);

	while (!queue.empty())
	{
		//first queue place
		graphNode* node = queue.front();
		queue.pop();

		int numberOfEdges = node->getNumberOfEdges();
		for (int i = 0; i < numberOfEdges; i++)
		{
			int nextNodeID = node->getEdge(i)->endNodeID;
			graphNode* nextNode = getNodeByKey(nextNodeID);
			assert(nextNode);

			if (!nextNode->getVisited())
			{
				nextNode->setVisited(true);
				queue.push(nextNode);
			}
		}
	}
	return checkVisited();
}

double Graph::prim(int startKey) 
 {
	//-------------------------------------------------------------------------------------------------------------------//
	//EXTRA FUNCTIONS//
	//[] is Capture list - ()is Function Argument provider - {} is lambda Implementation//
	auto compareFunc = [](const edge* a, const edge* b) {return a->Weight > b->Weight; };
	//sort by weight smallest weight edge in front
	std::priority_queue<edge*, vector<edge*>, decltype(compareFunc) > unvisitedEdgesQueue(compareFunc);
	//& cause no copy wanted we want to change smth inside the node
	auto visitFunc = [&](graphNode* node)
	{
		
			node->setVisited(true);
			const int numberOfEdges = node->getNumberOfEdges();
			for (int i = 0; i < numberOfEdges; ++i)
			{
				//push all edges starting from Node where the endNode is not visited
				if (!nodes.at(node->getEdge(i)->endNodeID)->getVisited())
					unvisitedEdgesQueue.push(node->getEdge(i));
			}
		
	};

	//prim
	setAllUnvisited();
	graphNode* startNode = getNodeByKey(startKey);
	assert(startNode);

	//first entry for prio_queue
	visitFunc(startNode);
	 
	std::vector<edge*> mstEdges;

	while (!unvisitedEdgesQueue.empty())
	{
		edge* Edge = unvisitedEdgesQueue.top();
		unvisitedEdgesQueue.pop();

		graphNode* startNode = nodes.at(Edge->startNodeID);
		graphNode* endNode = nodes.at(Edge->endNodeID);

		if (startNode->getVisited() && endNode->getVisited())
		{
			continue;
		}

		mstEdges.push_back(Edge);
		if (!startNode->getVisited())
			visitFunc(startNode);
		if (!endNode->getVisited())
			visitFunc(endNode);
	}

	double mstSum = 0;
	
	for (auto mstEdge : mstEdges)
		mstSum += mstEdge->Weight;
	/*for (auto edgePrint : mstEdges)
		std::cout << edgePrint->startNodeID << " -> " << edgePrint->endNodeID << std::endl;*/

	return mstSum;
}

double Graph::kruskal() 
{
	//auto cmp = [](edge* left, edge* right) {return left->Weight < right->Weight; };
	//std::priority_queue<edge*,std::vector<edge*>,decltype(cmp) > pq(cmp);

	std::vector<edge*> edgeList;
	std::vector<edge*> mstEdges;

	for (int i = 0; i < nodes.size(); i++)
		nodes.at(i)->setComponent(i);			//all nodes are seperated graphs

	for (auto& node : nodes)	//get all edges into the prio queue
	{
		int numberOfEdges = node->getNumberOfEdges();
		for (int i = 0; i < numberOfEdges; i++)
			edgeList.push_back(node->getEdge(i));
	}

	//sort vector
	std::sort(edgeList.begin(), edgeList.end(), [](edge* a, edge* b) {return a->Weight < b->Weight; });

	for(auto e : edgeList)
	{
		//edge* e = pq.top();
		//pq.pop();

		int start = nodes.at(e->startNodeID)->getComponent();
		int end = nodes.at(e->endNodeID)->getComponent();

		if (start != end)
		{
			mstEdges.push_back(e);

			for (auto node:nodes)
				if (node->getComponent() == end)
					node->setComponent(start);
			
		}

		if (mstEdges.size() >= nodes.size() - 1)
			break;
	}

	double mstSum=0.0;
	for (auto& mstEdge : mstEdges)
		mstSum += mstEdge->Weight;

	return mstSum;


	//for (int i = 0; i < nodes.size(); ++i) // zu Beginn ist jeder Knoten ein eigener Baum
	//	nodes.at(i)->setComponent(i);

	//std::vector<const edge*> edges;
	//for (const auto& node : nodes)
	//{
	//	const int numberOfEdges = node->getNumberOfEdges();
	//	for (int i = 0; i < numberOfEdges; ++i)
	//		edges.push_back(node->getEdge(i));
	//}

	//std::sort(edges.begin(), edges.end(), [](const edge* a, const edge* b) {
	//	return a->Weight < b->Weight;
	//});

	//std::vector<const edge*> mstEdges;
	//for (auto& edge : edges)
	//{
	//	const int startNodeIDComponent = nodes.at(edge->startNodeID)->getComponent();
	//	const int endNodeIDComponent = nodes.at(edge->endNodeID)->getComponent();
	//	// Wenn Knoten zu unterschiedlichen Bäumen gehört,
	//	// können diese mit der Kante ohne Zykel verbunden werde
	//	if (startNodeIDComponent != endNodeIDComponent)
	//	{
	//		mstEdges.push_back(edge);
	//		for (auto& node : nodes)
	//			if (node->getComponent() == endNodeIDComponent) // BaumId angleichen
	//				node->setComponent(startNodeIDComponent);
	//	}

	//	if (mstEdges.size() >= nodes.size() - 1)
	//		break; // Stoppt bei Kanten = Knoten -1
	//}

	//double mstSum = 0;
	//for (const auto& mstEdge : mstEdges)
	//	mstSum += mstEdge->Weight;

	//return mstSum;
}

int Graph::getAnzKnoten() 
{
	return anzKnoten;
}