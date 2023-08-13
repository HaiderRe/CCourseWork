#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <algorithm>
#include "raylib.h"  
using NodeListIterator = std::list<Node>::iterator;
using namespace std;

class Node
{
public:
    
    int h;
    int g;
    int f;
    
    Vector2 position;

    
    NodeListIterator parent;  
    bool operator==(const Node& node);
};

bool Node::operator==(const Node& node)
{
    return (node.position.x == this->position.x &&
            node.position.y == this->position.y);
}

class AStar
{
private:
    
    int density;

    
    std::vector<std::vector<int>> grid;

    Vector2 start;
    Vector2 end;
    std::list<Node> nodeList;  
    int move[8][2] = {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }
    };  
    std::list<Node> nodeList;  
public:
    AStar(Vector2 start, Vector2 end, int density, std::vector<std::vector<int>>& inputGrid);

    void printGrid();
    std::vector<Vector2> BeginPathSearch();

private:
    int costH(Vector2 pos);
    int costG(Node& a, Vector2& b);
    bool isOnList(Node node, vector<Node> list);
    void tracePath(NodeListIterator nodeIt, std::vector<Vector2>& path);
    void costF(Node new_node, Node curr_node);
    bool updateNodeInList(Node& successor, std::vector<NodeListIterator>& list, Node& currentNode);
    NodeListIterator findNodeInList(const Node& node, const std::list<Node>& nodeList);
};

AStar::AStar(Vector2 start, Vector2 end, int density, std::vector<std::vector<int>>& inputGrid)
    : start(start), end(end), density(density), grid(inputGrid)
{}

void AStar::printGrid()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int AStar::costG(Node& a, Vector2& b)
{
    if (fabs(a.position.x - b.x) == 1 && fabs(a.position.y - b.y) == 1)
        return 14;
    else
        return 10;
}


int AStar::costH(Vector2 pos)
{
    return abs(pos.x - end.x) + abs(pos.y - end.y);
}

bool AStar::isOnList(Node node, vector<Node> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (node == list[i])
            return true;
    }
    return false;
}

void AStar::tracePath(NodeListIterator nodeIt, std::vector<Vector2>& path)
{
    while (nodeIt != nodeList.end())
    {
        path.push_back(nodeIt->position);
        nodeIt = nodeIt->parent;
    }
    std::reverse(path.begin(), path.end());
}


void AStar::costF(Node new_node, Node curr_node)
{
    new_node.h = costH(new_node.position);
    new_node.g = costG(new_node, curr_node.position);
    new_node.f = new_node.h + new_node.g;
}
NodeListIterator AStar::findNodeInList(const Node& node, const std::list<Node>& nodeList) {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
        if (it->position.x == node.position.x && it->position.y == node.position.y) {
            return it;
        }
    }
    return nodeList.end(); // Return end() if not found.
}

bool AStar::updateNodeInList(Node& successor, std::vector<NodeListIterator>& list, Node& currentNode)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if ((*it)->position == successor.position)
        {
            if ((*it)->g > successor.g)
            {
                (*it)->g = successor.g;
                (*it)->f = (*it)->g + (*it)->h;
                (*it)->parent = findNodeInList(currentNode, nodeList);

            }
            return true;
        }
    }
    return false;
}

std::vector<Vector2> AStar::BeginPathSearch()
{
    vector<Node> openList;
    vector<Node> closedList;

    std::vector<Vector2> path;

    Node startNode;
    startNode.position = start;
    startNode.parent = nullptr;
    startNode.h = costH(start);
    startNode.g = 0;
    startNode.f = startNode.g + startNode.h;

    openList.push_back(startNode);

    while (!openList.empty())
    {
        // Find the node with the least f in the open list
        Node currentNode = openList[0];
        int currentIndex = 0;

        for (int i = 1; i < openList.size(); i++)
        {
            if (openList[i].f < currentNode.f)
            {
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        // Pop the current node from the open list
        openList.erase(openList.begin() + currentIndex);

        // Check for goal node
        if (currentNode.position.x == end.x && currentNode.position.y == end.y)
        {
            tracePath(&currentNode, path);
            return path;
        }

        // Generate the node's successors
        for (int i = 0; i < 8; i++)
        {
            Vector2 newPos;
            newPos.x = currentNode.position.x + move[i][0];
            newPos.y = currentNode.position.y + move[i][1];

            // If position is outside the grid or is an obstacle, skip this successor
            if (newPos.x < 0 || newPos.x >= grid.size() || newPos.y < 0 || newPos.y >= grid[0].size() || grid[newPos.y][newPos.x] != 0)
                continue;

            Node successor;
            successor.position = newPos;
            successor.g = currentNode.g + costG(currentNode, newPos);
            successor.h = costH(newPos);
            successor.f = successor.g + successor.h;

            // Check if the node is already in the open list or closed list
            // If it is but the new path is better, update it
            // Otherwise, add the node to the open list
            if (updateNodeInList(successor, openList, currentNode) || updateNodeInList(successor, closedList, currentNode))
                continue;

            openList.push_back(successor);
        }

        closedList.push_back(currentNode);
    }

    // If no path is found, return an empty path
    return path;
}
