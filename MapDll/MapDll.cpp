#include "stdafx.h"
#include <utility>
#include <iostream>


namespace DLLMapPath{
	extern "C" {
		__declspec(dllexport) int* findPath(int from, int to, int* map, int mapw, int maph, int pathlength) {
			printf("DLL berechnet weg von %d zu %d\n", from, to);
			int* path = new int[pathlength];
			//test
			for (int i = 0; i < mapw*maph; i++){
				if (map[i]>0){
					map[i] = 9999999;
				}
				else{
					if (i == from || i == to){
						map[i] = 0;
					}
					else{
						map[i] = 1;
					}
				}
			}

			//endTest
			printf("Weg berechnet! ;) \n\n");
			return path;
		}

		__declspec(dllexport) void freeArray(int* pointer) {
			delete[] pointer;
		}
	}
}
