/* Description: This program defines each edge in the actor-movie graph, 
 * actors are connected based on the common movies they acted in. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

#include "ActorNode.hpp"
#include "ActorEdge.hpp"

#define WEIGHTED 2019

using namespace std;

// Constructor for ActorEdge, initializes member variables
ActorEdge::ActorEdge(std::string name, int year, ActorNode * node1, 
						ActorNode * node2) : movieName(name), year(year){
	
	// Set weight of edge
	weight = 1 + (WEIGHTED - year);
	
	// set actors to passed in variables
	actor1 = node1;
	actor2 = node2;
	prevNode = nullptr;
}

/* BELOW IS EXTRA DO NOT UNCOMMENT */

// Check if two edges are equal
/*int ActorEdge::checkEqual(ActorEdge * other) {
	// Compare movie names
	int compareName = (this->movieName).compare(other->movieName);
	
	// Compare movie years
	int compareYear = 0;
	if ((this->year) > (other->year)) {
		compareYear = 1;
	}
	else if ((this->year) < (other->year)) {
		compareYear = -1;
	}
	else {
		compareYear = 0;
	}
	
	// Check if actors are the same
	int compareAct1 = actor1->checkEqual(other->actor1);
	int compareAct2 = actor2->checkEqual(other->actor2);
	
	// If crossed, change both to 0
	if (actor1->checkEqual(other->actor2) == 0 && 
			actor2->checkEqual(other->actor1) == 0) {
		compareAct1 = 0;
		compareAct2 = 0;
	}

	// Get the sum
	int returnVal;
	int sum = compareName + compareYear + compareAct1 + compareAct2;
	if (sum > 0) {
		returnVal = 1;
	}
	else if (sum < 0) {
		returnVal = -1;
	}
	else {
		returnVal = 0;
	}

	return returnVal;
}*/
