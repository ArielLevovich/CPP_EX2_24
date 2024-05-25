#include <vector>
#include <string>
#include <iostream>
#include "Graph.hpp"
#include <limits.h>
#include <queue>
#include <algorithm>
#include <sstream>
#include <limits>
#include "Algorithms.hpp"
#include "NegativeCycleException.hpp"

using namespace std;
namespace ariel {
    void Algorithms::dfs(const Graph g, int v, vector<bool>& visited) {
        visited[v] = true;
        for (unsigned int i = 0; i < g.getVertices(); ++i) {
            if (g.getAdjMatrix()[v][i] != 0 && !visited[i]) {
                dfs(g, i, visited);
            }
        }
    }

    bool Algorithms::isConnected(const Graph g) {
        if (g.getVertices() == 0) return true; // An empty graph is trivially connected

        vector<bool> visited(g.getVertices(), false);
        dfs(g, 0, visited); // Start DFS from vertex 0

        for (bool visit : visited) {
            if (!visit) return false; // If any vertex is not visited, the graph is not connected
        }
        return true;
    }

    
    /**
     * helper function for isContainsCycle
     * Utility function to perform DFS and detect cycles in a graph.
     * 
     * @param g The graph on which the DFS and cycle detection are performed. It is passed by reference to avoid copying.
     * @param v The current vertex being visited in the DFS traversal.
     * @param visited A reference to a vector of boolean values indicating whether each vertex has been visited.
     * @param parent A reference to a vector of integers representing the parent vertices in the DFS tree. This helps in backtracking to print the cycle.
     * @param recStack A reference to a vector of boolean values that keeps track of vertices currently in the recursion stack. This helps identify back edges, which indicate cycles.
     * 
     * @return true if a cycle is detected involving the current vertex, otherwise false.
     * also , this function should print one cycle (in the case of more then 1 cycle), or "no cycle detected" if there's no cycle.
     
        
        * Explanation of the Logic:

        1. **Initialization**: Each vertex starts as unvisited. As `detectCycleUtil` progresses, vertices are marked as visited and added to the recursion stack. The recursion stack is used to keep track of the path of the DFS traversal, which helps in identifying cycles.

        2. **Cycle Detection**:
        - **Unvisited Adjacent Vertex**: If an adjacent vertex hasn't been visited, the function recurses with this new vertex, continuing the DFS. If a cycle is found in the recursion, it bubbles up the call stack, indicating the presence of a cycle.
        - **Vertex in Recursion Stack**: If an adjacent vertex is already in the recursion stack, it indicates that we've encountered a cycle, as we've found a way back to an earlier vertex in the current DFS path. This backtracking process then allows for printing the cycle path by following parent links back to the start of the cycle.

        3. **Cycle Printing**: The printing of the cycle is done by backtracking from the current vertex to the start of the cycle using the `parent` array. This prints a sequence of vertices that forms the cycle, showcasing the loop within the graph structure.

        4. **End of Function**: After checking all adjacent vertices, the current vertex is removed from the recursion stack (indicating that all connections from this vertex have been fully explored), and the function returns `false` if no cycles involving the current vertex were found during its exploration.
        
    */
    bool Algorithms::detectCycleUtil(const Graph g, unsigned int v, vector<bool>& visited, vector<int>& parent, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (unsigned int i = 0; i < g.getVertices(); ++i) {
            if (g.getAdjMatrix()[v][i] != 0) {  // There's an edge from v to i
                if (!visited[i]) {
                    parent[i] = v;  // Set the parent before diving deeper
                    if (detectCycleUtil(g, i, visited, parent, recStack)) {
                        return true;
                    }
                } else if (recStack[i]) {
                    // Cycle detected, backtrack to print the cycle
                    cout << "Cycle: ";
                    vector<int> cyclePath;
                    for (unsigned int current = v; current != i; current = parent[current]) {
                        cyclePath.push_back(current);
                    }
                    cyclePath.push_back(i);  // Add the starting node to complete the cycle
                    cyclePath.push_back(v);  // Show the cycle closes back to the starting vertex
                    reverse(cyclePath.begin(), cyclePath.end());

                    for (long unsigned int j = 0; j < cyclePath.size(); j++) {
                        cout << cyclePath[j] << (j < (cyclePath.size() - 1)? "->" : "");
                    }
                    cout << endl;
                    return true;
                }
            }
        }
        recStack[v] = false;  // Unmark v from recursion stack after exploring all adjacent vertices
        return false;
    }   

    bool Algorithms::isContainsCycle(const Graph g) {        
        vector<int> path;
        bool result = isContainsCycleInternal(g, path);
        if (result) {
            printCycle(path);
        } else {
            cout << "Graph doesn't contain a cycle" << endl;            
        }
        return result;
    }

    bool Algorithms::isContainsCycleInternal(const Graph g, vector<int>& path) {
        if (g.isDirected()) {
            return isCyclicDirected(g, path);            
        }
        return isCyclicUndirected(g, path);
    }

    vector<int> Algorithms::bellmanFord(const Graph g, int src, int end) {
        int vertices = g.getVertices();
        vector<int> dist(vertices, INT_MAX);
        vector<int> parent(vertices, -1);

        dist[src] = 0; // Initialize the distance to the source
        vector<vector<int>> adj = g.getAdjMatrix();

        // Relax all edges |V| - 1 times     
        for (int i = 0; i < vertices - 1; ++i) {
            bool update = false;   
            for (int u = 0; u < vertices; ++u) {
                for (int v = 0; v < vertices; ++v) {
                    if (u == v || adj[u][v] == 0) continue;

                    if (v != src && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                        parent[v] = u;  
                        update = true;                  
                    }
                }
            }
            if (!update) break; // Early exit if no update in a whole pass
        }
        
        // Construct the path from src to end if reachable
        vector<int> path;
        if (dist[end] == INT_MAX) return path; // Return empty if no path

        for (int at = end; at != -1 && path.size() < (size_t)vertices; at = parent[at]) {
            path.push_back(at);
            if (at == src) break;
        }

        reverse(path.begin(), path.end());

        // Now check for negative-weight cycles only on the path from src to dest
        if (!path.empty() && dist[path.back()] != INT_MAX) {
            // for directed graphs, examine also the edge bringing back to the source vertice.
            size_t last = g.isDirected() ? path.size() : path.size()-1;
            for (size_t i = 0; i < last; ++i) {
                int u = path[i];
                int v = path[(i + 1) % path.size()];
                if (g.getAdjMatrix()[u][v] != 0 && dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {                 
                    throw NegativeCycleException("The graph contains a negative weight cycle.");
                }
            }
        }

        return path;
    }       

    std::string Algorithms::shortestPath(const Graph g, int src, int dest) {
        try {
            vector<int> path = bellmanFord(g, src, dest);
            if (path.empty()) {
                return "No path from source to destination.";
            }

            stringstream ss;
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) ss << "->";
                ss << path[i];
            }
            return ss.str();
        } catch (const NegativeCycleException& e) {
            return e.what();  // Return the error message if a negative cycle is detected
        }
    }

    /*
    Using BFS: Start from any unvisited vertex and assign it a color (say, red). 
    All its neighbors are given the opposite color (say, blue). 
    Continue the process for all neighbors and their respective neighbors.
    If at any point a neighbor has the same color as the current vertex, then the graph is not bipartite.
    */
    std::string Algorithms::isBipartite(const Graph& graph) {
        vector<int> color(graph.getVertices(), -1);  // Color array to store colors assigned to vertices
        queue<int> q;  // Queue for BFS
        // bool flag = true;

        // Check all vertices since graph might be disconnected
        for (unsigned int src = 0; src < graph.getVertices(); ++src) {
            if (color[src] == -1) {  // If not colored
                color[src] = 0;  // Start coloring with 0
                q.push(src);

                while (!q.empty()) {
                    unsigned int u = q.front();
                    q.pop();

                    // Check self loop
                    if (graph.getAdjMatrix()[u][u] != 0) {
                        //flag = false;
                    }
                    for (unsigned int v = 0; v < graph.getVertices(); ++v) {
                        if (graph.getAdjMatrix()[u][v] && v != u) {
                            if (color[v] == -1) {  // If v is not colored
                                color[v] = 1 - color[u];  // Assign alternate color
                                q.push(v);                            
                            } else if (color[v] == color[u]) { // If adjacent nodes have same color
                                return "The graph is not bipartite.";
                            }
                        }
                    }
                }
            }
        }
         
        string groupA = "A={";
        string groupB = "B={";
        bool firstA = true;
        bool firstB = true;

        // Ensure no syntax errors before the loop
        for (unsigned int k = 0; k < graph.getVertices(); ++k) {
            if (color[k] == 0) {
                if (!firstA){
                    groupA += ", ";
                } 
                groupA += to_string(k);
                firstA = false;
            } else {
                if (!firstB){
                    groupB += ", ";
                } 
                groupB += to_string(k);
                firstB = false;
            }
        }
        groupA += "}";
        groupB += "}";

        return "The graph is bipartite: " + groupA + ", " + groupB;
    }    

    // A recursive function that
    // uses visited[] and parent to detect
    // cycle in subgraph reachable
    // from vertex v.
    bool Algorithms::isCyclicUtilUndirected(const Graph g, unsigned int v, bool visited[], int parent, vector<int>& path)
    {
        vector<vector<int>> adj = g.getAdjMatrix();
        // Mark the current node as visited
        visited[v] = true;
    
        // Recur for all the vertices
        // adjacent to this vertex
        for (unsigned int i = 0; i < g.getVertices(); i++) {
            if (i == v || adj[v][i] == 0) continue;
            
            // If an adjacent vertex is not visited,
            // then recur for that adjacent
            if (!visited[i]) {    
                path.push_back(v);            
                if (isCyclicUtilUndirected(g, i, visited, v, path))
                    return true;
            }
    
            // If an adjacent vertex is visited and
            // is not parent of current vertex,
            // then there exists a cycle in the graph.
            else if ((signed int)i != parent) {
                // remove all the vertices from the "path" till the first appearance of "i"
                removeAllTheVerticesFromPathTillI(path, i);                
                // add the parent 'v' and its child node 'i'.
                path.push_back(v);
                path.push_back(i);
                return true;
            }
        }
        path.clear();
        return false;
    }
    
    // Returns true if the undirected graph contains
    // a cycle, else false.
    bool Algorithms::isCyclicUndirected(const Graph g, vector<int>& path)
    {
        bool result = false;
        unsigned int V = g.getVertices();
        // Mark all the vertices as not
        // visited and not part of recursion
        // stack
        bool* visited = new bool[V];
        for (unsigned int i = 0; i < V; i++)
            visited[i] = false;
    
        // Call the recursive helper
        // function to detect cycle in different
        // DFS trees
        for (unsigned int u = 0; u < V; u++) {
            path.clear();
            // Don't recur for u if
            // it is already visited
            if (!visited[u]) {
                if (isCyclicUtilUndirected(g, u, visited, -1, path)) {
                    result = true;
                    break;
                }                
            }
        }        
        delete[] visited;
        return result;
    } 
    // DFS function to find if a cycle exists
    bool Algorithms::isCyclicUtilDirected(const Graph g, unsigned int v, bool visited[], bool* recStack, vector<int>& path)
    {
        vector<vector<int>> adj = g.getAdjMatrix();
        if (visited[v] == false) {
            // Mark the current node as visited
            // and part of recursion stack
            visited[v] = true;
            recStack[v] = true;
    
            // Recur for all the vertices adjacent to this
            // vertex
            for (unsigned int i = 0; i < g.getVertices(); i++) {
                if (i == v || adj[v][i] == 0) continue;
                if (path.empty() || (unsigned int)path.back() != v) {
                    path.push_back(v);
                }
                if (!visited[i] && isCyclicUtilDirected(g, i, visited, recStack, path))
                    return true;
                else if (recStack[i]) {
                    // remove all the vertices from the "path" till the first appearance of "i"
                    removeAllTheVerticesFromPathTillI(path, i); 
                    path.push_back(i);
                    return true;
                }
            }
        }
    
        // Remove the vertex from recursion stack
        recStack[v] = false;
        // we do not need to remove "v" from the 'path' - because in the next call the new instance of 'path' will be used.
        return false;
    }
    
    // Returns true if the graph contains a cycle, else false
    bool Algorithms::isCyclicDirected(const Graph g, vector<int>& path)
    {
        bool result = false;
        unsigned int V = g.getVertices();
        // Mark all the vertices as not visited
        // and not part of recursion stack
        bool* visited = new bool[V];
        bool* recStack = new bool[V];
        for (unsigned int i = 0; i < V; i++) {
            visited[i] = false;
            recStack[i] = false;
        }
    
        // Call the recursive helper function
        // to detect cycle in different DFS trees
        for (unsigned int i = 0; i < V; i++) {
            path.clear();
            if (!visited[i] && isCyclicUtilDirected(g, i, visited, recStack, path)) {                
                result = true;
                break;
            }
        }

        delete[] visited;
        delete[] recStack;
        if (!result) {
            path.clear();            
        }
        return result;
    }

    bool Algorithms::hasNegativeCycle(const Graph g) {
        bool result = false;   
        vector<int> path;
        if (isContainsCycleInternal(g, path) && g.hasNegativeWeight()) {
            unsigned int numOfVrtx = g.getVertices();
            for (unsigned int i = 0; i < numOfVrtx; i++) {
                for (unsigned int j = 0; j < numOfVrtx; j++) {
                    if (i == j) continue;
                    try {
                        vector<int> path = bellmanFord(g, i, j);                
                    } catch (const NegativeCycleException& e) {
                        cout << e.what() << endl;
                        result = true;
                    }            
                    if (result) break;
                }
                if (result) break;
            }
        }
        if (!result) {
            cout << "Graph doesn't contain a negative cycle" << endl;
        }
        return result;
    }   

    void Algorithms::printCycle(vector<int>& path) {
        // cout << "Graph contains the cycle:" << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i != path.size() - 1) {
                std::cout << "->";
            }
        }
        std::cout << std::endl;  // For a new line at the end
    }

    void Algorithms::removeAllTheVerticesFromPathTillI(vector<int>& path, unsigned int i) {
        auto it = std::find(path.begin(), path.end(), i);
        if (it != path.end()) {                    
            path.erase(path.begin(), it);
        }
    }
} 