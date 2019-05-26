/* Description: This program defines each edge in the actor-movie graph, 
 * actors are connected based on the common movies they acted in. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "ActorNode.hpp"
#include <string.h>

class ActorNode; // Define ActorNode

using namespace std;

/** A class, instances of which are edges in an Actorgraph. 
 * Member variables store the movie name, year, and connected actors
 */
class ActorEdge {
public:
	// Name of actor
    char * movieName;

	// Name the year
	int year;
	
	// Pointers to two connected actors
	ActorNode * actor1;
	ActorNode * actor2;	
	
	// Constructor for ActorEdge, initializes member variables
    ActorEdge(const char * name, int year, ActorNode * node1, ActorNode *node2);

	// Check if two edges are equal
	bool operator==(ActorEdge * const & other) const {
		// Compare movie names
		int compareName = strcmp(this->movieName, other->movieName);
		
		// Compare movie years
		int compareYear = ((this->year) == (other->year)) ? 1 : 0;
		
		// Return true if equal, else false
		if ((compareName == 0) && compareYear)
			return true;

		return false;
	}
};
#endif // ACTOREDGE_HPP
