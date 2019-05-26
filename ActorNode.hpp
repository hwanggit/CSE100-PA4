/* Description: This program defines each actor in a tree of actors
 * and the movies they collectively acted in.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 24, 2019
 * Sources: Piazza
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <queue>
#include <utility>
#include <string.h>
#include "ActorEdge.hpp"

class ActorEdge; // Define Actor Edge class

using namespace std;

typedef std::pair <ActorEdge *, ActorNode *> branch; // Define a edge-node pair

/** The comparator used in sorting points based on edge weight*/
struct compareEdge {
	bool operator() (const branch & p1, const branch & p2) {
		return p1.first->year < p2.first->year;
	}
};

/** A class, instances of which are nodes in an ACTORTree. 
 * Member variables store the actor name, distance and previous
 * pointer
 */
class ActorNode {
public:
	// Name of actor
    char * name;
	
	// Determine if visited
	bool isVisited;

	// List of edges and corresponding actors
	priority_queue<branch, vector<branch>, compareEdge> movies; 
	
	// Constructor for ActorNode, initializes member variables
    ActorNode(const char * nameInput);

	// Add edge and neighbor to movies list
	void addNeighbor(ActorEdge * edgeIn, ActorNode * neighbor);

	// Check if two nodes are equal
	bool operator==(ActorNode * const & other) const {
		// Compare movie names
		int compareName = strcmp(this->name, other->name);
		
		// Return true if equal, else false
		if (compareName == 0)
			return true;

		return false;
	}
};
#endif // ACTORNODE_HPP