
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   // TODO
   this->solution = new Trail();
}

MazeSolver::~MazeSolver() {
   // TODO delete solution;
}

void MazeSolver::solve(Maze maze) {
   // TODO
   // Coordinates
   int x = 0;
   int y = 0;
   bool notE = true;

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
   // Breadcrumb* test = new Breadcrumb(3, 1, false);
   // solution->addCopy(test);
   

   std::cout << "Current location: " << maze[y][x] << std::endl;

   while(notE) {
      // Look NORTH
      if(maze[y-1][x] == OPEN && !solution->contains(x, y-1)) {   // Is it open AND is there a breadcrumb?
         y--;                                                     // Move NORTH
         Breadcrumb* bc = new Breadcrumb(x, y, false);            // Create breadcrumb at coordinates
         solution->addCopy(bc);                                   // Add to trail
      }
      // Look EAST
      else if(maze[y][x+1] == OPEN && !solution->contains(x+1, y)) { 
         x++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
      }
      // Look SOUTH
      else if(maze[y+1][x] == OPEN && !solution->contains(x, y+1)) {
         y++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
      } 
      // Look WEST
      else if(maze[y][x-1] == OPEN && !solution->contains(x-1, y)) {
         x--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
      }
      // If NO.. Backtrack!!
      else {
         bool looking = true;
         int trailIndex = solution->size()-1;
         solution->getPtr(trailIndex)->setStale(true);
         
         do {
            if (solution->getPtr(trailIndex)->isStale()) {
               trailIndex--;
            } else {
               x = solution->getPtr(trailIndex)->getX();
               y = solution->getPtr(trailIndex)->getY();
               looking = false;
            }
         } while (looking);
         

        

         // if(!solution->getPtr(trailIndex)->isStale()) {     // Is it stale!?
         //    solution->getPtr(trailIndex)->setStale(true);   // NO -> Stale that breadcrumb!!
         // } else {                                           // YES -> Do this then!
         //    trailIndex--;
         //    x = solution->getPtr(trailIndex)->getX();
         //    y = solution->getPtr(trailIndex)->getY();
         // }
         // std::cout << trailIndex << std::endl;
         
         // do {
         //    trailIndex--;
         //    if (!solution->getPtr(trailIndex)->isStale()) {
         //       x = solution->getPtr(trailIndex)->getX();
         //       y = solution->getPtr(trailIndex)->getY();

         //       std::cout << "x Coord: " << x << std::endl;
         //       std::cout << "y Coord: " << y << std::endl;
         //       std::cout << "trailindex: " << trailIndex << std::endl;
         //    }

         //    std::cout << "x Coord: " << x << std::endl;
         //    std::cout << "y Coord: " << y << std::endl;

         // } while (solution->getPtr(trailIndex)->isStale());

      }

      std::cout << "Current breadcrumb X: " << solution->getPtr(solution->size()-1)->getX() << std::endl;
      std::cout << "Current breadcrumb Y: " << solution->getPtr(solution->size()-1)->getY() << std::endl;

      if ((maze[y-1][x])=='E' || (maze[y][x+1])=='E' || (maze[y+1][x])=='E' || (maze[y][x-1])=='E') {
         std::cout << maze[y][x] << std::endl;
         std::cout << "Found E" << std::endl;
         notE = false;
      }
   }

}

Trail* MazeSolver::getSolution() {
   // TODO
   return nullptr;
}
