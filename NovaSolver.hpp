#ifndef NOVASOLVER_HPP
#define NOVASOLVER_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp"


class NovaSolver: public MazeSolver
{
    public:
        NovaSolver();
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
        void setUpArray(const Maze& maze);
        void findSolutionPath(const Maze& maze, MazeSolution& mazeSolution);
        std::vector<Direction> validDirections(int x, int y, const Maze& maze);
    private:
        std::vector<std::vector<bool>> maze2DArray;
};

#endif
