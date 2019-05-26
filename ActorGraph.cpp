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
#include <vector>
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
	unsigned int lowInd = 0;
	unsigned int highInd = actors.size()-1;
	unsigned int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
		// Return index if found
		if (item == actors[middle]) {
			return middle;
		}
	}
	// Return where the element should be if not found
	return lowInd;
}

/**
* Helper method to binary search for given edge in movie list 
*/
unsigned int ActorGraph::bSearchMovie(ActorEdge * item) {
	// Get low and high of vector
	unsigned int lowInd = 0;
	unsigned int highInd = movies.size()-1;
	unsigned int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
		// Return index if found
		if (item == movies[middle]) {
			return middle;
		}
	}
	// Return where the element should be if not found
	return lowInd;
} 

/** Return the pointer to the actor */
ActorNode * ActorGraph::findActor(ActorNode * item) {
	// Search correct index for item
	unsigned int index = bSearchActor(item);
		
	// If not found, return 
	if (actors[index] == item) {
		return actors[index];
	}
	return nullptr;
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
		
	// If already exists, return false
	if (actors[index] == item) {
		return false;
	}

	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	actors.insert(itr, item);
	
	// return true
	return true;
}

/** Return the pointer to the edge*/
ActorEdge * ActorGraph::findMovie(ActorEdge * item) {
	// Search correct index for item
	unsigned int index = bSearchMovie(item);
		
	// If not found, return 
	if (movies[index] == item) {
		return movies[index];
	}
	return nullptr;
}
	
/** Insert item into sorted position */
bool ActorGraph::insertMovie(ActorEdge * item) {
	// If array is empty, simply push to array
	if (!movies.size()) {
		movies.push_back(item);
		return true;
	}
	// Search correct index for item
	unsigned int index = bSearchMovie(item);

	// Create a new iterator for v
	vector<ActorEdge *>::iterator itr = movies.begin();
		
	// If already exists, return false
	if (movies[index] == item) {
		return false;
	}

	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	movies.insert(itr, item);
	
	// return true
	return true;
}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
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

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // TODO: we have an actor/movie relationship, now what?
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* Desctructor for actorGraph*/
ActorGraph::~ActorGraph() {
	// Delete all actors and edges
	for (unsigned int i=0; i<actors.size(); i++) {
		delete (actors[i]);
	}

	// Delete all actors and edges
	for (unsigned int j=0; j<movies.size(); j++) {
		delete (movies[j]);
	}
}
