#include <iostream>
#include <vector>
#include <random>
#include <ics46/factory/DynamicFactory.hpp>
#include "NovaGenerator.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Direction.hpp"
#include "MazeException.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, NovaGenerator, "Nova's Generator (Required)");


NovaGenerator:: NovaGenerator() {}


void NovaGenerator:: generateMaze(Maze& maze)
{
    if (maze.getWidth() == 0 || maze.getHeight() == 0)
        throw MazeException("0 is not a valid width or height");
    maze.addAllWalls();
    setUpArray(maze);
    generatePath(0, 0, maze);
}


void NovaGenerator:: setUpArray(Maze& maze)
{
    maze2DArray.resize(maze.getWidth(), std::vector<bool>(maze.getHeight(), false));
}


void NovaGenerator:: generatePath(int x, int y, Maze& maze)
{
    maze2DArray[x][y] = true;
    std::vector<Direction> possibleDirections = validDirections(x, y, maze);
    
    while (possibleDirections.size() > 0)
    {
        Direction directionToMove = possibleDirections[rand() % possibleDirections.size()];
        int newx = x;
        int newy = y;
        move(newx, newy, directionToMove);
        if (maze2DArray[newx][newy] == false)
        {
            maze.removeWall(x, y, directionToMove);
            generatePath(newx, newy, maze);
        }
        possibleDirections = validDirections(x, y, maze);
    }    
}


std::vector<Direction> NovaGenerator:: validDirections(int x, int y, Maze& maze)
{
    std::vector<Direction> validDir;
    if (maze.wallExists(x, y, Direction::left) && x - 1 >= 0 && maze2DArray[x - 1][y] == false)
        validDir.push_back(Direction::left);
   
    if (maze.wallExists(x, y, Direction::right) && x + 1 < maze.getWidth() && maze2DArray[x + 1][y] == false)
        validDir.push_back(Direction::right);

    if (maze.wallExists(x, y, Direction::up) && y - 1 >= 0 && maze2DArray[x][y - 1] == false)
        validDir.push_back(Direction::up);

    if (maze.wallExists(x, y, Direction::down) && y + 1 < maze.getHeight() && maze2DArray[x][y + 1] == false)
        validDir.push_back(Direction::down);
    
    return validDir;
}


void NovaGenerator:: move(int& x, int& y, Direction dir)
{
    switch(dir)
    {
        case Direction::up:
            --y;
            break;
        case Direction::down:
            ++y;
            break;
        case Direction::left:
            --x;
            break;
        case Direction::right:
            ++x;
            break;
    }       
}












