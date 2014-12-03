#include "stdafx.h"
#include "Node.h"
#include "DLLManager.h"

#include <stdio.h>
#include <conio.h>
namespace DLLMapPath{
	extern "C" {
		__declspec(dllexport) int* findPath(int from, int to, int* map, int mapw, int maph, int pathlength) {
			DLLManager m;
			int* path = new int[pathlength];
			int fieldWeight = mapw*maph;
			getch(); printf("1"); //-------------------------------------------------------------
			Node* nodes = new Node[fieldWeight];
			getch(); printf("3"); //-------------------------------------------------------------
			for (int i = 0; i < fieldWeight; i++)
			{
				bool visit = false;
				if (map[i] > 0){
					visit = true;
				}
				nodes[i] =*new Node(INFINITE,i,visit);
			}
			for (int i = 0; i < fieldWeight; i++)
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
			nodes[from].setDist(0);

			Node u = nodes[from];
			while (m.notVisited(nodes, fieldWeight) != 0 && u.getID()!=to){
				//Get Neightbours
				Node* tmpNB = new Node[4];
				tmpNB = u.getNB();

				//Set Distance to the Neighbours
				for (int i = 0; i < 4; i++){
					if (!tmpNB[i].getFlag()){
						if (tmpNB[i].getDistance() > u.getDistance() + 1){
							tmpNB[i].setDist(u.getDistance() + 1);
							tmpNB[i].setPreNode(u);
						}					
					}				
				}
				u.setFlag(true);
				u=m.getSmallDisNode(nodes,fieldWeight);
			}
			int counter = 0;
			while (u.getID() != from){
				path[counter] = u.getID();
				u = u.getPreNode();
				counter++;
			}
			//Code Dij
			delete[] nodes;
			return path;
		}
		__declspec(dllexport) void freeArray(int* pointer) {
			delete[] pointer;
		}
	}
}
