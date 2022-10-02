#ifndef UNDIRECTED_WEIGHTED_GRAPH_H
#define UNDIRECTED_WEIGHTED_GRAPH_H
#include <DataStructures/WeightedGraph.h>

template<class T>
class UndirectedWeightedGraph : public WeightedGraph<T> {
public:
    UndirectedWeightedGraph() {}
    ~UndirectedWeightedGraph() {}
public:
    virtual bool RemoveEdge(int vertex1, int vertex2) override{
        if(!ContainsEdge(vertex1, vertex2)) return false;
        if(this->WeightedEdges.count(vertex1))
            this->WeightedEdges.find(vertex1)->second.erase(vertex2);
        if(this->WeightedEdges.count(vertex2))
            this->WeightedEdges.find(vertex2)->second.erase(vertex1);
        return true;
    }
    virtual bool ContainsEdge(int vertex1, int vertex2) const override{
        if(this->ContainsVertex(vertex1) && this->ContainsVertex(vertex2)){
            bool have = false;
            if(this->WeightedEdges.count(vertex1))
                have = have || this->WeightedEdges.find(vertex1)->second.count(vertex2);
            if(this->WeightedEdges.count(vertex2))
                have = have || this->WeightedEdges.find(vertex2)->second.count(vertex1);
            return have;
        }else return false;
    }
    virtual T GetWeight(int vertex1, int vertex2) const override{
        if (ContainsEdge(vertex1, vertex2)) {
            if (this->WeightedEdges.count(vertex1)) {
                if (this->WeightedEdges.find(vertex1)->second.count(vertex2))
                    return this->WeightedEdges.find(vertex1)->second.find(vertex2)->second;
            }
            if (this->WeightedEdges.count(vertex2))
                if (this->WeightedEdges.find(vertex2)->second.count(vertex1))
                    return this->WeightedEdges.find(vertex2)->second.find(vertex1)->second;
        }
        //return -1;//error
    }

public:
    virtual std::vector<WeightedEdge<T>> GetIncomingEdges(int vertex) const override{
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
    virtual std::vector<WeightedEdge<T>> GetOutgoingEdges(int vertex) const override{
        return this->GetIncomingEdges(vertex);
    }
    virtual int GetDegree(int vertex) const override{
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
    virtual std::vector<int> GetNeighbors(int vertex) const override {
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
};

#endif //UNDIRECTED_WEIGHTED_GRAPH_H
