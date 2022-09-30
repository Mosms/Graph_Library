#include <DataStructures/UndirectedWeightedGraph.h>


bool UndirectedWeightedGraph::RemoveEdge(int vertex1, int vertex2)

bool UndirectedWeightedGraph::ContainsEdge(int vertex1, int vertex2) const

int UndirectedWeightedGraph::GetWeight(int vertex1, int vertex2) const

std::vector<WeightedEdge> UndirectedWeightedGraph::GetIncomingEdges(int vertex) const

std::vector<WeightedEdge> UndirectedWeightedGraph::GetOutgoingEdges(int vertex) const

int UndirectedWeightedGraph::GetDegree(int vertex) const

std::vector<int> UndirectedWeightedGraph::GetNeighbors(int vertex) const