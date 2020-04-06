
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

   while(notE) {

      // std::cout << "Current breadcrumb start of loop: (" 
      //           << x 
      //           << ", " << y
      //           << ")" << std::endl;

      // Look NORTH as long as y is not 0
      if(y != 0 && maze[y-1][x] == OPEN && !solution->contains(x, y-1)) {
         y--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("north");
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look EAST
      else if(maze[y][x+1] == OPEN && !solution->contains(x+1, y)) { 
         x++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("east"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look SOUTH
      else if(maze[y+1][x] == OPEN && !solution->contains(x, y+1)) {
         y++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("south"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      } 
      // Look WEST
      else if(maze[y][x-1] == OPEN && !solution->contains(x-1, y)) {
         x--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("west"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Backtrack!!
      else {
         bool looking = true;
         
         solution->getPtr(trailIndex)->setStale(true);

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

      if ((maze[y-1][x])=='E' || (maze[y][x+1])=='E' 
            || (maze[y+1][x])=='E' || (maze[y][x-1])=='E') {
         notE = false;
      }

   }

}

Trail* MazeSolver::getSolution() {
   solutionCopy = new Trail(*solution);
   return solutionCopy;
}

// Milestone #4 Constructor
MazeSolver::MazeSolver(int rows, int cols) {
   this->solution = new Trail(rows, cols);
}

Trail* MazeSolver::getSolution(int rows, int cols) {
   solutionCopy = new Trail(*solution, rows, cols);
   return solutionCopy;
}

// Milestone #4 solver
void MazeSolver::solve(Maze maze, int rows, int cols) {
   // Coordinates, 
   int x = 0;
   int y = 0;
   int trailIndex = 0;
   bool notE = true;

   // Find starting point 'S' and adding first breadcrumb
   for(int i = 0; i < rows; ++i) {
      for(int j = 0; j < cols; ++j) {
         if(maze[i][j] == 'S') {
            x = j;
            y = i;
            // std::cout << "x: " << x << std::endl;
            // std::cout << "y: " << y << std::endl;
         }
      }
   }

   while(notE) {

      std::cout << "Current breadcrumb start of loop: (" 
                << x 
                << ", " << y
                << ")" << std::endl;

      // Look NORTH
      if(y != 0 && maze[y-1][x] == OPEN && !solution->contains(x, y-1)) {      
         y--;                                                        
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("north");              
         solution->addCopy(bc);                                    
         trailIndex = solution->size()-1;       
      }
      // Look EAST
      else if(maze[y][x+1] == OPEN && !solution->contains(x+1, y)) { 
         x++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("east"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look SOUTH
      else if(maze[y+1][x] == OPEN && !solution->contains(x, y+1)) {
         y++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("south"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      } 
      // Look WEST
      else if(maze[y][x-1] == OPEN && !solution->contains(x-1, y)) {
         x--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("west"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Backtrack!!
      else {
         bool looking = true;
         
         solution->getPtr(trailIndex)->setStale(true);

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
         notE = false;
      }

   }

   // std::cout << solution->size() << std::endl;

}

