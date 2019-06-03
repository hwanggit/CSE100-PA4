/* UcsdGraph.hpp
 * Author: Luhao Wang, luw055
 * Date:   05/25/19
 *
 * This is a program that defines a Ucsd Graph, that stores all
 * locations on campus and can be used to search for shortest
 * paths between locations
 */

#include <fstream>
#include <sstream>
#include <float.h>
#include <cmath>
#include <queue>
#include "UcsdNode.cpp"
#include "UcsdGraph.hpp"

#define HCONST 1 // Constant for heuristic function

using namespace std;

/**
 * Constructor of the Ucsd graph
 */ 
UcsdGraph::UcsdGraph(void) {}

/* Load the graph from a tab-delimited file of ucsd location relationships.
 * return true if file was loaded sucessfully, false otherwise
 */
bool UcsdGraph::loadFromFile(const char* in_filename, bool initialize){

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = true;
  
	// Define previous actor name, and node
	string prevUcsd = "";
	UcsdNode * currNode;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {

            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and 
			// put it in 'next'
            if (!getline( ss, next, ' ' )) break;

            record.push_back( next );
        }
		
		// Read 3 if initialize
		if (initialize) {
			if (record.size() != 3) {
				// we should have exactly 3 columns
				continue;
			}
		}
		else {
			if (record.size() != 2) {
				// we should have exactly 2 columns
				continue;
			}
		}

		// If initializing, get name, coordinates
		if (initialize) {
			// Get the name, x and y coordinate
			string name(record[0]);
			int x = stoi(record[1]);
			int y = stoi(record[2]);
			
			// Create new ucsd node and insert
			UcsdNode * location = new UcsdNode(name, x, y);

			// Put into graph
			ucsd_graph[name] = location;
		}
		else {
			// Get location1 and 2
			string location1(record[0]);
			string location2(record[1]);
				
			// Search for nodes at location 1 and 2
			UcsdNode * node1 = ucsd_graph[location1];
			UcsdNode * node2 = ucsd_graph[location2];
			
			// Add neighbors to both
			node1->neighbors.push_back(node2);
			node2->neighbors.push_back(node1);
		}
	}

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

	// Close file and return
	infile.close();
	return true;
}

// Method to read pairs from test pairs file and print out shortest path
bool UcsdGraph::loadPairs(const char * in_file, ofstream & out){
	 // Initialize the file stream
    ifstream infile(in_file);

    bool have_header = true;
	
	// Define start and end vectors
	vector <std::string> start;
	vector <std::string> end;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {

            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and 
			// put it in 'next'
            if (!getline( ss, next, ' ' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }
		
		// Get the start and end search
        string start_q(record[0]);
        string end_q(record[1]);
		
		// Add to vectors
		start.push_back(start_q);
		end.push_back(end_q);
    }
	if (!infile.eof()) {
        cerr << "Failed to read " << in_file << "!\n";
		out.close();
        return false;
    }

    // Call helper method to build graph
	findShortestPath(start, end, out);
	
	// Close file and return
	infile.close();
	return true;
}

// Helper method to BFS traverse graph and find closest path
void UcsdGraph::findShortestPath(vector<std::string> & start, 
									vector<std::string> & end, ofstream & out){
	// For each query, do a BFS search
	for (unsigned int i=0; i<start.size(); i++) {
	
		// Reset all nodes
		for( const auto & n : ucsd_graph ) {
			// Get current node
			UcsdNode * currNode = ucsd_graph[n.first];
			currNode->isVisited = false;
			currNode->distance = DBL_MAX;
			currNode->prevNode = nullptr;
		}
		
		// Print computing statements
		cout << "Computing path for (" << start[i] << ") -> (" << end[i];
		cout << ")" << endl;
		
		// Create starting nodes for start and end 
		UcsdNode * currBegin = ucsd_graph[start[i]];
		UcsdNode * end_q = ucsd_graph[end[i]];
		
		// If not found, print failed
		if (currBegin == nullptr) {
			out << endl;
			cerr << "Failed to locate node '" << start[i] << "'" << endl;
			continue;
		}
		
		// To check if found
		bool checkFound = false;
		UcsdNode * lastNode;
	
		// Initialize queue for BFS
		priority_queue<UcsdNode *, vector<UcsdNode *>, compareNode> explore;
		
		// create new branch for start and push start to queue
		currBegin->distance = 0;
		currBegin->queueVal = 0;

		// Create node pair and push to queue
		explore.push(currBegin);
		
		// While not empty, keep exploring
		while (!explore.empty()) {
			// Get first of queue
			UcsdNode * next = explore.top();
			explore.pop();
			
			// If destination is found, break
			if (end_q->checkEqual(next) == 0) {
				// Set found flag to true
				checkFound = true;
				
				// Set last branch to found and set previous to next
				lastNode = next;
				break;
			}		
			
			// If next not visited, set visited
			if (next->isVisited == false) {
				// Set done to true
				next->isVisited = true;

				// Add neighbors to queue
				for (unsigned int k=0; k<(next->neighbors).size(); k++) {
					// Get current neighbor of next
					UcsdNode * currNeighbor = next->neighbors[k];
	
					// Get distance to w through next
					double dist_to_adj = next->distance + 
											heuristic(next, currNeighbor, 1);
					
					// If c is less than currNeighbor's distance, enqueue
					if (dist_to_adj < (currNeighbor->distance)) {
						currNeighbor->prevNode = next;
						
						// Calculate heuristic
						double h_x = heuristic(currNeighbor, end_q, HCONST);
						
						// Set neighbor's distance
						currNeighbor->distance = dist_to_adj;

						// Set queueVal
						currNeighbor->queueVal = dist_to_adj + h_x;

						// Create node pair to push
						explore.push(currNeighbor);						
					}
				}
			}
		}	
	
		// If not found, print failed
		if (!checkFound) {
			out << endl;
			cerr << "Failed to locate node '" << end[i] << "'" << endl;	
		}
		else {
			// Print path if found
			vector<UcsdNode *> path;
			UcsdNode * currBranch = lastNode;
			path.push_back(currBranch);
			
			// While the predecessor is not null, push
			while (currBranch->prevNode != nullptr) {
				currBranch = currBranch->prevNode;
				path.push_back(currBranch);
			}

			// write path to output
			for (unsigned int h=path.size()-1; h>0; h--) {
				// Print node
				out << "(" << path[h]->name << ")-->";
			}
			
			// Print node
			out << "(" << path[0]->name << ")" << endl;
		}
	}

	// Close file stream
	out.close();
}

// Heuristic function to calculate distance bewteen two nodes
double UcsdGraph::heuristic(UcsdNode * node1, UcsdNode * node2, int constant) {
	// Get the square difference between coordinates
	double squareDiffX = std::pow((node2->xCoord - node1->xCoord), 2);	
	double squareDiffY = std::pow((node2->yCoord - node1->yCoord), 2);

	// Return square root of sum multiply by constant
	return constant * std::sqrt(squareDiffX + squareDiffY);
}

/* Desctructor for actorGraph*/
UcsdGraph::~UcsdGraph() {
	// Delete all locations
	for( const auto & n : ucsd_graph ) {
		delete (ucsd_graph[n.first]);
	}
}
