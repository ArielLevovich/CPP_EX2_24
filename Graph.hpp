#include <string>
#include <vector> 
#include <iostream>

#pragma once
using namespace std;

namespace ariel {
    class Graph {
        private:
            unsigned int vertices;  
            vector<vector<int>> adjMatrix;
            bool isDirectedGraph;
            bool isNegativeWeight;
        public:
            std::string printGraph();
            void loadGraph(const std::vector<std::vector<int>> graph);
            unsigned int getVertices() const;   
            unsigned int getEdges() const;         
            const vector<vector<int>> getAdjMatrix() const;            
            bool isDirected() const;         
            bool hasNegativeWeight() const;  

            Graph operator+(const Graph& other) const;
            Graph& operator+=(const Graph& other);
            Graph operator+() const;

            Graph operator-(const Graph& other) const;
            Graph& operator-=(const Graph& other);
            Graph operator-() const;

            bool operator==(const Graph& other) const;
            bool operator!=(const Graph& other) const;
            bool operator<(const Graph& other) const;
            bool operator>(const Graph& other) const;
            bool operator<=(const Graph& other) const;
            bool operator>=(const Graph& other) const;

            Graph& operator++();
            Graph operator++(int);
            Graph& operator--();
            Graph operator--(int);
            
            friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
            
            Graph operator*(int scalar) const;
            Graph operator*(const Graph& other);
            Graph& operator*=(double scalar);

            Graph operator/(int scalar) const;
            Graph& operator/=(double scalar);
        private:
            void setAdjMatrix(const vector<vector<int>> matrix, bool isDirected);
            bool isSymmetric(const vector<vector<int>> mtr);
            void setVertices(unsigned int v);            
            bool hasGraphNegativeWeight(const vector<vector<int>> mtr);
            bool isIncludedIn(const Graph& other) const;            
    };
}
