#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <DataStructures/WeightedEdge.h>
#include <vector>
#include <set>
#include <map>

class WeightedGraph {
public:
    WeightedGraph();
    ~WeightedGraph();
public:
    bool AddVertex(int vertex);
    bool RemoveVertex(int vertex);
    bool AddEdge(int vertex1, int vertex2, int weight);
    bool RemoveEdge(int vertex1, int vertex2);
public:
    int CountVertices() const;
    int CountEdges() const;
    bool ContainsVertex(int vertex) const;
    bool ContainsEdge(int vertex1, int vertex2) const;
    int GetWeight(int vertex1, int vertex2) const;
    std::vector<int> GetVertices() const;
    std::vector<WeightedEdge> GetEdges() const;
    std::vector<WeightedEdge> GetIncomingEdges(int vertex) const;
    std::vector<WeightedEdge> GetOutgoingEdges(int vertex) const;
    int GetDegree(int vertex) const;
    std::vector<int> GetNeighbors(int vertex) const;
private:
    std::set<int> Vertices;
    std::map<int, std::map<int, int>> WeightedEdges;
};


#endif //WEIGHTEDGRAPH_H
