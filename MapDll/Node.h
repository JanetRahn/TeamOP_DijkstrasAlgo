#pragma once
class Node {
public:
	Node* preNode;
	int distance;
	bool flag;
	int id;
	Node *neightbours = new Node[4];

	Node();

	Node(int _dist, int _id, bool _flag);

	void setDist(int dist);

	void setPreNode(Node pre);

	void setNB(Node* _neightbours);

	void setFlag(bool flaged);

	bool getFlag();

	int getDistance();

	int getID();

	Node* getNB();

	Node getPreNode();
};

