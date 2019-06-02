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
	if(argc < 5) {
		cout << argv[0] << " called with incorrect arguments." << endl;
		cout << "Usage: " << argv[0] << " movie_cast_tsv_file u/w " 
			 << "pairs_tsv_file output_paths_tsv_file" << endl;
        exit(-1);
    }

	// Extract input file
	char * inputFile (argv[1]);
	 
	// Determine if weighted or unweighted
	string weight (argv[2]);
	
	// If weight is not u/w, print error
	if (weight.compare("w") != 0 && weight.compare("u") != 0) {
		cout << "wrong parameter '" << weight << "', must be u or w" << endl;
		exit(-1);
	}
	
	// Make new actorGraph
	ActorGraph * imdb = new ActorGraph();

	cout << "Reading " << inputFile << " ..." << endl;
	
	// If weighted, load with 1, else 0
	if (weight.compare("w") == 0) {
		// Read file and initialize actorGraph
		imdb->loadFromFile(inputFile, true);	
	}
	else {
		imdb->loadFromFile(inputFile, false);	
	}

	cout << "done" << endl;
	
	// Get test pairs file
	char * testPairs (argv[3]);
	
	// Get outputfile
	string outputFile (argv[4]);
	
	// Open output file
	ofstream outFile (outputFile);

	// If weighted, load with 1, else 0
	if (weight.compare("w") == 0) {
		// load pairs and print shortest paths
		imdb->loadPairs(testPairs, outFile, true);	
	}
	else {
		// load pairs and print shortest paths
		imdb->loadPairs(testPairs, outFile, false);	
	}	
	
	// Deallocate imdb
	delete imdb;
}
