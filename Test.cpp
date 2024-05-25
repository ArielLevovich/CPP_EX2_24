#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition1")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]\n");    
}

TEST_CASE("Test graph multiplication2")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]\n");    
}

TEST_CASE("Invalid operations3")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    g2.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Test graph multiplication4")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 1, 0}};
    CHECK(g4.printGraph() == "[0, 1, 0]\n[1, 0, 0]\n[0, 1, 0]\n");
}

TEST_CASE("5 - Test graph prefix increment, equality and unary +")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ++g1;
    auto g2 = +g1;
        
    vector<vector<int>> expectedGraph = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    ariel::Graph g3;
    g3.loadGraph(expectedGraph);
    bool result = g2 == g3;
    CHECK(result == true);    
}

TEST_CASE("6 - Test graph postfix increment, equality and unary -")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    auto g2 = g1++;
            
    vector<vector<int>> expectedGraph = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    ariel::Graph g3;
    g3.loadGraph(expectedGraph);
    bool result = g2 == g3;
    CHECK(result == true);    

    auto g4 = -g2;
    vector<vector<int>> expectedGraph2 = {
        {-1, -2, -1},
        {-2, -1, -2},
        {-1, -2, -1}};
    ariel::Graph g5;
    g5.loadGraph(expectedGraph2);
    bool result2 = g4 == g5;
    CHECK(result2 == true); 
}

TEST_CASE("7 - Test graph +=, -=, g1-g2")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    auto g2 = g1++;

    g1 += g2;            
    vector<vector<int>> expectedGraph = {
        {1, 3, 1},
        {3, 1, 3},
        {1, 3, 1}};
    ariel::Graph g3;
    g3.loadGraph(expectedGraph);
    bool result = g1 == g3;
    CHECK(result == true);    

    auto g4 = g2 - g1;
    g2 -= g1;    
    bool result2 = g2 == g4;
    CHECK(result2 == true); 
}

TEST_CASE("8 - Test graph >, <, !=")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    ariel::Graph g2;
    g2.loadGraph(graph2);
    CHECK((g1 < g2) == true); 

    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    ariel::Graph g3;
    g3.loadGraph(graph3);    
    CHECK((g1 > g3) == true);       
    
    auto g4 = g1 + g2;
    CHECK((g4 != g2) == true);
    CHECK((g4 != g1) == true);
    CHECK((g4 != g3) == true);
}

TEST_CASE("9 - Test graph >=, <=")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    ariel::Graph g2;
    g2.loadGraph(graph2);
    CHECK((g1 <= g2) == true); 

    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    ariel::Graph g3;
    g3.loadGraph(graph3);    
    CHECK((g1 >= g3) == true);       
    
    auto g4 = +g1;
    auto g5 = -g2;
    CHECK((g4 >= g1) == true);
    CHECK((g4 <= g1) == true);
    CHECK((g5 <= g2) == false);
    CHECK((g5 >= g2) == false);
}

TEST_CASE("10 - Test graph prefix decrement")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}};
    g1.loadGraph(graph);
    --g1;
    CHECK(g1.printGraph() == "[-1, 1, 2]\n[1, -1, 3]\n[2, 3, -1]\n");    
}

TEST_CASE("11 - Test graph postfix decrement")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g1.loadGraph(graph);
    auto g2 = g1--;            
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]\n");
}

TEST_CASE("12 - Test graph operator* (scalar)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(graph);
    auto g2 = g1*13;            
    CHECK(g2.printGraph() == "[0, 13, 13]\n[13, 0, 13]\n[13, 13, 0]\n");
}

TEST_CASE("13 - Test graph operator*= (scalar)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(graph);
    g1*=13;            
    CHECK(g1.printGraph() == "[0, 13, 13]\n[13, 0, 13]\n[13, 13, 0]\n");
}

TEST_CASE("14 - Test graph operator/ (scalar)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 10, 10},
        {10, 0, 10},
        {10, 10, 0}};
    g1.loadGraph(graph);
    auto g2 = g1/2;            
    CHECK(g2.printGraph() == "[0, 5, 5]\n[5, 0, 5]\n[5, 5, 0]\n");
}

TEST_CASE("15 - Test graph operator/= (scalar)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 10, 10},
        {10, 0, 10},
        {10, 10, 0}};
    g1.loadGraph(graph);
    g1/=5;            
    CHECK(g1.printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]\n");
}

TEST_CASE("15 - Test graph operator/= (scalar)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 10, 10},
        {10, 0, 10},
        {10, 10, 0}};
    g1.loadGraph(graph);
    g1/=5;            
    CHECK(g1.printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]\n");
}

TEST_CASE("16 - has negative cycle before and after appying *-1 doesn't have it anymore")
{
    ariel::Graph g;
    const vector<vector<int>> graph6 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph6); 

    CHECK(ariel::Algorithms::hasNegativeCycle(g) == true); 
    g *= -1;
    CHECK(g.printGraph() == "[0, 0, 0, 0]\n[-4, 0, 6, 0]\n[0, 0, 0, -5]\n[0, 2, 0, 0]\n");
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == false); 
}

TEST_CASE("17 - 'g' is not connected before and after appying '++g' becomes connected")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    ++g;
    CHECK(ariel::Algorithms::isConnected(g) == true); 
}

TEST_CASE("18 - Test directed graph shortest path before and after adding another graph to the original one")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0},
        {4, 0, -1, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1->2->3");

    vector<vector<int>> graph2 = {
        {0, 0, 0, -1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    ariel::Graph g2;
    g2.loadGraph(graph2);
    g += g2;
    cout << g.printGraph();    
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1->0->3");
}

TEST_CASE("19 - graph is directed before and got undirected after")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},};

    g.loadGraph(graph); 

    CHECK(g.isDirected() == true);    

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},};

    g2.loadGraph(graph2);   
    g += g2;
    CHECK(g.isDirected() == false); 
}

TEST_CASE("20 - Test Undirected shortestPath - No Path Exists before and after applying '++g' the path exists.")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path from source to destination.");
    ++g;
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->4");
}
