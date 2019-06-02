/* Description: This program represents a disjoint set, which is a data storing
 * structure that can group data into sets and provide efficient search 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: June 01, 2019
 * Sources: Piazza
 */

#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

/* Disjoint set class, used to group nodes together and search for them
 * Has find and union methods
 */
class DisjointSet {
private:
	
	unordered_map<std::string, ActorNode*> parents; // Nodes at top of each tree
	unordered_map<std::string, ActorNode*> points; // List of each node in tree

public:
	// Constructor for Disjoint set
	DisjointSet(vector<ActorNode *> actors);

	// Find the set of given item
	ActorNode * find(ActorNode * actor);

	// Do Union of two sets 
	bool Union(std::string act1, std::string act2);
	
	// Method to check when algorithm is finished
	bool checkFinished();
};
#endif // DISJOINTSET_HPP
