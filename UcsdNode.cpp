/* Description: This program represents each node in a UcsdGraph,
 * containing locations on UCSD campus.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: June 02, 2019
 * Sources: Piazza
 */

#include "UcsdNode.hpp"

// Constructor for UcsdNode, initializes member variables
UcsdNode::UcsdNode(std::string nameInput, int x, int y) {
	name = nameInput;
	xCoord = x;
	yCoord = y;
	distance = 0;
	isVisited = false;
	prevNode = nullptr;
}

// Check if two nodes are equal
int UcsdNode::checkEqual(UcsdNode * other) {
	// compare movie names
	int comparename = (this->name).compare(other->name);	
	return comparename;
}
