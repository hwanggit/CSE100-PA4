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

using namespace std;

typedef std::pair <ActorEdge *, ActorNode *> branch; // Define a edge-node pair

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

	// Compare nodes
	bool equals(ActorNode * p1, ActorNode * p2);
};

/** The comparator used in sorting points based on edge weight*/
struct compareEdge {
    bool operator() (const branch & p1, const branch & p2) {
		return p1.first->year < p2.first->year;
	}
}
#endif // ACTORNODE_HPP
