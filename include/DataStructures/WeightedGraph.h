#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

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
    virtual bool RemoveEdge(int vertex1, int vertex2);
public:
    int CountVertices() const;
    int CountEdges() const;
    bool ContainsVertex(int vertex) const;
    virtual bool ContainsEdge(int vertex1, int vertex2) const;
    virtual int GetWeight(int vertex1, int vertex2) const;
    std::vector<int> GetVertices() const;
    std::vector<WeightedEdge> GetEdges() const;
    virtual std::vector<WeightedEdge> GetIncomingEdges(int vertex) const;
    virtual std::vector<WeightedEdge> GetOutgoingEdges(int vertex) const;
    virtual int GetDegree(int vertex) const;
    virtual std::vector<int> GetNeighbors(int vertex) const;

protected:
    std::set<int> Vertices;
    std::map<int, std::map<int, int>> WeightedEdges;
};


#endif //WEIGHTED_GRAPH_H
