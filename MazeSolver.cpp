
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   this->solution = new Trail();
}

MazeSolver::~MazeSolver() {
   delete solution;
}

void MazeSolver::solve(Maze maze) {
   // Coordinates, 
   int x = 0;
   int y = 0;
   int trailIndex = 0;
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

   // Breadcrumb* bc = new Breadcrumb(x, y, false);
   // solution->addCopy(bc);
   // Breadcrumb* test = new Breadcrumb(12, 6, false);
   // solution->addCopy(test);
   

   // std::cout << "Current location: " << maze[y][x] << std::endl;

   while(notE) {

      // std::cout << "Current breadcrumb start of loop: (" 
      //           << x 
      //           << ", " << y
      //           << ")" << std::endl;

      // Look NORTH
      if(maze[y-1][x] == OPEN && !solution->contains(x, y-1)) {      // Is it open AND is there a breadcrumb?
         y--;                                                        // Move NORTH
         Breadcrumb* bc = new Breadcrumb(x, y, false);               // Create breadcrumb at coordinates
         solution->addCopy(bc);                                      // Add to trail
         trailIndex = solution->size()-1;                            // Set non stale breadcrumb index
      }
      // Look EAST
      else if(maze[y][x+1] == OPEN && !solution->contains(x+1, y)) { 
         x++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look SOUTH
      else if(maze[y+1][x] == OPEN && !solution->contains(x, y+1)) {
         y++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      } 
      // Look WEST
      else if(maze[y][x-1] == OPEN && !solution->contains(x-1, y)) {
         x--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Backtrack!!
      else {
         bool looking = true;
         
         solution->getPtr(trailIndex)->setStale(true);               // Make that breadcrumb stale!

         do {
            if(solution->getPtr(trailIndex)->isStale()) {
               trailIndex = trailIndex-1;
            } else {
               x = solution->getPtr(trailIndex)->getX();
               y = solution->getPtr(trailIndex)->getY();
               looking = false;
            }

         } while (looking);

      }

      if ((maze[y-1][x])=='E' || (maze[y][x+1])=='E' || (maze[y+1][x])=='E' || (maze[y][x-1])=='E') {
         // std::cout << "Found E" << std::endl;
         notE = false;
      }

   }

}

Trail* MazeSolver::getSolution() {
   // TODO
   solutionCopy = new Trail(*solution);
   return solutionCopy;
}


// TESTING

Trail* MazeSolver::returnSolution() {
      return solution;
   }
