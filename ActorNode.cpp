/* Description: This program defines each actor in a graph of actors
 * and the movies they collectively acted in.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

#include <queue>
#include <utility>

using namespace std;

typedef std::pair <ActorEdge *, ActorNode *> branch; // Define a edge-node pair

// Constructor for ActorNode, initializes member variables
ActorNode::ActorNode(const char * nameInput) : name(nameInput), 
												isVisited(false) {}

// Add edge and neighbor to movies list
void ActorNode::addNeighbor(ActorEdge * edgeIn, ActorNode * neighbor) {
	// Create new branch
	branch newBranch = std::make_pair(edgeIn, neighbor);

	// Add to list
	movies.push(newBranch);
}
