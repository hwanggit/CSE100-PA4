/* Description: This program defines each actor in a graph of actors
 * and the movies they collectively acted in.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

#define <queue>

using namespace std;

typedef std::pair <ActorEdge *, ActorNode *> branch; // Define a edge-node pair

// Constructor for ActorNode, initializes member variables
ActorNode::ActorNode(char * nameInput) : name(nameInput) {}

// Add edge and neighbor to movies list
void ActorNode::addNeighbor(ActorEdge * edgeIn, ActorNode * neighbor) {
	// Create new branch
	branch newBranch = (edgeIn, neighbor);

	// Add to list
	movies.push(newBranch);
}
