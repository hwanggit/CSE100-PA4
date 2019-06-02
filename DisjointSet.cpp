/* Description: This program represents a disjoint set, which is a data storing
 * structure that can group data into sets and provide efficient search 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: June 01, 2019
 * Sources: Piazza
 */

#include "DisjointSet.hpp"

using namespace std;

// Constructor for Disjoint set
DisjointSet::DisjointSet(vector<ActorNode *> actors) {
	// Iterate through actors and make copy
	for (unsigned int i=0; i<actors.size(); i++) {
		actors[i]->parent = actors[i];
		parents[actors[i]->name] = actors[i];
		points[actors[i]->name] = actors[i];
	}
}

// Find the set of given item
ActorNode * DisjointSet::find(ActorNode * actor) {
	// Get the parent
	ActorNode * tempParent = actor->parent;

	// Recursively find parent
	if (actor->checkEqual(tempParent) == 0) {
		return tempParent;
	}

	// Implement path compression
	actor->parent = find(actor->parent);
	return actor->parent;
}

// Do Union of two sets 
bool DisjointSet::Union(std::string act1, std::string act2) {
	// Find both sets
	ActorNode * leaf1 = points[act1];
	ActorNode * leaf2 = points[act2];
		
	// Find parent
	ActorNode * parent1 = find(leaf1);
	ActorNode * parent2 = find(leaf2);
	
	// If they are equal, return
	if (parent1->checkEqual(parent2) == 0) {
		return false;
	}

	// The higher rank becomes parent of the other
	if (parent1->rank >= parent2->rank) {
		// Increment rank only if both sets have same rank
		parent1->rank = (parent1->rank == parent2->rank) ? 
							(parent1->rank + 1) : parent1->rank;
		parent2->parent = parent1;
		parents.erase(parent2->name);
	}
	// If parent1 rank smaller, set parent to parent2
	else {
		parent1->parent = parent2;
		parents.erase(parent1->name);
	}
	
	return true;
}

// Method to check when algorithm is finished
bool DisjointSet::checkFinished () {
	// If parents array has size 1, return true
	if (parents.size() == 1) {
		return true;
	}
	return false;
}
