// Alan Lam s3436174

#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   this->solution = new Trail();
}

MazeSolver::~MazeSolver() {
   delete solution;
}
/*
   The solve method which takes in the input maze and solves it following the 
   Tremaux algorithm.
*/
void MazeSolver::solve(Maze maze) {
   // Coordinates, 
   int x = 0;
   int y = 0;
   // Index to keep track of the last non-stale breadcrumb
   int trailIndex = 0;
   // Varaiable to determine if 'E' has been found
   bool notE = true;

   // Find starting point 'S' by scanning input maze array
   for(int i = 0; i < MAZE_DIM; ++i) {
      for(int j = 0; j < MAZE_DIM; ++j) {
         if(maze[i][j] == 'S') {
            x = j;
            y = i;
         }
      }
   }
   /*
      Loop to look for the next available path - one that does not contain a 
      breadcrumb and is an 'OPEN' path. Once a direction has been obtained, add 
      a breadcrumb containing coordinates and the direction moved in to trail 
      array.
   */ 
   while(notE) {
      /*
         Look NORTH! - as long as Y is not 0 - to prevent looking out of bounds 
         of the array if S starts at the top of the maze.
      */ 
      if(y != 0 && maze[y-1][x] == OPEN && !solution->contains(x, y-1)) {
         y--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("north");
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look EAST!
      else if(maze[y][x+1] == OPEN && !solution->contains(x+1, y)) { 
         x++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("east"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      // Look SOUTH!
      else if(maze[y+1][x] == OPEN && !solution->contains(x, y+1)) {
         y++;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("south"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      } 
      // Look WEST!
      else if(maze[y][x-1] == OPEN && !solution->contains(x-1, y)) {
         x--;
         Breadcrumb* bc = new Breadcrumb(x, y, false);
         bc->setDirection("west"); 
         solution->addCopy(bc);
         trailIndex = solution->size()-1;
      }
      /*
         Backtrack!! - if no available paths, loop through trail array using 
         last available index to find a non stale breadcrumb
      */ 
      else {
         bool looking = true;
         // Set current breadcrumb to stale
         solution->getPtr(trailIndex)->setStale(true);
         // Look for the last non-stale breadcrumb coordinates
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
      // Found exit 'E'! - Stops loop
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


// Milestone #4 Code

// Milestone #4 - Constructor that passes through maze size parameters
MazeSolver::MazeSolver(int rows, int cols) {
   this->solution = new Trail(rows, cols);
}


// Milestone #4 - Returns a deep copy with dynamic maze size parameters
Trail* MazeSolver::getSolution(int rows, int cols) {
   solutionCopy = new Trail(*solution, rows, cols);
   return solutionCopy;
}

/*
   Milestone #4 solve - This is essentially the same as the above solve method 
   modified to include parameters for the dynamic maze size.
*/
void MazeSolver::solve(Maze maze, int rows, int cols) {
   // Coordinates, 
   int x = 0;
   int y = 0;
   int trailIndex = 0;
   bool notE = true;

   // Find starting point 'S'
   for(int i = 0; i < rows; ++i) {
      for(int j = 0; j < cols; ++j) {
         if(maze[i][j] == 'S') {
            x = j;
            y = i;
         }
      }
   }

   while(notE) {
      // Look NORTH! - as long as Y is not 0
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
      //Found E!
      if ((maze[y-1][x])=='E' || (maze[y][x+1])=='E' 
            || (maze[y+1][x])=='E' || (maze[y][x-1])=='E') {
         notE = false;
      }
   }
}

