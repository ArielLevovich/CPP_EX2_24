### README for operators assignment - EX2 
### Ariel Levovich - 326535242

#### Overview
The `Graph` class encapsulates the functionality for representing and manipulating both directed and undirected graphs using adjacency matrices. It includes a comprehensive set of member functions for graph manipulation, along with overloaded operators that enhance ease of use and intuitive interaction with graph data.

#### Key Features
- **Graph Representation**: Utilizes adjacency matrices to store graph data, supporting both directed and undirected graph types.
- **Graph Properties**: Includes methods to check for symmetry (indicating undirected graphs), detect negative weights, and manage graph attributes like vertices count and edges.

#### Member Functions
- `isSymmetric()`: Checks if the adjacency matrix is symmetric, indicating the graph is undirected.
- `hasGraphNegativeWeight()`: Determines if any edge in the graph has a negative weight.
- `loadGraph(vector<vector<int>> mtr)`: Initializes the graph with the specified adjacency matrix, determining properties like directionality and weight characteristics.
- `printGraph()`: Returns a string representation of the adjacency matrix.
- `get/setVertices()`: Accessor and mutator for the number of vertices in the graph.
- `get/setAdjMatrix()`: Accessor and mutator for the adjacency matrix of the graph.
- `isDirected()`, `hasNegativeWeight()`, `getEdges()`: Provide information about graph properties.

#### Overloaded Operators
- **Arithmetic Operators**: `+`, `-`, `*`, `/` for graph addition, subtraction, multiplication by another graph or scalar, and division by a scalar, respectively.
- **Unary Operators**: Unary `+` and `-` for creating a positive copy of the graph and negating all edge weights.
- **Increment/Decrement**: `++` and `--` (both prefix and postfix) for incrementing or decrementing all edge weights by 1.
- **Comparison Operators**: `==`, `!=`, `<`, `>`, `<=`, `>=` to compare two graphs based on vertices, edges, or graph properties like directionality.

### Detailed Operator Implementations and Their Impact on Graph Algorithms

#### Operator Implementations

1. **Operator + (Addition of Graphs)**
   - **Implementation**: This operator adds corresponding elements of the adjacency matrices of two graphs. It assumes both graphs have the same number of vertices.
   - **Impact on Algorithms**: Adding two graphs can increase connectivity, potentially introducing new paths and decreasing the shortest path length between nodes.

2. **Operator * (Multiplication by a Scalar)**
   - **Implementation**: Multiplies every edge weight of the graph by a scalar value. This is straightforward as it applies the scalar multiplication to each entry in the adjacency matrix.
   - **Impact on Algorithms**: Multiplying by a positive scalar does not change the graph's structure but scaling by a negative value can invert the sign of weights, affecting algorithms that differentiate between positive and negative weights, like those checking for negative cycles.

3. **Operator - (Unary Negation)**
   - **Implementation**: Negates the weights of all edges in the graph. This is implemented by applying a unary minus to each element of the adjacency matrix.
   - **Impact on Algorithms**: Negating a graph can turn positive weight cycles into negative ones and vice versa, directly impacting algorithms like Bellman-Ford, which are used to detect negative cycles.

4. **Increment/Decrement Operators (++, --)**
   - **Implementation**: These operators increase or decrease every edge weight by 1. They can be applied in both prefix and postfix forms.
   - **Impact on Algorithms**: Incrementing or decrementing weights can affect the total weight of paths, potentially altering the outcomes of shortest path algorithms or changing the status of a graph from having no negative cycles to having them.

#### Example: Impact of Operators on Algorithms

Let's consider a more concrete example involving the decrement operator and its effect on a graph's connectivity and shortest path calculations:

**Original Graph (G):**
```
0 - 1 - 3
|       |
4       2
|       |
3 - 2 - 0
```
**Graph after applying the decrement operator (--G):**
```
-1 - 0 - 2
 |       |
 3       1
 |       |
 2 - 1 - -1
```

#### Scenario: Checking Connectivity and Shortest Path
- **Connectivity**: The original graph `G` might already be connected, but decrementing every edge by 1 could disconnect sections of the graph if any edge weight becomes zero, potentially isolating nodes.
- **Shortest Path**: Algorithms like Dijkstra's may no longer function correctly without modifications since they do not handle negative weights. However, the decrement operation may shorten the perceived distances between nodes, altering the output of shortest path calculations.

#### Test Case Example
```cpp
TEST_CASE("Graph Decrement Impact on Shortest Path") {
    ariel::Graph g;
    g.loadGraph({{0, 1, 3}, {1, 0, 2}, {3, 2, 0}});
    --g;
    ariel::Algorithms::shortestPath(g, 0, 2); // Check how the shortest path is affected
}
```
In this test, we would evaluate how the shortest path length changes after the graph is decremented. The decrement could lead to a negative cycle, which would fundamentally alter the results from shortest path algorithms like Floyd-Warshall or Bellman-Ford, which need to be employed instead of Dijkstra's in the presence of negative weights.

### Conclusion
Each operator within the `Graph` class has been carefully implemented to allow intuitive graph manipulations. These operators can significantly influence the behavior of graph algorithms, either enhancing capabilities, introducing limitations, or necessitating the use of different algorithms to accommodate changes in graph properties like edge weights and connectivity.
