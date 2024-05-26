### README for operators assignment - EX2 
### Ariel Levovich - 326535242

#### Overview
The `Graph` class encapsulates functionality for representing and manipulating both directed and undirected graphs using adjacency matrices. It includes a comprehensive set of member functions for graph manipulation, along with overloaded operators that enhance ease of use and intuitive interaction with graph data.

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
- **Output Stream Operator (`<<`)**: Facilitates the output of the graph's adjacency matrix to a stream, enhancing readability and debugging capabilities.

#### Detailed Operator Implementations and Their Impact on Graph Algorithms

#### 1. Arithmetic Operators

- **Operator + (Addition of Graphs)**
  - **Implementation**: Adds corresponding elements from the adjacency matrices of two graphs. It ensures both graphs have the same number of vertices before performing addition.
  - **Code Example**:
    ```cpp
    Graph Graph::operator+(const Graph& other) const {
        if (this->getVertices() != other.getVertices()) {
            throw std::invalid_argument("Graphs must have the same number of vertices.");
        }
        vector<vector<int>> result = this->adjMatrix;
        for (unsigned int i = 0; i < this->getVertices(); i++) {
            for (unsigned int j = 0; j < this->getVertices(); j++) {
                result[i][j] += other.adjMatrix[i][j];
            }
        }
        Graph resultGraph;
        resultGraph.loadGraph(result);
        return resultGraph;
    }
    ```

- **Operator - (Subtraction of Graphs)**
  - **Implementation**: Subtracts elements of one graph's adjacency matrix from another's, provided they have the same vertex count.
  - **Code Example**:
    ```cpp
    Graph Graph::operator-(const Graph& other) const {
        if (this->getVertices() != other.getVertices()) {
            throw std::invalid_argument("Graphs must have the same number of vertices.");
        }
        vector<vector<int>> result = this->adjMatrix;
        for (unsigned int i = 0; i < this->getVertices(); i++) {
            for (unsigned int j = 0; j < this->getVertices(); j++) {
                result[i][j] -= other.adjMatrix[i][j];
            }
        }
        Graph resultGraph;
        resultGraph.loadGraph(result);
        return resultGraph;
    }
    ```

- **Operator * (Multiplication by a Scalar)**
  - **Implementation**: Multiplies each edge weight of the graph by a specified scalar.
  - **Code Example**:
    ```cpp
    Graph Graph::operator*(int scalar) const {
        vector<vector<int>> result = this->adjMatrix;
        for (unsigned int i = 0; i < this->getVertices(); i++) {
            for (unsigned int j = 0; j < this->getVertices(); j++) {
                result[i][j] *= scalar;
            }
        }
        Graph resultGraph;
        resultGraph.loadGraph(result);
        return resultGraph;
    }
    ```

- **Operator / (Division by a Scalar)**
  - **Implementation**: Divides each edge weight of the graph by a given scalar, ensuring not to divide by zero.
  - **Code Example**:
    ```cpp
    Graph Graph::operator/(int scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        vector<vector<int>> result = this->adjMatrix;
        for (unsigned int i = 0; i < this->getVertices(); i++) {
            for (unsigned int j = 0; j < this->getVertices(); j++) {
                result[i][j] /= scalar;
            }
        }
        Graph resultGraph;
        resultGraph.loadGraph(result);
        return resultGraph;
    }
    ```

#### 2. Unary Operators

- **Unary + (Positive Copy)**
  - **Implementation**: Returns an unchanged copy of the graph's adjacency matrix.
  - **Code Example**:
    ```cpp
    Graph Graph::operator+() const {
        return *this;  // Simply returns a copy of the current object
    }
    ```

- **Unary - (Negation)**
  - **Implementation**: Negates each edge weight in the graph.
  - **Code Example**:
    ```cpp
    Graph Graph::operator-() const {
        Graph result = *this;
        for (auto &row : result.adjMatrix) {
            for (auto &weight : row) {
                weight = -weight;
            }
        }
        return result;
    }
    ```

#### 3. Increment/Decrement Operators

- **Increment (++) and Decrement (--)**
  - **Implementation**: Both prefix and postfix forms increment or decrement every edge weight by 1.
  - **Prefix Code Example**:
    ```cpp
    Graph& Graph::operator++()
    {
        for (auto &row : this->adjMatrix) {
            for (auto &weight : row) {
                ++weight;
            }
        }
        return *this;
    }
    ```
  - **Postfix Code Example**:
    ```cpp
    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++(*this);
        return temp;
    }
    ```
  - The primary difference between prefix and postfix increment/decrement operators in C++ lies in the timing and the returned value. Prefix operators (`++g`, `--g`) modify the graph's edge weights before returning the modified object, allowing immediate use of the updated graph. In contrast, postfix operators (`g++`, `g--`) make a copy of the graph before modifying it, returning the original graph's state prior to modification, which is useful when the old value is needed temporarily.

#### 4. Comparison Operators

- **Equality (==) and Inequality (!=)**
  - **Implementation**: Compares graphs for equality based on their adjacency matrices.
  - **Code Example**:
    ```cpp
    bool Graph::operator==(const Graph& other) const {
        return this->adjMatrix == other.adjMatrix;
    }
    ```

- **Relational Operators (<, >, <=, >=)**
  - **Implementation**: Compares graphs based on properties such as the number of edges or vertices.
  - **Code Example**:
    ```cpp
    bool Graph::operator<(const Graph& other) const {
        if (this->getVertices() < other.getVertices()) return true;
        if (this->getVertices() == other.getVertices() && this->getEdges() < other.getEdges()) return true;
        return false;
    }
    ```

#### 5. Output Stream Operator (`<<`)

- **Implementation**: Facilitates the output of the graph's adjacency matrix to a stream, enhancing readability.
- **Code Example**:
  ```cpp
  std::ostream& operator<<(std::ostream& os, const Graph& graph) {
      for (const auto& row : graph.adjMatrix) {
          for (const auto& value : row) {
              os << value << " ";
          }
          os << std::endl;
      }
      return os;
  }
  ```
To illustrate how graph operators can influence important graph properties such as connectivity and bipartiteness, and how they might introduce negative cycles in graphs with weighted edges, here are a few detailed examples:

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
In this test, we would evaluate how the shortest path length changes after the graph is decremented. The decrement could lead to a negative cycle, which would fundamentally alter the results from shortest path algorithms like Floyd-Warshall or Bellman-Ford. (In the first assignment I implmented via Bellman- Ford).

### Example 1: Effect of the `+` Operator on Connectivity and Bipartiteness

#### Scenario
Suppose you have two separate graphs that each represent segments of a larger transportation network. Each graph has isolated components, and one of them is a bipartite graph.

#### Using the `+` Operator
By applying the `+` operator to combine these two graphs, we can observe the following effects:

- **Connectivity**: The addition of the two graphs can potentially connect previously isolated components, thereby enhancing the overall connectivity of the network. This could open up new routes between previously unreachable nodes.
  
- **Bipartiteness**: If one of the graphs is bipartite, adding another graph that does not maintain the bipartite structure (where vertices can be divided into two disjoint sets such that no two graph vertices within the same set are adjacent) could disrupt this property. The resulting graph after applying the `+` operator may no longer be bipartite if the added edges create odd cycles or connect vertices within the same set.

### Example 2: Creating a Negative Cycle with the `--` Postfix Decrement Operator

#### Scenario
Consider a graph where edges represent constraints or capacities, such as bandwidth in a network, and initially, all cycles have non-negative total weights.

#### Using the `--` Postfix Decrement Operator
By applying the `--` operator (postfix), which decrements the weight of each edge in the graph by one, we can induce significant changes:

- **Introduction of Negative Cycles**: If the graph initially has a cycle where the total weight sums to a small positive value, decrementing each edge's weight by one could reduce the total cycle weight to a negative number. For example, a cycle with three edges each weighted `1` would have a total weight of `3`. After applying `--`, each edge weight becomes `0`, and the total weight becomes `0`. If applied again, each edge weight becomes `-1`, leading to a cycle weight of `-3`, thus forming a negative cycle.
  
- **Impact on Algorithms**: The introduction of a negative cycle fundamentally changes the behavior of algorithms like Bellman-Ford, which is used for finding shortest paths. Normally, Bellman-Ford can handle negative weights but will fail or return an error if negative cycles are present, as they imply infinitely reducing path weights.

### Summary
These examples demonstrate how seemingly simple operations on graphs, like adding two graphs or decrementing edge weights, can have profound impacts on critical graph properties and the behavior of graph algorithms. They underline the importance of understanding the implications of graph operations. 
