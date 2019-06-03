/*
 * ActorGraph.hpp
 * Author: Luhao Wang, luw055
 * Date:   05/25/19
 *
 * This file is meant to exist as a container for starter code that you can use 
 * to read the input file format defined imdb_2019.tsv. Feel free to modify 
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "ActorNode.hpp"
#include "ActorEdge.hpp"

using namespace std;

/* Actor graph is a relationship between actors and the movies they acted in
 * represented with a graph data structure
 */
class ActorGraph {
	
 protected:
	
	// To store cast for each movie, and for each year
	std::unordered_map<std::string, int> year_graph;
	std::unordered_map<std::string, std::string> title_graph;	
	std::unordered_map<std::string, vector<ActorNode *>> movie_graph;
	std::unordered_map<std::string, ActorNode *> actor_graph;
	
	// Define comparison function for dijkstra priority queue
	struct compareNode {
		bool operator() (ActorNode * p1, ActorNode * p2) {
			return p2->distance < p1->distance;
		}
	};
	   
 public:

	vector<ActorNode *> actors; // BSA to store actor names
	vector<ActorEdge *> edges; // BSA to store movie and year
	
	/**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

	/* Destructor for ActorGraph*/
	~ActorGraph();
	
	/**
	 * Helper method to binary search for given node in actor list 
	 */
	unsigned int bSearchActor(ActorNode * item, vector<ActorNode *> & list);
	
	/** Insert item into sorted position based on binary search*/
	bool insertActor(ActorNode * item, vector<ActorNode *> & list);

	/** Return the pointer to the actor if the given actor is found*/
	ActorNode * findActor(ActorNode * item);

    /* Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + 
	 *													(2019 - movie_year), 
     *                      otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);  
	
	// helper method to build graph using unordered map
	void buildMap();

	// Method to read pairs from test pairs file and print out shortest path
	bool loadPairs(const char * in_file, ofstream & out, bool weighted);

	// Helper method to BFS traverse graph and find closest path
	void findShortestPath(vector<std::string> & start,vector<std::string> & end,
							ofstream & out, bool weighted);

};

#endif // ACTORGRAPH_HPP

/** BELOW IS EXTRA DO NOT UNCOMMENT */

/* Helper method to binary search for given edge in movie list 
*/
//	unsigned int bSearchEdge(ActorEdge * item);
/** Return the pointer to the edge if the given item is found*/
//	ActorEdge * findEdge(ActorEdge * item);
	
/** Insert item into sorted position based on binary search*/
//	bool insertEdge(ActorEdge * item);
