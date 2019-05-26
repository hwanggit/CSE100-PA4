/* Description: This program defines each edge in the actor-movie graph, 
 * actors are connected based on the common movies they acted in. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 25, 2019
 * Sources: Piazza
 */

using namespace std;

// Constructor for ActorEdge, initializes member variables
ActorEdge::ActorEdge(const char * name, int year, ActorNode * node1, 
						ActorNode * node2) : movieName(name), year(year) {
	// set actors to passed in variables
	actor1 = node1;
	actor2 = node2;
}
