#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int m) {
	size = m;
	//*****************************
	// implement constructor here *
	//*****************************
	hashTable = new vector<int>(size);	// neue Tabelle auf dem heap
	for (int i = 0; i < size; i++)
	{
		hashTable->at(i) = -1;
	}
	collisionCount = 0;
	elements = 0;
}

HashTable::~HashTable()
{
	//****************************
	// implement destructor here *
	//****************************
	delete hashTable;
}

int HashTable::hashValue(int item) {
	

	//******************************************
	// implement calculation of hashindex here *
	//******************************************
	
	return (item % size);
}

void HashTable::insert(int item) {
	
	//******************************************
	// implement insertion of new element here *
	//******************************************

	int index = hashValue(item);
	int i = 0;
	while(hashTable->at(index) != -1)
	{
		collisionCount++;
		i++;
		index = hashValue(item + (i*i));
		
	}

	hashTable->at(index) = item;
	elements++;
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
