/* Description: This is a program that finds the closest relationship
 * between two location based on a graph of locations at UCSD. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: Jun 03, 2019
 * Sources: Piazza
 */

#include "UcsdGraph.hpp"
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Reads files and initializes Ucsd Graph, then searches for quickest path
 */
int main(int argc, char** argv)
{
  	// Check valid arguments
	if(argc < 5) {
		cout << argv[0] << " called with incorrect arguments." << endl;
		cout << "Usage: " << argv[0] << " ucsdxy.txt ucsdpairs.txt";
		cout << "test_location_pairs.txt a_star_paths.txt" << endl;
        exit(-1);
    }

	// Extract initialize file
	char * initialize (argv[1]);
	 
	// Determine if weighted or unweighted
	char * edges (argv[2]);
	
	// Make new ucsdGraph
	UcsdGraph * ucsd = new UcsdGraph();

	// Load data from file
	cout << "Reading " << initialize << " ..." << endl;
	
	ucsd->loadFromFile(initialize, true);	
	ucsd->loadFromFile(edges, false);

	cout << "done" << endl;
	
	// Get test pairs file
	char * testPairs (argv[3]);
	
	// Get outputfile
	string outputFile (argv[4]);
	
	// Open output file
	ofstream outFile (outputFile);

	// load pairs and print shortest paths
	ucsd->loadPairs(testPairs, outFile);	
	
	// Deallocate imdb
	delete ucsd;
}
