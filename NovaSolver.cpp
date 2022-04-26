#include <iostream>
#include <vector>
#include <utility>
#include <ics46/factory/DynamicFactory.hpp>
#include "NovaSolver.hpp"
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp"
#include "MazeException.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, NovaSolver, "Nova Solver (Required)");


NovaSolver::NovaSolver() {}

void NovaSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    if (maze.getWidth() == 0 || maze.getHeight() == 0)
        throw MazeException("The height or weight of a maze cannot be 0");
    mazeSolution.restart();
    setUpArray(maze);
    findSolutionPath(maze, mazeSolution);
}


void NovaSolver::setUpArray(const Maze& maze)
{
    maze2DArray.resize(maze.getWidth(), std::vector<bool>(maze.getHeight(), false));
}


void NovaSolver::findSolutionPath(const Maze& maze, MazeSolution& mazeSolution)
{
    if (mazeSolution.isComplete())
        return;
    std::pair<int, int> xyPair = mazeSolution.getCurrentCell();
    maze2DArray[xyPair.first][xyPair.second] = true;
    std::vector<Direction> availableMoves = validDirections(xyPair.first, xyPair.second,maze);    
    if (availableMoves.size() > 0) 
    {
        for (int i = 0; i < availableMoves.size(); ++i)
        {
            Direction directionToMove = availableMoves[0];
            if (mazeSolution.isComplete() == false) 
            {
                mazeSolution.extend(directionToMove);
                findSolutionPath(maze, mazeSolution); 
            }
        }
    } else {
        mazeSolution.backUp();
        findSolutionPath(maze, mazeSolution);
    }
}


std::vector<Direction> NovaSolver::validDirections(int x, int y, const Maze& maze)
{
    std::vector<Direction> validDir;
    if (x - 1 >= 0 && maze.wallExists(x, y, Direction::left) == false && maze2DArray[x - 1][y] == false)
        validDir.push_back(Direction::left);

    if (x + 1 < maze.getWidth() && maze.wallExists(x, y, Direction::right) == false && maze2DArray[x + 1][y] == false)
        validDir.push_back(Direction::right);

    if (y - 1 >= 0 && maze.wallExists(x, y, Direction::up) == false && maze2DArray[x][y - 1] == false)
        validDir.push_back(Direction::up);

    if (y + 1 < maze.getHeight() && maze.wallExists(x, y, Direction::down) == false && maze2DArray[x][y + 1] == false)
        validDir.push_back(Direction::down);

    return validDir;
}
