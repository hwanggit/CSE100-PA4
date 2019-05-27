/* Description: This is a program that finds the closest relationship
 * between two actors based on a graph of actors connected by the 
 * movies they collectively acted in.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 26, 2019
 * Sources: Piazza
 */

#include "ActorGraph.hpp"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Pathfinder main program, loads actor, year, movie from file
 * and builds graph, then searches for the shortest path between
 * two actors
 */
int main(int argc, char** argv)
{
  	// Check valid arguments
	if(argc < 2) {
		cout << "This program needs exactly one argument!" << endl;
        exit(-1);
    }
	
	// Extract input file
	char * inputFile = argv[1];

	// Make new actorGraph
	ActorGraph * imdb = new ActorGraph();

	// Read file and initialize actorGraph
	imdb->loadFromFile(inputFile, 0);	
	
	// Deallocate imdb
	delete imdb;
}
