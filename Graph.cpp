#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include "Graph.hpp"

using namespace std;

namespace ariel {
    bool Graph::isSymmetric(const vector<vector<int>> mtr){
        //function that checks if a matrix is symetric - means the graph is undirected.
        for (unsigned int i = 0; i < vertices; i++) {
            for (unsigned int j = 0; j < vertices; j++) { 
                if (mtr[i][j] != mtr[j][i]) {
                    return false; //means the graph is directed
                }
            }
        }
        return true;
    }
    bool Graph::hasGraphNegativeWeight(const vector<vector<int>> mtr) {
        for (unsigned int i = 0; i < vertices; i++) {
            for (unsigned int j = 0; j < vertices; j++) { 
                if (mtr[i][j] < 0) {
                    return true;
                }
            }
        }
        return false;
    }  
    void Graph::loadGraph(const vector<vector<int>> mtr) {
        vertices = mtr.size();
        isNegativeWeight = hasGraphNegativeWeight(mtr); 
        if(isSymmetric(mtr)){
            setAdjMatrix(mtr,false);  //if the matrix is symmetric , then set the bool isDirectedGraph = false
        }else{
            setAdjMatrix(mtr,true);
        }                
    }
    
    std::string Graph::printGraph() {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    // Getter for vertices
    unsigned int Graph::getVertices() const {
        return vertices;
    }

    // Setter for vertices,allowing setting vertices with adjustment to the adjacency matrix)
    void Graph::setVertices(unsigned int v) {
        if (v != vertices) {
            vertices = v;
            adjMatrix.resize(vertices);
            for (auto& row : adjMatrix) {
                row.resize(vertices, 0);
            }
        }else{
            vertices = v;
        }
    }

    // Getter for the adjacency matrix
    const vector<vector<int>> Graph::getAdjMatrix() const {
        return adjMatrix;
    }

    // Setter for the adjacency matrix
    void Graph::setAdjMatrix(const vector<vector<int>> graph, bool isDirectedGraph) {
        // Check if the matrix is square
        unsigned int rows = graph.size();
        for (const auto& row : graph) {
            if (row.size() != rows) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        this->adjMatrix = graph;
        this->isDirectedGraph = isDirectedGraph;
    }    
    
    bool Graph::isDirected() const {
        return isDirectedGraph;
    }

    bool Graph::hasNegativeWeight() const {
        return isNegativeWeight;
    }

    unsigned int Graph::getEdges() const {
        unsigned int numOfEdges = 0;
        unsigned int n = getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                numOfEdges++;
            }
        }

        if (!isDirected()) {
            numOfEdges /= 2;
        }
        return numOfEdges;
    }

    Graph Graph::operator+(const Graph& other) const {
        if(this->getVertices() != other.getVertices()) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");        
        }
        
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        vector<vector<int>> otherMtx = other.getAdjMatrix();
        unsigned int n = other.Graph::getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j] += otherMtx[i][j];
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;
    }

    Graph& Graph::operator+=(const Graph& other) {
        Graph sum = this->operator+(other);
        this->loadGraph(sum.getAdjMatrix());
        return *this;
    }

    Graph Graph::operator+() const {
        Graph result;
        result.loadGraph(this->getAdjMatrix()); 
        return result;
    }

    Graph Graph::operator-(const Graph& other) const {
        if(this->getVertices() != other.getVertices()) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");        
        }
        
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        vector<vector<int>> otherMtx = other.getAdjMatrix();
        unsigned int n = other.Graph::getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j] -= otherMtx[i][j];
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;
    }

    Graph& Graph::operator-=(const Graph& other) {
        Graph sum = this->operator-(other);
        this->loadGraph(sum.getAdjMatrix());
        return *this;
    }

    Graph Graph::operator-() const {
        return this->operator*(-1);
    }    

    bool Graph::operator==(const Graph& other) const {
        unsigned int n = this->getVertices();
        if(n != other.getVertices()) {
            return false;
        }
        
        vector<vector<int>> mtx = this->getAdjMatrix();        
        vector<vector<int>> otherMtx = other.getAdjMatrix();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                if (mtx[i][j] != otherMtx[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph& other) const {
        if (this->isIncludedIn(other)) {
            return true;
        }        

        if (!other.isIncludedIn(*this) && (*this != other)) {
            unsigned int edges = this->getEdges();
            unsigned int otherEdges = other.getEdges();
            if (edges < otherEdges) {
                return true;
            }
            if (edges == otherEdges && getVertices() < other.getVertices()) {
                return true;
            }
        }
        return false;
    }

    bool Graph::operator>(const Graph& other) const {
        return other < *this; // Reuse operator<
    }

    bool Graph::operator<=(const Graph& other) const {
        return (*this == other) || (*this < other);
    }

    bool Graph::operator>=(const Graph& other) const {
        return (*this == other) || (*this > other);
    }

    bool Graph::isIncludedIn(const Graph& other) const {
        unsigned int n = this->getVertices();
        if(n > other.getVertices() || *this == other) {
            return false;
        }
        
        vector<vector<int>> mtx = this->getAdjMatrix();        
        vector<vector<int>> otherMtx = other.getAdjMatrix();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                if (mtx[i][j] != 0 && mtx[i][j] != otherMtx[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    Graph& Graph::operator++() {
        Graph inc = this->operator++(1);
        this->loadGraph(inc.getAdjMatrix());
        return *this;
    }

    Graph Graph::operator++(int) {
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        unsigned int n = this->getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j]++;
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;    
    }
    
    Graph& Graph::operator--() {
        Graph inc = this->operator--(1);
        this->loadGraph(inc.getAdjMatrix());
        return *this;
    }
    
    Graph Graph::operator--(int) {
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        unsigned int n = this->getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j]--;
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;    
    }

    Graph Graph::operator*(int scalar) const {
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        unsigned int n = this->getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j] *= scalar;
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;

    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        unsigned int n = graph.getVertices();
        for (const auto& row : graph.getAdjMatrix()) {
            os << "[";
            for (unsigned int i=0; i<n-1; i++) {
                os << row[i] << ", ";
            }
            os << row[n-1] << "]" << endl;
        }
        return os;
    }


    Graph Graph::operator*(const Graph& other) {
        unsigned int n = other.getVertices();

        if (this->getVertices() != n) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        std::vector<std::vector<int>> resultMtx(n, std::vector<int>(n, 0));
        auto otherMtx = other.getAdjMatrix();

        for (unsigned int i = 0; i < n; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                for (unsigned int k = 0; k < n; ++k) {
                    resultMtx[i][j] += (adjMatrix[i][k] * otherMtx[k][j]);
                }
            }
        }
        Graph result;
        result.loadGraph(resultMtx); 
        return result;
    }

    Graph& Graph::operator*=(double scalar) {
        Graph multiply = this->operator*(scalar);
        this->loadGraph(multiply.getAdjMatrix());
        return *this;
    }

    Graph Graph::operator/(int scalar) const {
        vector<vector<int>> resultMtx(this->getAdjMatrix());        
        unsigned int n = this->getVertices();

        for (unsigned int i=0; i<n; i++) {
            for (unsigned int j=0; j<n; j++) {
                resultMtx[i][j] /= scalar;
            }
        }

        Graph result;
        result.loadGraph(resultMtx); 
        return result;
    }

    Graph& Graph::operator/=(double scalar) {
        Graph divide = this->operator/(scalar);
        this->loadGraph(divide.getAdjMatrix());
        return *this;
    }    
}
