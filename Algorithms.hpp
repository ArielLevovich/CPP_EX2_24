#include <string>
#include <vector> // Include for std::vector
#include <stack>
#include "Graph.hpp"

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

// using namespace ariel;
namespace ariel {
    class Algorithms {
        public:
            static bool isConnected(const Graph g); 
            static bool isContainsCycle(const Graph g); 
            static std::string shortestPath(const Graph g, int src, int dest); 
            static std::string isBipartite(const Graph& g); 
            static bool hasNegativeCycle(const Graph g);             
        private:
            static void dfs(const Graph g, int v, vector<bool>& visited);
            static bool detectCycleUtil(const Graph g, unsigned int v, vector<bool>& visited, vector<int>& parent, vector<bool>& recStack); 
            static vector<int> bellmanFord(const Graph g, int src, int end);
            static bool isCyclicUtilUndirected(const Graph g, unsigned int v, bool visited[], int parent, vector<int>& path);
            static bool isCyclicUndirected(const Graph g, vector<int>& path);
            static bool isCyclicUtilDirected(const Graph g, unsigned int v, bool visited[], bool* recStack, vector<int>& path);
            static bool isCyclicDirected(const Graph g, vector<int>& path);
            static bool isContainsCycleInternal(const Graph g, vector<int>& path);
            static void printCycle(vector<int>& path);
            static void removeAllTheVerticesFromPathTillI(vector<int>& path, unsigned int i);
    };  
} 

#endif // ALGORITHMS_HPP
