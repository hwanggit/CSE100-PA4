/* FileName: ActorGraph.cpp
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
#include <queue>
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
unsigned int ActorGraph::bSearchActor(ActorNode * item, 
										vector <ActorNode *> & list) {
	// Get low and high of vector
	int lowInd = 0;
	int highInd = list.size()-1;
	int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
	
		// Check if equals
		int compare = item->checkEqual(list[middle]);

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

/** Return the pointer to the actor */
ActorNode * ActorGraph::findActor(ActorNode * item) {
	// Search correct index for item
	unsigned int index = bSearchActor(item, actors);
	
	// If index out of bounds, return false
	if (index < 0 || index >= actors.size()) {
		return nullptr;
	}
	
	// If found, return 
	if (!(actors[index]->checkEqual(item))) {
		return actors[index];
	}
	
	return nullptr;
}
	
/** Insert item into sorted position */
bool ActorGraph::insertActor(ActorNode * item, vector<ActorNode *> & list) {
	// If array is empty, simply push to array
	if (!list.size()) {
		list.push_back(item);
		return true;
	}
	
	// Search correct index for item
	unsigned int index = bSearchActor(item, list);

	// Create a new iterator for v
	vector<ActorNode *>::iterator itr = list.begin();
	
	// If found, return false 
	if (index >= 0 && index < list.size()) {
		if (!(list[index]->checkEqual(item))) {
			return false;
		}
	}
	
	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	list.insert(itr, item);
	
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
        int year = stoi(record[2]);
		string movie_and_year (record[1] + " " + record[2]);

		// If different actor, create new node and insert
		if (prevActor.compare(actor_name) != 0) {
			// Create new actor
			currNode = new ActorNode(actor_name);
			
			// Insert actor into list
			insertActor(currNode, actors);
		}
	
		// Add entry to movie_graph
		insertActor(currNode, movie_graph[movie_and_year]);
		year_graph[movie_and_year] = year;
		title_graph[movie_and_year] = movie_title;

		// Set previous actor name
		prevActor = actor_name;
	}

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    // Call helper method to build graph
	buildMap();

	// Close file and return
	infile.close();
	return true;
}

/* helper method to build tree from unordered map
 * PRECONDITION: loadFromFile has been called to initialize map
 */
void ActorGraph::buildMap() {	
	// Create nodes for all adjacent actors
	for( const auto & n : movie_graph ) {
		// Get list of actors for current movie
		vector <ActorNode *> currList = n.second;
		
		// Link each pair of actors using an edge
		for (unsigned int i=0; i<currList.size(); i++) {
			for (unsigned int j=i+1; j<currList.size(); j++) {
				// Create new edge and push to list of edges 
				ActorEdge * currEdge = new ActorEdge(title_graph[n.first], 
														year_graph[n.first], 
															currList[i], 
																currList[j]);
				// Push to list of accumulating edges
				edges.push_back(currEdge);

				// Add edge as neighbor of each linked node
				currList[i]->addNeighbor(currEdge);
				currList[j]->addNeighbor(currEdge);
					
			}
		}
	}
}

// Method to read pairs from test pairs file and print out shortest path
bool ActorGraph::loadPairs(const char * in_file, ofstream & out) {
	 // Initialize the file stream
    ifstream infile(in_file);

    bool have_header = false;
	
	// Define start and end vectors
	vector <std::string> start;
	vector <std::string> end;

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
    
        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }
		
		// Get the start and end search
        string start_q(record[0]);
        string end_q(record[1]);
		
		// Add to vectors
		start.push_back(start_q);
		end.push_back(end_q);
    }
	if (!infile.eof()) {
        cerr << "Failed to read " << in_file << "!\n";
		out.close();
        return false;
    }

	// Print header to outputfile
	out << "(actor)--[movie#@year]-->(actor)--...\n";

    // Call helper method to build graph
	findShortestPath(start, end, out);
	
	// Close file and return
	infile.close();
	return true;
}

// Helper method to BFS traverse graph and find closest path
void ActorGraph::findShortestPath(vector<std::string> & start, 
									vector<std::string> & end, ofstream & out) {
	// For each query, do a BFS search
	for (unsigned int i=0; i<start.size(); i++) {
		// Print computing statements
		cout << "Computing path for (" << start[i] << ") -> (" << end[i];
		cout << ")" << endl;
		
		// Initialize queue for BFS
		queue <ActorNode *> toExplore;

		// Create starting nodes for start and end 
		ActorNode * start_q = new ActorNode(start[i]);
		ActorNode * end_q = new ActorNode(end[i]);

		// Find starting point
		ActorNode * currBegin = findActor(start_q);
		
		// If not found, print failed
		if (currBegin == nullptr) {
			out << endl;
			cerr << "Failed to locate node '" << start[i] << "'" << endl;
			delete(start_q);
			delete(end_q);
			continue;
		}
		
		// To check if found
		bool checkFound = false;
		ActorNode * lastNode;

		// create new branch for start and push start to queue
		currBegin->isVisited = true;
		toExplore.push(currBegin);
		
		// While not empty, keep exploring
		while (!toExplore.empty()) {
			// Get first of queue
			ActorNode * next = toExplore.front();
			toExplore.pop();
			
			// Add neighbors to queue
			for (unsigned int k=0; k<(next->adjEdges).size(); k++) {
				// Set the previous node of adjacent edge
				ActorEdge * currEdge = next->adjEdges[k];

				// Get current neighbor of next
				ActorNode * currNeighbor;

				// Set neighbor
				if (next->checkEqual(currEdge->actor1) == 0) {
					currNeighbor = currEdge->actor2;
				}
				else {
					currNeighbor = currEdge->actor1;
				}
				
				// If not visited, set to visited, and push to queue
				if (currNeighbor->isVisited == false) {
					currNeighbor->isVisited = true;
					currNeighbor->prevEdge = currEdge;
					currEdge->prevNode = next;
					toExplore.push(currNeighbor);
				
					// If destination is found, empty queue and break
					if (end_q->checkEqual(currNeighbor) == 0) {
						// Empty queue
						while (!toExplore.empty()) {
							toExplore.pop();
						}
						// Set found flag to true
						checkFound = true;

						// Set last branch to found and set previous to next
						lastNode = currNeighbor;
						break;
					}	
				}
			}
		}
		
		// If not found, print failed
		if (!checkFound) {
			out << endl;
			cerr << "Failed to locate node '" << end[i] << "'" << endl;	
		}
		else {
			// Print path if found
			vector<ActorNode *> path;
			ActorNode * currBranch = lastNode;
			path.push_back(currBranch);
			
			// While the predecessor is not null, push
			while (currBranch->prevEdge != nullptr) {
				currBranch = currBranch->prevEdge->prevNode;
				path.push_back(currBranch);
			}

			// write path to output
			for (unsigned int h=path.size()-1; h>0; h--) {
				// If edge is not null, print edge
				if (path[h]->prevEdge != nullptr) {
					out << "--[";
					out << path[h]->prevEdge->movieName << "#@";
					out << path[h]->prevEdge->year << "]-->";
				}
				
				// Print node
				out << "(" << path[h]->name << ")";
			}
			
			// Print last node
			out << "--[";
			out << path[0]->prevEdge->movieName << "#@";
			out << path[0]->prevEdge->year << "]-->";
			
			// Print node
			out << "(" << path[0]->name << ")" << endl;
		}
	
		// Set all nodes to not visited
		for (unsigned int m=0; m<actors.size(); m++) {
			// Set previous to null
			actors[m]->prevEdge = nullptr;
			actors[m]->isVisited = false;
		}	
		for (unsigned int n=0; n<edges.size(); n++) {
			// Set all edges, and children nodes to nullptr
			edges[n]->prevNode = nullptr;
			edges[n]->actor1->prevEdge = nullptr;
			edges[n]->actor2->prevEdge = nullptr;
			
			// Set all linked visited flags to false
			edges[n]->actor1->isVisited = false;
			edges[n]->actor2->isVisited = false;
		}
		
		// Delete initial pointers, and newStart
		delete(start_q);
		delete(end_q);
	}

	// Close file stream
	out.close();
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
