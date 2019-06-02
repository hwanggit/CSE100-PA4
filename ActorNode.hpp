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
#include <string>

class ActorEdge; // Define ActorEdge class

using namespace std;
	
/** A class, instances of which are nodes in an ActorGraph 
 * Member variables store the actor name, distance and previous
 * pointer
 */
class ActorNode {
	
public:

	// Name of actor
    std::string name;
	
	// Determine if visited
	bool isVisited;
	
	// Distance, used in Dijkstra's algorithm
	int distance;

	// Branch to previous edge-node, used in BFS
	ActorEdge * prevEdge;

	// Define adjacent edges and nodes, each entry is an edge-node pair
	vector<ActorEdge *> adjEdges;

	// Constructor for ActorNode, initializes member variables
    ActorNode(std::string nameInput);
	
	// Adds a branch to the adjEdges of node
	void addNeighbor(ActorEdge * edgeIn);

	// Check if two nodes are equal
	int checkEqual(ActorNode * other);
};
#endif // ACTORNODE_HPP

/* BELOW IS EXTRA DO NOT UNCOMMENT */

// List of adjacent edge-actor pairs sorted by year
//priority_queue<ActorEdge *, vector<ActorEdge *>, compareEdge> adjEdges; 
	

/** The comparator used in sorting points based on edge weight*/
/*	struct compareEdge {
	bool operator() (ActorEdge * p1, ActorEdge * p2) {
		return p1 < p2;
	}
};*/
