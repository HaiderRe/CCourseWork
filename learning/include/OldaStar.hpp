/* USAGE
#include "aStar.hpp"
Node start = { startY, startX }; 
Node end = { endY, endX}; 
std::vector<Node> path = Cordinate::aStar(start, end);
   // Example values in path =  [(0, 0), (0, 1), (0, 2), (1, 2), (2, 2), (3, 3)]
 USAGE */


#ifndef CORDINATE_H // Code from https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h
#define CORDINATE_H
#pragma once
#include <iostream> 
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <array>
#include "raymath.h"
#include <cfloat>
#include <memory>
#define X_MAX 64 
#define X_STEP 16 
#define Y_MAX 64
#define Y_STEP 16
using namespace std;
struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost; 
	float fCost;
};

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}


class Cordinate {

public:
	std::vector<std::vector<int>> collisionIDs;
	Cordinate(std::vector<std::vector<int>> aCollisionIDs) {
		collisionIDs = aCollisionIDs;
	}
	bool isValid(int x, int y, Node* dest = nullptr) {
    if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP)) {
		std::clog << "Out of bounds at " << x << ", " << y << std::endl;
        return false;
    }
    if (collisionIDs[y][x] != 0) {
        // Check if current x, y is not the destination before treating it as an obstacle.
        if (!dest || (x != dest->x || y != dest->y)) {
			std::clog << "Collision at " << x << ", " << y << std::endl;

            return false; // if it's not 0, it's an obstacle
        }
    }
    return true;
}

	 bool isDestination(int x, int y, Node dest) {
		if (x == dest.x && y == dest.y) {
			return true;
		}
		return false;
	}

	 double calculateH(int x, int y, Node dest) {
		double H = (sqrt((x - dest.x)*(x - dest.x)
			+ (y - dest.y)*(y - dest.y)));
		return H;
	}

	 vector<Node> makePath(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
		try {
			cout << "Found a path" << endl;
			int x = dest.x;
			int y = dest.y;
			stack<Node> path;
			vector<Node> usablePath;

			while (!(map[y][x].parentX == x && map[y][x].parentY == y)
    			   && map[y][x].x != -1 && map[y][x].y != -1) 
			{
				path.push(map[y][x]);
int tempX = map[y][x].parentX;
int tempY = map[y][x].parentY;
				x = tempX;
				y = tempY;
				
			}
path.push(map[y][x]);

			while (!path.empty()) {
				Node top = path.top();
				path.pop();
				//cout << top.x << " " << top.y << endl;
				usablePath.emplace_back(top);
			}
			return usablePath;
		}
		catch(const exception& e){
			std::cout << e.what() << std::endl;
		}
	}


	 vector<Node> aStar(Node player, Node dest) {
		vector<Node> empty;
		if (isValid(dest.x, dest.y, &dest) == false) {
			cout << "Destination is an obstacle" << endl;
			return empty;
			//Destination is invalid
		}
		if (isDestination(player.x, player.y, dest)) {
			cout << "You are the destination" << endl;
			return empty;
			//You clicked on yourself
		}
		bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

		//Initialize whole map
		//Node allMap[50][25];
		array<array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
		for (int x = 0; x < (X_MAX / X_STEP); x++) {
			for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
				allMap[y][x].fCost = FLT_MAX;
allMap[y][x].gCost = FLT_MAX;
allMap[y][x].hCost = FLT_MAX;
allMap[y][x].parentX = -1;
allMap[y][x].parentY = -1;
allMap[y][x].x = x;
allMap[y][x].y = y;

closedList[y][x] = false;
			}
		}

		//Initialize our starting list
		int x = player.x;
		int y = player.y;
		allMap[y][x].fCost = 0.0;
allMap[y][x].gCost = 0.0;
allMap[y][x].hCost = 0.0;
allMap[y][x].parentX = x;
allMap[y][x].parentY = y;

		vector<Node> openList;	
		openList.emplace_back(allMap[x][y]);
		bool destinationFound = false;

		while (!openList.empty()&&openList.size()<(X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
			Node node;
			do {
				//This do-while loop could be replaced with extracting the first
				//element from a set, but you'd have to make the openList a set.
				//To be completely honest, I don't remember the reason why I do
				//it with a vector, but for now it's still an option, although
				//not as good as a set performance wise.
				float temp = FLT_MAX;
				vector<Node>::iterator itNode;
				for (vector<Node>::iterator it = openList.begin();
					it != openList.end(); it = next(it)) {
					Node n = *it;
					if (n.fCost < temp) {
						temp = n.fCost;
						itNode = it;
					}
				}
				node = *itNode;
				openList.erase(itNode);
			} while (isValid(node.x, node.y) == false);

			x = node.x;
			y = node.y;
closedList[y][x] = true;

			//For each neighbour starting from North-West to South-East
			for (int newX = -1; newX <= 1; newX++) {
				for (int newY = -1; newY <= 1; newY++) {
					double gNew, hNew, fNew;
					if (isValid(x + newX, y + newY,&dest)) {
						if (isDestination(x + newX, y + newY, dest))
						{
							//Destination found - make path
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							destinationFound = true;
							return makePath(allMap, dest);
						}
else if (closedList[y + newY][x + newX] == false)
						{
							gNew = node.gCost + 1.0;
							hNew = calculateH(x + newX, y + newY, dest);
							fNew = gNew + hNew;
							// Check if this path is better than the one already present
							if (allMap[y + newY][x + newX].fCost == FLT_MAX ||
   								 allMap[y + newY][x + newX].fCost > fNew)
							{
								// Update the details of this neighbour node
								allMap[y + newY][x + newX].fCost = fNew;
allMap[y + newY][x + newX].gCost = gNew;
allMap[y + newY][x + newX].hCost = hNew;
allMap[y + newY][x + newX].parentX = x;
allMap[y + newY][x + newX].parentY = y;
								openList.emplace_back(allMap[y + newY][x + newX]);
							}
						}
					}
				}
			}
			}
			if (destinationFound == false) {
				cout << "Destination not found" << endl;
				return empty;
		}
	}
};
#endif