/* Description: Questions to answer about Six Degrees of
 * Kevin Bacon
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: Jun 01, 2019
 * Sources: Piazza
 */

 1. To verify an undirected graph is connected, do a BFS traversal starting
 from any node using either a queue. If the current examined node 
 hasn't already been visited, set it to visited and schedule its neighbors on 
 the queue to be explored. Eventually, when the queue is empty, 
 iterate through a list containing each node in the graph and check if their 
 'visited' field is set to true. If all the nodes have been visited, then 
 the graph is connected. If not, that means there was some node that couldn't be
 reached, which violates the definition of 'connectedness'. The time complexity
 of this algorithm is the complexity of BFS which is O(V+E), as well as the
 time to verify all the nodes are visited, O(V). Hence, the total runtime is
 O(V+E+V) = O(2V + E) which is still O(V+E).
 
 2. Initially set all vertices in the graph as not visited, then iterate through
 all the nodes and start DFS traversal from the first unvisited node, then 
 increment the count of number of connected components by one. Do this until 
 all nodes are visited, and count should be the correct number of connected
 components. The runtime of this algorithm is the runtime of DFS, O(E+V).

 3. To verify the claim of 'Six Degrees of Kevin Bacon', we simply have to begin
 a BFS traversal starting at the node representing Kevin Bacon. First, search 
 for this node in a list of all the graph nodes, set the distance of this node
 to 0, set every other distance to INF and then start the BFS traversal. 
 For each unvisited node that is popped from the queue, set the distance of 
 its neighbors to previous distance + 1. Once the algorithm finishes, 
 iterate through a list of all the nodes in the graph and check their distance 
 values. Since the graph is connected, all the actors nodes should have been
 visited, and all the distance values should be set. If all the node distances
 are between [0, 6], and there are no nodes with distance Infinity, which would
 indicate a disconnected edge, then we have successfully verified the theory of
 'Six Degrees of Kevin Bacon'. Overall, the runtime of this algorithm would 
 be the same as in the first question. It would take O(V+E) time to BFS 
 traverse the whole graph starting from Kevin Bacon, and then O(V) time to 
 verify each vertex's distance. In total, this would take O(V+E) time. 

