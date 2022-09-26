#include <DataStructures/Graph.h>
#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

class UndirectedGraph : public Graph{
public:
    virtual bool ContainsEdge(int vertex1, int vertex2) const override;
    virtual bool RemoveEdge(int vertex1, int vertex2) override;

public:
    virtual std::vector<Edge> GetIncomingEdges(int vertex) const override;
    virtual std::vector<Edge> GetOutgoingEdges(int vertex) const override;
    virtual int GetDegree(int vertex) const override;
    virtual std::vector<int> GetNeighbors(int vertex) const override;
};



#endif //UNDIRECTEDGRAPH_H
