#include <DataStructures/UndirectedWeightedGraph.h>

bool UndirectedWeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    if(WeightedEdges.count(vertex1))
        WeightedEdges.find(vertex1)->second.erase(vertex2);
    if(WeightedEdges.count(vertex2))
        WeightedEdges.find(vertex2)->second.erase(vertex1);
    return true;
}

bool UndirectedWeightedGraph::ContainsEdge(int vertex1, int vertex2) const {
    if(ContainsVertex(vertex1) && ContainsVertex(vertex2)){
        bool have = false;
        if(WeightedEdges.count(vertex1))
            have = have || WeightedEdges.find(vertex1)->second.count(vertex2);
        if(WeightedEdges.count(vertex2))
            have = have || WeightedEdges.find(vertex2)->second.count(vertex1);
        return have;
    }else return false;
}

int UndirectedWeightedGraph::GetWeight(int vertex1, int vertex2) const {
    if (ContainsEdge(vertex1, vertex2))
        if (WeightedEdges.count(vertex1)) {
            if(WeightedEdges.find(vertex1)->second.count(vertex2))
                return WeightedEdges.find(vertex1)->second.find(vertex2)->second;
        }
        if(WeightedEdges.count(vertex2))
            if(WeightedEdges.find(vertex2)->second.count(vertex1))
                return WeightedEdges.find(vertex2)->second.find(vertex1)->second;
    return -1;//error
}

std::vector<WeightedEdge> UndirectedWeightedGraph::GetIncomingEdges(int vertex) const {
    std::vector<WeightedEdge> inComing_Edges;
    if(ContainsVertex(vertex)) {
        for (auto cor: WeightedEdges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)
                    inComing_Edges.push_back(WeightedEdge(cor.first, vertex, cor.second.find(vertex)->second));
        if (WeightedEdges.count(vertex))
            for (auto cor: WeightedEdges.find(vertex)->second)
                inComing_Edges.push_back(WeightedEdge(vertex, cor.first, cor.second));
    }
    return inComing_Edges;
}

std::vector<WeightedEdge> UndirectedWeightedGraph::GetOutgoingEdges(int vertex) const {
    return this->GetIncomingEdges(vertex);
}

int UndirectedWeightedGraph::GetDegree(int vertex) const {
    int DegreeNum = 0;
    if(ContainsVertex(vertex)) {
        for (auto cor: WeightedEdges)
            if (cor.second.count(vertex))
                    ++DegreeNum;
        if (WeightedEdges.count(vertex))
            DegreeNum += WeightedEdges.find(vertex)->second.size();
    }
    return DegreeNum;
}

std::vector<int> UndirectedWeightedGraph::GetNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if(ContainsVertex(vertex)) {
        if(WeightedEdges.count(vertex))
            for(auto cor : WeightedEdges.find(vertex)->second)
                neighbors.push_back(cor.first);
        for (auto cor: WeightedEdges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)
                    neighbors.push_back(cor.first);

    }
    return neighbors;
}