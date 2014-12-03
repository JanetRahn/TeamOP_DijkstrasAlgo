#include "stdafx.h"
#include "Node.h"

#include <conio.h>
#include <stdio.h>
Node::Node(){
	getch(); printf("sdsagfgsfsadf"); //-------------------------------------------------------------
}

Node::Node(int _dist, int _id, bool _flag){
	distance = _dist;
	id = _id;
	flag = _flag;
}

void Node::setDist(int dist){
	distance = dist;
}

void Node::setPreNode(Node pre){
	*preNode = pre;
}

void Node::setNB(Node* _neightbours){
	neightbours = _neightbours;
}

void Node::setFlag(bool flaged){
	flag = flaged;
}

bool Node::getFlag(){
	return flag;
}

int Node::getDistance(){
	return distance;
}

int Node::getID(){
	return id;
}

Node* Node::getNB(){
	return neightbours;
}

Node Node::getPreNode(){
	return *preNode;
}
