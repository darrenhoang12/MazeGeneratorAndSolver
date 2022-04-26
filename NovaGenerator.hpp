#ifndef NOVAGENERATOR_HPP
#define NOVAGENERATOR_HPP
//maze generator is named after my cat
#include <iostream>
#include <vector>
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Direction.hpp"


class NovaGenerator: public MazeGenerator
{
    public:
        NovaGenerator();
        void generateMaze(Maze& maze) override;
        void setUpArray(Maze& maze);
        void generatePath(int x, int y, Maze& maze);
        std::vector<Direction> validDirections(int x, int y, Maze& maze);
        void move(int& x, int& y, Direction dir);
    private:
        std::vector<std::vector<bool>> maze2DArray;
};

#endif
