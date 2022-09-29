#ifndef UNDIRECTED_WEIGHTED_GRAPH_H
#define UNDIRECTED_WEIGHTED_GRAPH_H
#include <DataStructures/WeightedGraph.h>

class UndirectedWeightedGraph : public WeightedGraph {
public:
    UndirectedWeightedGraph();
    ~UndirectedWeightedGraph();
public:
    virtual bool RemoveEdge(int vertex1, int vertex2) override;
    virtual bool ContainsEdge(int vertex1, int vertex2) const override;
    virtual int GetWeight(int vertex1, int vertex2) const override;

public:
    virtual std::vector<WeightedEdge> GetIncomingEdges(int vertex) const override;
    virtual std::vector<WeightedEdge> GetOutgoingEdges(int vertex) const override;
    virtual int GetDegree(int vertex) const override;
    virtual std::vector<int> GetNeighbors(int vertex) const override;
};

#endif //UNDIRECTED_WEIGHTED_GRAPH_H
