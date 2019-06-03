/* Description: This is a program that will print out the minimum
 * connections between actors in the ActorGraph program, such that 
 * there is a path through the whole graph.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: Jun 02, 2019
 * Sources: Piazza
 */

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include "DisjointSet.hpp"
#include "ActorGraph.hpp"

using namespace std;

// Comparator function for ActorEdge to sort by weight
bool compareEdge (ActorEdge * p1, ActorEdge * p2) {
	return p1->weight < p2->weight;
}
	
/**
 * Movie Traveler program, sorts an array of edges based on weight, then 
 * outputs the minimum weights that form a complete path connecting every node.
 */
int main(int argc, char** argv)
{
  	// Check valid arguments
	if(argc < 3) {
		cout << argv[0] << " called with incorrect arguments." << endl;
		cout << "Usage: " << argv[0] << " movie_cast_tsv_file "; 
		cout << "output_paths_tsv_file" << endl;
        exit(-1);
    }

	// Extract input file
	char * inputFile (argv[1]);
	 
	// Make new actorGraph
	ActorGraph * imdb = new ActorGraph();

	// Read file and initialize actorGraph
	imdb->loadFromFile(inputFile, true);	
	
	// Initialize a disjoint set
	DisjointSet * actorSet = new DisjointSet(imdb->actors);
	
	// Sort the edges based on weight
	std::sort(imdb->edges.begin(), imdb->edges.end(), compareEdge);

	// Get outputfile
	string outputFile (argv[2]);
	
	// Open output file
	ofstream outFile (outputFile);
	
	// Print header to outputfile
	outFile << "(actor)<--[movie#@year]-->(actor)\n";
	
	// Keep counts of nodes, edges, and total edge weights
	int nodesConnected = 0;
	int edgesConnected = 0; 
	int totalWeight = 0;
	
	// For each edge, run Kruskal's algorithm to build MST
	for (unsigned int i=0; i<imdb->edges.size(); i++) {
		ActorEdge * currEdge = imdb->edges[i];

		// Get actor names
		std::string actor1 = currEdge->actor1->name;
		std::string actor2 = currEdge->actor2->name;
		
		// Check if algorithm is finished
		if (actorSet->checkFinished()) {
			// Increment nodes connected
			nodesConnected++;
			outFile << "#NODE CONNECTED: " << nodesConnected << endl;
			outFile << "#EDGE CHOSEN: " << edgesConnected << endl;
			outFile << "TOTAL EDGE WEIGHTS: " << totalWeight << endl;
			break;
		}
		
		// Run union on all minimum edges
		if (actorSet->Union(actor1, actor2)) {
			// Actor 1 Link
			outFile << "(" << actor1 << ")";
			nodesConnected++;

			// Edge outputted
			outFile << "<--[" << currEdge->movieName << "#@" << currEdge->year;
			edgesConnected++;

			// Actor2 link
			outFile << "]-->(" << actor2 << ")" << endl;

			// Increment total weight
			totalWeight += (currEdge->weight);
		}
	}
	
	// Close output file
	outFile.close();

	// Deallocate imdb and disjoint set
	delete actorSet;
	delete imdb;
}
