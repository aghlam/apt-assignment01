
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

// Milestone #4
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

    // ------------------------------MILESTONE #4------------------------------
    std::string str = "";
    int rows = -1;
    int cols = 0;

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

    Maze maze;

    maze = make_maze(rows, cols, str);

    MazeSolver* solver = new MazeSolver(rows, cols);
    solver->solve(maze, rows, cols);

    Trail* solution = nullptr;
    solution = solver->getSolution(rows, cols);
    printMazeStdout(maze, solution, rows, cols);
    printDirections(maze, solution, rows, cols);

    std::cout << solution->size() << std::endl;
    delete_maze(maze, rows, cols);
    delete solution;
    delete solver;

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

    for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
        if (solution->getPtr(i) != nullptr) {
            if (!solution->getPtr(i)->isStale()) {
                x = solution->getPtr(i)->getX();
                y = solution->getPtr(i)->getY();
                
                maze[y][x] = ROUTE;
            }
        }
    }

    for (int i = 0; i < MAZE_DIM; ++i) {
        for (int j = 0; j < MAZE_DIM; ++j) {
            std::cout << maze[i][j];
            }
        std::cout << std::endl;
    }
    
}

// Milestone #3
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
Maze make_maze(const int rows, const int cols, std::string str) {
    Maze maze = nullptr;
    int length = str.length();
    int s = 0;

    if (rows >= 0 && cols >= 0) {
        maze = new char*[rows];
        for (int i = 0; i != rows; ++i) {
            maze[i] = new char[cols];
        }
    }

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

void printMazeStdout(Maze maze, Trail* solution, int rows, int cols) {

    int x = 0;
    int y = 0;

    for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
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
