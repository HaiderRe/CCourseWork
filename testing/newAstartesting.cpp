#include <iostream>
#include <vector>
#include "raylib.h"
#include "newAstar.hpp"

int main()
{
    // Just as an example:
    std::vector<std::vector<int>> grid(64, std::vector<int>(64, 0)); // Assuming 0 is walkable, and other values are not.
    grid[0][2] = 1;
    grid[1][2] = 1;
    grid[2][2] = 1;
    grid[3][2] = 1;
    grid[4][2] = 1;
    grid[5][2] = 1;
    grid[0][1] = 1;
    Vector2 start = { 0, 0 };
    Vector2 end = { 4, 4 };

    AStar pathfinder(start, end, 1, grid); // Here 2 is just an example density value.
    std::vector<Vector2> path = pathfinder.BeginPathSearch();

    // You can now use the path.
    for (auto& point : path)
    {
        cout << "(" << point.x << "," << point.y << ")" << endl;
    }
    system("pause");
    return 0;
}