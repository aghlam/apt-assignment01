.default: all

all: assign1

clean:
	rm -f assign1 *.o

assign1: Breadcrumb.o Trail.o MazeSolver.o main.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^