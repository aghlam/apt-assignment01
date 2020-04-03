
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   // TODO
}

MazeSolver::~MazeSolver() {
   // TODO delete solution;
}

void MazeSolver::solve(Maze maze) {
   // TODO
   // Coordinates
   int x = 0;
   int y = 0;

   // Find starting point 'S' and adding first breadcrumb
   for(int i = 0; i < MAZE_DIM; ++i) {
      for(int j = 0; j < MAZE_DIM; ++j) {
         if(maze[i][j] == 'S') {
            x = j;
            y = i;
         }
      }
   }

   Breadcrumb* bc = new Breadcrumb(x, y, false);
   solution->addCopy(bc);

   // Loop to solve
   while (maze[x][y]!='E') {
      // Look NORTH
      if(maze[x][y-1] == OPEN && solution->contains(x, y-1)){
         y -= 1;
      } 
      // Look EAST
      else if(maze[x+1][y] == OPEN && solution->contains(x+1, y)) { 
         x += 1;
      } 
      // Look SOUTH
      else if(maze[x][y+1] == OPEN && solution->contains(x, y+1)) {
         y += 1;
      } 
      // Look WEST
      else if(maze[x-1][y] == OPEN && solution->contains(x-1, y)) {
         x -= 1;
      }
      // Backtrack!!
      else {
         
      }

   }
}

Trail* MazeSolver::getSolution() {
   // TODO
   return nullptr;
}
