#include "graphNode.h"

graphNode::graphNode(int value)
{
	key = value;
}

int graphNode::getKey() 
{
	return key;
}

void graphNode::setKey(int value) 
{
	key = value;
}

bool graphNode::getVisited() 
{
	return visited;
}

void graphNode::setVisited(bool value) 
{
	visited = value;
}

void graphNode::addEdge(edge value) 
{
	edges.push_back(value);		// push_back
}

edge * graphNode::getEdge(unsigned int value) {
	if (value < edges.size())				// Wenn Kante existiert:
		return &edges[value];					// zurückgeben

	return nullptr;							// Ansonsten: nullptr zurückgeben
}

int graphNode::getNumberOfEdges() {
	return edges.size();
}

int graphNode::getComponent() {
	return component;
}

void graphNode::setComponent(int value) {
	component = value;
}