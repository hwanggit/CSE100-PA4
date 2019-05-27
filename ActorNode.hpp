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
	
	typedef std::pair <ActorEdge *, ActorNode *> branch; // Define a edge-node 
	
	/** The comparator used in sorting points based on edge weight*/
	struct compareEdge {
		bool operator() (const branch & p1, const branch & p2) {
			return p1.first < p2.first;
		}
	};

public:

	// Name of actor
    std::string name;
	
	// Determine if visited
	bool isVisited;

	// List of adjacent edge-actor pairs sorted by year
	priority_queue<branch, vector<branch>, compareEdge> adjEdges; 
	
	// Create a vector list of movie_year strings
	vector<std::string> movieList;

	// Constructor for ActorNode, initializes member variables
    ActorNode(std::string nameInput);
	
	// Adds a branch to the adjEdges of node
	void addNeighbor(ActorEdge * edgeIn, ActorNode * neighbor);

	/**
	 * Helper method to binary search for given movie in movie list 
	 */
	unsigned int bSearchMovie(std::string item);

	/** Return true if the given movie_year string is found*/
	bool findMovie(std::string item);
		
	/** Insert item into sorted position based on binary search*/
	bool insertMovie(std::string item);
	
	// Check if two nodes are equal
	int checkEqual(ActorNode * other);
};
#endif // ACTORNODE_HPP
