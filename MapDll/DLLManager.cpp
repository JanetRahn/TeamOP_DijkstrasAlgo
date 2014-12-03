#include "stdafx.h"
#include "DLLManager.h"
#include "Node.h"

DLLManager::DLLManager(){}

Node DLLManager::getSmallDisNode(Node *nodes, int lengh){
	Node smallest = nodes[0];
	for (int i = 1; i < lengh; i++){
		if (smallest.getDistance()>nodes[i].getDistance()){
			smallest = nodes[i];
		}
	}
	return smallest;
}

int DLLManager::notVisited(Node *nodes, int lengh){
	int counter = 0;
	for (int i = 0; i < lengh; i++){
		if (!nodes[i].getFlag()){
			counter++;
		}
	}
	return counter;
}