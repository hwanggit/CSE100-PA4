/* Description: This program defines each node in a UcsdGraph, which
 * contains each location on UCSD campus, defined by coordinates
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 24, 2019
 * Sources: Piazza
 */

#ifndef UCSDNODE_HPP
#define UCSDNODE_HPP

#include <vector>
#include <string>

using namespace std;
	
/** A class, instances of which are nodes in an UcsdGraph 
 * Member variables store the name, coordinates, previous edges, etc.
 */
class UcsdNode {
	
public:

	// Name of location
    std::string name;

	// X and Y coordinates
	int xCoord; 
	int yCoord;

	// Neighbors list
	vector<UcsdNode *> neighbors;

	// Determine if visited
	bool isVisited;
	
	// Distance, used in A* algorithm
	double distance;

	// Branch to previous node, used in BFS
	UcsdNode * prevNode;
	
	// Constructor for UcsdNode, initializes member variables
    UcsdNode(std::string nameInput, int x, int y);
	
	// Check if two nodes are equal
	int checkEqual(UcsdNode * other);
};
#endif // UCSDNODE_HPP
