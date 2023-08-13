#include "AStar.hpp"
#include <iostream>

int main()
{
    pf::AStar astar;

    astar.loadMap("testingMaps/1.txt");
    astar.setDiagonalMovement(true);
    auto path = astar.findPath(pf::Vec2i(0, 0), pf::Vec2i(7, 10), pf::heuristic::manhattan, 10);

    for (const auto& coord : path) 
    {
        std::cout << coord.x << "," << coord.y << "\n";
    }

    system("pause");    
    return 0;
}