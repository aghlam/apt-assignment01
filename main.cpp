// Alan Lam s3436174
/*
    Milestone #2
    Following the instructions outlined in the assignment spec, I implemented 
    maze reader and printer first to make sure the maze was read in properly. 
    Once that was done, I implemented the Breadcrumb, Trail and MazeSolver 
    classes. Afterwards, all I had to do was make sure the solution was passed 
    to the main class and the maze with the solution was printed out properly. 
    
    The majority of my time was spent coding in the MazeSolver class as this 
    was where the bulk of the functions worked. This was also where the bulk of
    issues and problems I had were. The code determining which direction to 
    travel was fairly easily implemented but the main trouble was trying to find
    a way to backtrack to a non-stale breadcrumb. Using just the 'length' of the 
    trail was not allowing me to move backwards in the trail for some reason. I 
    managed to solve the problem by creating a variable which kept track of where 
    the last non-breadcrumb was instead of using the length variable.

    The other major problem I encountered was trying to implement a DEEP copy 
    of the solution array. It evaded me for a while that I had to create a 
    completely new object of trail and instantiate that with the same elements 
    of the original solution before passing it on as a DEEP copy

    While trying test mazes, I realised that the program failed when the starting
    point of a maze was on the top line. This was due to the solver trying to 
    look for a path that would be out of bounds. This was solved by making the 
    code to not look for a north direction while y = 0.

    While I believe there Breadcrumb and Trail classes were fairly well implemented,
    the MazeSolver class could have been improved on. Instead of creating a new 
    varibale to track the index, I could have used length but I wasn't able to 
    make that work.

    Milestone #3
    Milestone 3 was actually fairly easy to implement. I had to create new a
    variable in the Breadcrumb class to store the direction the trail moved in. 
    Afterwards all that I needed to do was return the stored direction and have 
    it printed out with the non-stale breadcrumbs once the maze with the solution 
    was printed.

    Milestone #4
    The main problem of milestone #4 was figuring out how to read a dynamic maze 
    and obtain its dimensions. I managed to solve this by reading the input maze 
    and appending each element to a string. I divided the string length by the 
    number of new lines in the maze to obtain the column and row dimensions. Once 
    this was obtained, it was a matter of passing the dimensions to the maze_maker
    method and printing out the maze.

    I chose to write obtaining the maze dimension in the main method as I was not
    able to determine a method to read from input once and return two variables.

    The other issue was figuring out that I had to implement methods and constructors
    to take in the new dimensions instead of using the standard 20x20. I did this
    by following the code and seeing what method was called and which required 
    passing on the new dimensions.


    ****
    To get milestone #2 code working - have to comment out all milestone #4 code
    ****
*/

#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

// Milestone #3 - Print out directions
void printDirections(Maze maze, Trail* solution);

// Milestone #4 - Same functions as above but included parameters for rows and cols
Maze make_maze(const int rows, const int cols, std::string str);
void printMazeStdout(Maze maze, Trail* solution, int rows, int cols);
void delete_maze(Maze maze, int rows, int cols);
void printDirections(Maze maze, Trail* solution, int rows, int cols);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testBreadcrumb();
    // testTrail();
    // std::cout << "DONE TESTING" << std::endl << std::endl;
    

    // ------------------------------MILESTONE #2------------------------------
    // // Load Maze from stdin
    // Maze maze;
    // readMazeStdin(maze);

    // // Solve using MazeSolver
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    // MazeSolver* solver = new MazeSolver();
    // Trail* solution = nullptr;
    // solver->solve(maze);
    // solution = solver->getSolution();

    // // Print Maze to stdout
    // printMazeStdout(maze, solution);

    // std::cout << std::endl;

    // // Milestone #3 - Print directions to stdout
    // printDirections(maze, solution);

    // delete solver;
    // delete solution;
    // ----------------------------MILESTONE #2 END----------------------------

    // ------------------------------MILESTONE #4------------------------------
    // To hold the read input
    std::string str = "";
    // Rows start at -1 to account for extra line at end of maze
    int rows = -1;
    int cols = 0;

    /*
        Read from standard input and determine the size of the maze. Each character
        of the input is appended to a string. The number of new line elements are
        counted to obtain the number of rows and the string length is then divided 
        by the rows to obtain the number of columns.
    */
    if (std::cin.good()) {
        char c;
        while (!std::cin.eof()) {
            std::cin.get(c);
            if (c == OPEN || c == 'S' || c == 'E' || c == WALL) {
                str += c;
            }
            if (c == '\n') {
                rows++;
            }
        }
    }
    
    cols = str.length()/rows;

    // Create maze
    Maze maze;
    maze = make_maze(rows, cols, str);

    // Solve maze
    MazeSolver* solver = new MazeSolver(rows, cols);
    solver->solve(maze, rows, cols);

    // Obtain copy of solution trail
    Trail* solution = nullptr;
    solution = solver->getSolution(rows, cols);

    // Print out maze with solution and directions
    printMazeStdout(maze, solution, rows, cols);
    std::cout << std::endl;
    printDirections(maze, solution, rows, cols);

    delete_maze(maze, rows, cols);
    delete solver;
    delete solution;

    // ----------------------------MILESTONE #4 END----------------------------

    return EXIT_SUCCESS;
}


void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    if (std::cin.good()) {
        for (int i = 0; i < MAZE_DIM; ++i) {
            for (int j = 0; j < MAZE_DIM; ++j) {
                std::cin >> maze[i][j];
            }
        }
    }
}

void printMazeStdout(Maze maze, Trail* solution) {
    int x = 0;
    int y = 0;
    // Change to * for all non-stale breadcrumbs at coordinates x, y
    for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
        if (solution->getPtr(i) != nullptr) {
            if (!solution->getPtr(i)->isStale()) {
                x = solution->getPtr(i)->getX();
                y = solution->getPtr(i)->getY();
                
                maze[y][x] = ROUTE;
            }
        }
    }
    // Prints out maze with solution trail
    for (int i = 0; i < MAZE_DIM; ++i) {
        for (int j = 0; j < MAZE_DIM; ++j) {
            std::cout << maze[i][j];
            }
        std::cout << std::endl;
    }
}

// Milestone #3
// Prints out directions stored with the non-stale breadcrumbs
void printDirections(Maze maze, Trail* solution) {
    for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
        if (solution->getPtr(i) != nullptr) {
            if (!solution->getPtr(i)->isStale()) {
                std::cout << solution->getPtr(i)->getDirection() << std::endl;
            }
        }
    }
}


// Milestone #4
/*
    Creates maze according to the rows and cols parameters. Inputs each character 
    of the string into array to create the maze
*/
Maze make_maze(const int rows, const int cols, std::string str) {
    Maze maze = nullptr;
    int length = str.length();
    // Varibale to keep track of str index
    int s = 0;
    // Dynamic maze dimension creation - (It's magic!)
    if (rows >= 0 && cols >= 0) {
        maze = new char*[rows];
        for (int i = 0; i != rows; ++i) {
            maze[i] = new char[cols];
        }
    }
    // Cycles through the string by each character and inputs into the maze array
    while(s<length) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maze[i][j] = str[s];
                s++;
            }
        }
    }
    return maze;
}

// Same as standard print method but with the dynamic maze parameters
void printMazeStdout(Maze maze, Trail* solution, int rows, int cols) {

    int x = 0;
    int y = 0;

    for (int i = 0; i < rows*cols; ++i) {
        if (solution->getPtr(i) != nullptr) {
            if (!solution->getPtr(i)->isStale()) {
                x = solution->getPtr(i)->getX();
                y = solution->getPtr(i)->getY();
                
                maze[y][x] = ROUTE;
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

void delete_maze(Maze maze, int rows, int cols) {
    if (rows >= 0 && cols >= 0) {
        for (int i = 0; i != rows; ++i) {
            delete maze[i];
        }
        delete maze;
    }
    return;
}

// Same as standard printDirections method but with dynamic maze parameters
void printDirections(Maze maze, Trail* solution, int rows, int cols) {
    for (int i = 0; i < rows*cols; ++i) {
        if (solution->getPtr(i) != nullptr) {
            if (!solution->getPtr(i)->isStale()) {
                std::cout << solution->getPtr(i)->getDirection() << std::endl;
            }
        }
    }
}


// Initial tests
void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
