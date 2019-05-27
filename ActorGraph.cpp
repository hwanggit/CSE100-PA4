/*
 * ActorGraph.cpp
 * Author: Luhao Wang, luw055
 * Date:   05/25/19
 *
 * This file is meant to exist as a container for starter code that you can use 
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify 
 * any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ActorNode.cpp"
#include "ActorEdge.cpp"
#include "ActorGraph.hpp"

using namespace std;

/**
 * Constructor of the Actor graph
 */ 
ActorGraph::ActorGraph(void) {}

/**
* Helper method to binary search for given node in actor list 
*/
unsigned int ActorGraph::bSearchActor(ActorNode * item) {
	// Get low and high of vector
	int lowInd = 0;
	int highInd = actors.size()-1;
	int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
	
		// Check if equals
		int compare = item->checkEqual(actors[middle]);

		// Return index if found
		if (compare < 0) {
			highInd = middle - 1;
		}
		else if (compare > 0) {
			lowInd = middle + 1;
		}
		else {
			return middle;
		}
	}
	// Return where the element should be if not found
	return lowInd;
}
	
/** Insert item into sorted position */
bool ActorGraph::insertActor(ActorNode * item) {
	// If array is empty, simply push to array
	if (!actors.size()) {
		actors.push_back(item);
		return true;
	}
	// Search correct index for item
	unsigned int index = bSearchActor(item);

	// Create a new iterator for v
	vector<ActorNode *>::iterator itr = actors.begin();
	
	// If found, return false 
	if (index >= 0 && index < actors.size()) {
		if (!(actors[index]->checkEqual(item))) {
			return false;
		}
	}
	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	actors.insert(itr, item);
	
	// return true
	return true;
}

/* Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year)
 *                      otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
	// Define previous actor name, and node
	string prevActor = "";
	ActorNode * currNode;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {

            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and 
			// put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }
		
		// Get the name, movie, year
        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
		string movie_and_year(record[1] + " " + record[2]);
	
		// If different actor, create new node and insert
		if (prevActor.compare(actor_name) != 0) {
			// Create new actor
			currNode = new ActorNode(actor_name);
			
			// Insert actor into list
			insertActor(currNode);
		}
	
		// Add entry to movie_graph
		movie_graph[movie_and_year].push_back(currNode);

		// Set previous actor name
		prevActor = actor_name;
	}

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
	
	// Create nodes for all adjacent actors
	for( const auto& n : movie_graph ) {
		// Get list of actors for current movie
		vector <ActorNode *> currList = n.second;
		
		// Link each pair of actors using an edge
		for (unsigned int i=0; i<currList.size(); i++) {
			for (unsigned int j=i+1; j<currList.size(); j++) {
				// Create new edge and push to list of edges 
				ActorEdge * currEdge = new ActorEdge(n.first, 0, currList[i], 
														currList[j]);
				// Push to list of accumulating edges
				edges.push_back(currEdge);

				// Add edge as neighbor of each linked node
				currList[i]->addNeighbor(currEdge, currList[j]);
				currList[j]->addNeighbor(currEdge, currList[i]);
			}
		}
	}

    return true;
}

/* Desctructor for actorGraph*/
ActorGraph::~ActorGraph() {
	// Delete all actors and edges
	for (unsigned int i=0; i<actors.size(); i++) {
		delete (actors[i]);
	}

	// Delete all actors and edges
	for (unsigned int j=0; j<edges.size(); j++) {
		delete (edges[j]);
	}
}

/* BELOW IS EXTRA DO NOT UNCOMMENT */

/**
* Helper method to binary search for given edge in movie list 
*/
/*unsigned int ActorGraph::bSearchEdge(ActorEdge * item) {
	// Get low and high of vector
	int lowInd = 0;
	int highInd = edges.size()-1;
	int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
		
		// Check if equal
		int compare = item->checkEqual(edges[middle]);

		// Return index if found
		if (compare < 0) {
			highInd = middle - 1;
		}
		else if (compare > 0) {
			lowInd = middle + 1;
		}
		else {
			return middle;
		}
	}
	// Return where the element should be if not found
	return lowInd;
} */

/** Return the pointer to the actor */
/*ActorNode * ActorGraph::findActor(ActorNode * item) {
	// Search correct index for item
	unsigned int index = bSearchActor(item);
	
	// If index out of bounds, return false
	if (index < 0 || index >= actors.size()) {
		return nullptr;
	}
	
	// If found, return 
	if (!(actors[index]->checkEqual(item))) {
		return actors[index];
	}
	return nullptr;
}*/

/** Return the pointer to the edge*/
/*ActorEdge * ActorGraph::findEdge(ActorEdge * item) {
	// Search correct index for item
	unsigned int index = bSearchEdge(item);

	// If index out of bounds, return false
	if (index < 0 || index >= edges.size()) {
		return nullptr;
	}

	// If not found, return 
	if (!(edges[index]->checkEqual(item))) {
		return edges[index];
	}
	return nullptr;
}*/
	
/** Insert item into sorted position */
/*bool ActorGraph::insertEdge(ActorEdge * item) {
	// If array is empty, simply push to array
	if (!edges.size()) {
		edges.push_back(item);
		return true;
	}
	// Search correct index for item
	unsigned int index = bSearchEdge(item);

	// Create a new iterator for v
	vector<ActorEdge *>::iterator itr = edges.begin();
		
	// If found, return false 
	if (index >= 0 && index < edges.size()) {
		if (!(edges[index]->checkEqual(item))) {
			return false;
		}
	}

	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	edges.insert(itr, item);
	
	// return true
	return true;
}*/
