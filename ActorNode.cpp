/* Description: This program defines each actor in a graph of actors
 * and the movies they collectively acted in.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

#include "ActorEdge.hpp"
#include "ActorNode.hpp"

using namespace std;

// Constructor for ActorNode, initializes member variables
ActorNode::ActorNode(std::string nameInput) : name(nameInput), 
												isVisited(false) {}

// Add edge and neighbor to movies list
void ActorNode::addNeighbor(ActorEdge * edgeIn, ActorNode * neighbor) {
	// Create new branch
	branch newBranch = std::make_pair(edgeIn, neighbor);

	// Add to list
	adjEdges.push(newBranch);
}

/**
* Helper method to binary search for given movie in movie list 
*/
unsigned int ActorNode::bSearchMovie(std::string item) {
	// Get low and high of vector
	unsigned int lowInd = 0;
	unsigned int highInd = movieList.size()-1;
	unsigned int middle = 0;

	// Get mid value and narrow down array by half
	while (lowInd <= highInd) {
		// Halve the array each time and search subarray
		middle = ((highInd - lowInd)/2)+lowInd;
		// Return index if found
		if (item.compare(movieList[middle]) == 0) {
			return middle;
		}
	}
	// Return where the element should be if not found
	return lowInd;
} 

/** Return true if found*/
bool ActorNode::findMovie(std::string item) {
	// Search correct index for item
	unsigned int index = bSearchMovie(item);
		
	// If found, return true
	if (movieList[index].compare(item) == 0) {
		return true;
	}
	return false;
}
	
/** Insert item into sorted position */
bool ActorNode::insertMovie(std::string item) {
	// If array is empty, simply push to array
	if (!movieList.size()) {
		movieList.push_back(item);
		return true;
	}
	// Search correct index for item
	unsigned int index = bSearchMovie(item);

	// Create a new iterator for v
	vector<std::string>::iterator itr = movieList.begin();
		
	// If already exists, return false
	if (movieList[index].compare(item) == 0) {
		return false;
	}

	// Traverse to correct index
	advance(itr, index);
	
	// Insert node
	movieList.insert(itr, item);
	
	// return true
	return true;
}
