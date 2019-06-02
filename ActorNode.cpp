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
ActorNode::ActorNode(std::string nameInput) : name(nameInput),isVisited(false){
	rank = 0;
	distance = 0;
	prevEdge = nullptr;
	parent = nullptr;
}

// Add edge to movies list
void ActorNode::addNeighbor(ActorEdge * edgeIn) {
	// Add to list
	adjEdges.push_back(edgeIn);
}

// Check if two nodes are equal
int ActorNode::checkEqual(ActorNode * other) {
	// compare movie names
	int comparename = (this->name).compare(other->name);	
	return comparename;
}
