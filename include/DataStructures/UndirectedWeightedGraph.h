#ifndef UNDIRECTED_WEIGHTED_GRAPH_H
#define UNDIRECTED_WEIGHTED_GRAPH_H
#include <DataStructures/WeightedGraph.h>

template<class T>
class UndirectedWeightedGraph : public WeightedGraph<T> {
public:
    UndirectedWeightedGraph() {}
    ~UndirectedWeightedGraph() {}
public:
    virtual bool RemoveEdge(int vertex1, int vertex2) override;
    virtual bool ContainsEdge(int vertex1, int vertex2) const override;
    virtual T GetWeight(int vertex1, int vertex2) const override;

public:
    virtual std::vector<WeightedEdge<T>> GetIncomingEdges(int vertex) const override;
    virtual std::vector<WeightedEdge<T>> GetOutgoingEdges(int vertex) const override;
    virtual int GetDegree(int vertex) const override;
    virtual std::vector<int> GetNeighbors(int vertex) const override;
};



template<class T>
bool UndirectedWeightedGraph<T>::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    if(this->WeightedEdges.count(vertex1))
        this->WeightedEdges.find(vertex1)->second.erase(vertex2);
    if(this->WeightedEdges.count(vertex2))
        this->WeightedEdges.find(vertex2)->second.erase(vertex1);
    return true;
}
template<class T>
bool UndirectedWeightedGraph<T>::ContainsEdge(int vertex1, int vertex2) const {
    if(this->ContainsVertex(vertex1) && this->ContainsVertex(vertex2)){
        bool have = false;
        if(this->WeightedEdges.count(vertex1))
            have = have || this->WeightedEdges.find(vertex1)->second.count(vertex2);
        if(this->WeightedEdges.count(vertex2))
            have = have || this->WeightedEdges.find(vertex2)->second.count(vertex1);
        return have;
    }else return false;
}
template<class T>
T UndirectedWeightedGraph<T>::GetWeight(int vertex1, int vertex2) const {
    if (ContainsEdge(vertex1, vertex2)) {
        if (this->WeightedEdges.count(vertex1)) {
            if (this->WeightedEdges.find(vertex1)->second.count(vertex2))
                return this->WeightedEdges.find(vertex1)->second.find(vertex2)->second;
        }
        if (this->WeightedEdges.count(vertex2))
            if (this->WeightedEdges.find(vertex2)->second.count(vertex1))
                return this->WeightedEdges.find(vertex2)->second.find(vertex1)->second;
    }
    return 0;//error
}
template<class T>
std::vector<WeightedEdge<T>> UndirectedWeightedGraph<T>::GetIncomingEdges(int vertex) const {
    std::vector<WeightedEdge<T>> inComing_Edges;
    if(this->ContainsVertex(vertex)) {
        for (auto cor: this->WeightedEdges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)
                    inComing_Edges.push_back(WeightedEdge<T>(cor.first, vertex, cor.second.find(vertex)->second));
        if (this->WeightedEdges.count(vertex))
            for (auto cor: this->WeightedEdges.find(vertex)->second)
                inComing_Edges.push_back(WeightedEdge<T>(vertex, cor.first, cor.second));
    }
    return inComing_Edges;
}
template<class T>
std::vector<WeightedEdge<T>> UndirectedWeightedGraph<T>::GetOutgoingEdges(int vertex) const {
    return this->GetIncomingEdges(vertex);
}
template<class T>
int UndirectedWeightedGraph<T>::GetDegree(int vertex) const {
    int DegreeNum = 0;
    if(this->ContainsVertex(vertex)) {
        for (auto cor: this->WeightedEdges)
            if (cor.second.count(vertex))
                ++DegreeNum;
        if (this->WeightedEdges.count(vertex))
            DegreeNum += this->WeightedEdges.find(vertex)->second.size();
    }
    return DegreeNum;
}
template<class T>
std::vector<int> UndirectedWeightedGraph<T>::GetNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if(this->ContainsVertex(vertex)) {
        if(this->WeightedEdges.count(vertex))
            for(auto cor : this->WeightedEdges.find(vertex)->second)
                neighbors.push_back(cor.first);
        for (auto cor: this->WeightedEdges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)
                    neighbors.push_back(cor.first);
    }
    return neighbors;
}
#endif //UNDIRECTED_WEIGHTED_GRAPH_H
