#include "stdafx.h"
namespace DLLMapPath{
	class Node {
	public:
		Node* preNode;
		int distance;
		bool flag;
		int id;
		Node *neightbours[4];

		inline Node(){
			distance = 99999;
			id = -1;
			flag = false;
		}

		inline Node(int dist, int id, bool flag){
			this->distance = dist;
			this->id = id;
			this->flag = flag;
			for (int i = 0; i < 4; i++){
				neightbours[i] = new (Node);
			}
			preNode = new (Node);
		}

		inline void setDist(int distance){
			this->distance = distance;
		}

		inline void setPreNode(Node pre){
			*preNode = pre;
		}

		inline void setNB(Node *newNeightbours, int x){
			neightbours[x] = newNeightbours;
		}

		inline void setFlag(bool flag){
			this->flag = flag;
		}

		inline bool getFlag(){
			return flag;
		}

		inline int getDistance(){
			return distance;
		}

		inline int getID(){
			return id;
		}

		inline Node* getNB(int x){
			return neightbours[x];
		}

		inline Node* getPreNode(){
			return preNode;
		}
	};
	class DLLManager{
	public:
		inline DLLManager(){}

		inline int notVisited(Node *nodes, int lengh){
			int counter = 0;
			for (int i = 0; i < lengh; i++){
				if (!nodes[i].getFlag()){
					counter++;
				}
			}
			return counter;
		}
	};
	extern "C" {
		__declspec(dllexport) int* findPath(int from, int to, int* map, int mapw, int maph, int pathlength) {
			DLLManager *m;
			m = new(DLLManager);;
			int fieldWeight = mapw*maph;
			Node**nodes;
			nodes = new Node*[fieldWeight];
			for (int i = 0; i < fieldWeight; i++)
			{
				bool visit = false;
				if (map[i] > 0){
					visit = true;
				}
				nodes[i] = new Node(9999, i, visit);
			}
			Node *dummy = new Node(999999, -1, true);
			for (int i = 0; i < fieldWeight; i++)
			{
				int n = i - mapw;
				int o = i + 1;
				int s = i + mapw;
				int w = i - 1;
				if (i < mapw){
					nodes[i]->setNB(dummy, 0);
				}
				else{
					nodes[i]->setNB(nodes[n], 0);
				}
				if (i%mapw == (mapw - 1)){
					nodes[i]->setNB(dummy, 1);
				}
				else{
					nodes[i]->setNB(nodes[o], 1);
				}
				if (fieldWeight - mapw <= i){
					nodes[i]->setNB(dummy, 2);
				}
				else{
					nodes[i]->setNB(nodes[s], 2);
				}
				if (i%mapw == 0){
					nodes[i]->setNB(dummy, 3);
				}
				else{
					nodes[i]->setNB(nodes[w], 3);
				}
			}
			nodes[from]->setDist(0);

			Node *u = nodes[from];
			while (m->notVisited(*nodes, fieldWeight) != 0 && u->getID() != to){
				//Get Neightbours
				Node *tmpNB[] = { u->getNB(0), u->getNB(1), u->getNB(2), u->getNB(3) };
				//Set Distance to the Neighbours
				for (int i = 0; i < 4; i++){
					if (!tmpNB[i]->getFlag()){
						if (tmpNB[i]->getDistance() > u->getDistance() + 1){
							tmpNB[i]->setDist(u->getDistance() + 1);
							tmpNB[i]->setPreNode(*u);
						}
					}
				}
				u->setFlag(true);
				u = new (Node);
				u->setDist(9999999);
				for (int i = 0; i < fieldWeight; i++){
					if (u->getDistance()>nodes[i]->getDistance() && !nodes[i]->getFlag()){
						u = nodes[i];
					}
				}
			}
			int counter = 0;
			int* path = new int[pathlength];
			while (u->getID() != from){
				path[counter] = u->getID();
				u = u->getPreNode();
				counter++;
			}
			path[counter] = from;
			//Code Dij
			delete[] nodes;
			return path;
		}
		__declspec(dllexport) void freeArray(int* pointer) {
			delete[] pointer;
		}
	}
}
