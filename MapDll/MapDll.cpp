#include "stdafx.h"
#include <utility>
#include <iostream>


namespace DLLMapPath{

	class Node {
	public:
		Node* preNode;
		int distance;
		bool flag;
		int id;
		Node *neightbours = new Node[4];

		Node();

		Node(int _dist, int _id, bool _flag){
			distance = _dist;
			id = _id;
			flag = _flag;
		}

		void setDist(int dist){
			distance = dist;
		}

		void setPreNode(Node pre){
			*preNode = pre;
		}

		void setNB(Node* _neightbours){
			neightbours = _neightbours;
		}

		void setFlag(bool flaged){
			flag = flaged;
		}

		bool getFlag(){
			return flag;
		}

		int getDistance(){
			return distance;
		}

		int getID(){
			return id;
		}

		Node* getNB(){
			return neightbours;
		}
	};

	extern "C" {
		__declspec(dllexport) int* findPath(int from, int to, int* map, int mapw, int maph, int pathlength) {
			printf("DLL berechnet weg von %d zu %d\n", from, to);
			int* path = new int[pathlength];
			int fieldWeight = mapw*maph;
			Node* nodes = new Node[fieldWeight];
			//Code Dij

			for (size_t i = 0; i < fieldWeight; i++)
			{
				bool visit = false;
				if (map[i]>0){
					visit = true;
				}
				nodes[i] =*new Node(INFINITE,i,visit);
			}

			for (size_t i = 0; i < fieldWeight; i++)
			{
				int n = i - mapw;
				int o = i + 1;
				int s = i + mapw;
				int w = i - 1;
				if (i < mapw){
					n = 0;
				}
				if (i%mapw == 0){
					w = 0;
				}
				if (i%mapw==(mapw-1)){
					o = 0;
				}
				if (fieldWeight - mapw <= i){
					s = 0;
				}
				Node neightbours[4] = { nodes[n], nodes[o], nodes[s], nodes[w] };
				nodes[i].setNB(neightbours);
			}
			
			nodes[from].setDist(1);

			Node u = nodes[from];
			while (allVisited(nodes, fieldWeight) == 0){
				
				Node* tmpNB = new Node[4];
				tmpNB = u.getNB();

				for (int i = 0; i < 4; i++){
					
						tmpNB[i].setPreNode(u);
						tmpNB[i].setDist(
							u.getDistance()
							);
					}
				}			
			}
			//Code Dij
			printf("Weg berechnet! ;) \n\n");
			return path;
		}

		int allVisited(Node *nodes,int lengh){
			int counter = 0;
			for (int i = 0; i < lengh; i++){
				if (!nodes[i].getFlag){
					counter++;
				}
			}
			return counter;
		}
		__declspec(dllexport) void freeArray(int* pointer) {
			delete[] pointer;
		}
	}
}
