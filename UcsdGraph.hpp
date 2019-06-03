/* UcsdGraph.hpp
 * Author: Luhao Wang, luw055
 * Date:   05/25/19
 *
 * This is a program that defines a Ucsd Graph, that stores all
 * locations on campus and can be used to search for shortest
 * paths between locations
 */

#ifndef UCSDGRAPH_HPP
#define UCSDGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "UcsdNode.hpp"

using namespace std;

/* Ucsd graph is a relationship between locations on UCSD campus
 * represented with a graph data structure
 */
class UcsdGraph {
	
 protected:
	
	// To store cast for each movie, and for each year
	std::unordered_map<std::string, UcsdNode *> ucsd_graph;
	
	// Define comparison function for dijkstra priority queue
	struct compareNode {
		bool operator() (UcsdNode * p1, UcsdNode * p2) {
			return p2->distance < p1->distance;
		}
	};
	   
 public:

	/**
     * Constuctor of the Ucsd graph
     */
    UcsdGraph(void);

	/* Destructor for UcsdGraph*/
	~UcsdGraph();
	
    /* Load the graph from a tab-delimited file of ucsd location relationships.
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool initialize);  
	
	// Method to read pairs from test pairs file and print out shortest path
	bool loadPairs(const char * in_file, ofstream & out);

	// Heuristic function, calculates Euclidean distance times constant
	double heuristic(UcsdNode * node1, UcsdNode * node2, int constant);

	// Helper method to BFS traverse graph and find closest path
	void findShortestPath(vector<std::string> & start,vector<std::string> & end,
							ofstream & out);

};

#endif // UCSDGRAPH_HPP
