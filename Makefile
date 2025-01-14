# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use 
# "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder movietraveler navigationsystem

# include what ever source code *.hpp files pathfinder relies on (these are 
# merely the ones that were used in the solution)

pathfinder: ActorGraph.o

movietraveler: DisjointSet.o ActorGraph.o

navigationsystem: UcsdGraph.o

# include what ever source code *.hpp files ActorGraph relies on (these are
# merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.hpp
# file that is already included with class/method headers

UcsdGraph.o: UcsdNode.o UcsdGraph.hpp UcsdGraph.cpp

ActorGraph.o: ActorNode.o ActorEdge.o ActorGraph.hpp ActorGraph.cpp

DisjointSet.o: ActorNode.o DisjointSet.hpp DisjointSet.cpp

ActorEdge.o: ActorEdge.hpp ActorEdge.cpp

UcsdNode.o: UcsdNode.hpp UcsdNode.cpp

ActorNode.o: ActorNode.hpp ActorNode.cpp

clean:
	rm -f pathfinder *.o core*

