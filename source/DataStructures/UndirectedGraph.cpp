#include <DataStructures/UndirectedGraph.h>

UndirectedGraph::UndirectedGraph() : Graph() {}
UndirectedGraph::~UndirectedGraph() { }

bool UndirectedGraph::ContainsEdge(int vertex1, int vertex2) const {
    if(ContainsVertex(vertex1) && ContainsVertex(vertex2)){
        bool have = false;
        if(Edges.count(vertex1))
            have = have || Edges.find(vertex1)->second.count(vertex2);
        if(Edges.count(vertex2))
            have = have || Edges.find(vertex2)->second.count(vertex1);
        return have;
    } return false;
}

bool UndirectedGraph::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    if(Edges.count(vertex1)) Edges.find(vertex1)->second.erase(vertex2);
    if(Edges.count(vertex2)) Edges.find(vertex2)->second.erase(vertex1);
    return true;
}

std::vector<Edge> UndirectedGraph::GetIncomingEdges(int vertex) const {
    std::vector<Edge> inComing_Edges;
    if(ContainsVertex(vertex)) {
        for (auto cor: Edges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)//不加入自环情况
                    inComing_Edges.push_back(Edge(cor.first, vertex));
        if (Edges.count(vertex))
            for (auto cor: Edges.find(vertex)->second)
                inComing_Edges.push_back(Edge(cor, vertex));
    }
    return inComing_Edges;
}

std::vector<Edge> UndirectedGraph::GetOutgoingEdges(int vertex) const {
    std::vector<Edge> outGoing_Edges;
    if(ContainsVertex(vertex)) {
        for (auto cor: Edges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)//不加入自环情况
                    outGoing_Edges.push_back(Edge(vertex, cor.first));
        if (Edges.count(vertex))
            for (auto cor: Edges.find(vertex)->second)
                outGoing_Edges.push_back(Edge(vertex, cor));
    }
    return outGoing_Edges;
}

int UndirectedGraph::GetDegree(int vertex) const {
    int DegreeNum = 0;
    if(ContainsVertex(vertex)) {
        for (auto cor: Edges)
            if (cor.second.count(vertex))
                    ++DegreeNum;
        if (Edges.count(vertex))
            DegreeNum += Edges.find(vertex)->second.size();
    }
    return DegreeNum;
}

std::vector<int> UndirectedGraph::GetNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if(ContainsVertex(vertex)) {
        if (Edges.count(vertex))
            neighbors.assign(Edges.find(vertex)->second.begin(), Edges.find(vertex)->second.end());
        for (auto cor: Edges)
            if (cor.second.count(vertex))
                if(cor.first != vertex)//不两次加入自环情况
                    neighbors.push_back(cor.first);
    }
    return neighbors;
}