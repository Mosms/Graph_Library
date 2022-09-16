#include <DataStructures/WeightedGraph.h>

WeightedGraph::WeightedGraph() {}
WeightedGraph::~WeightedGraph() {}

bool WeightedGraph::AddVertex(int vertex) {
    if(ContainsVertex(vertex)) return false;
    else Vertices.insert(vertex);
    return true;
}
bool WeightedGraph::RemoveVertex(int vertex) {
    if(!ContainsVertex(vertex)) return false;
    Vertices.erase(vertex);
    if(WeightedEdges.count(vertex))
        WeightedEdges.erase(vertex);
    for(auto cor : WeightedEdges)
        cor.second.erase(vertex);//分别删掉以之为入口和以之为出口的边
    return true;
}

bool WeightedGraph::AddEdge(int vertex1, int vertex2, int weight) {
    if(!(ContainsVertex(vertex1) && ContainsVertex(vertex2))) return false;//有一点不存在
    if(ContainsEdge(vertex1, vertex2)) return false; //边存在

    if(WeightedEdges.count(vertex1))
        WeightedEdges.find(vertex1)->second.insert(std::make_pair(vertex1, weight));
    else {
        std::map<int, int> this_out = {std::make_pair(vertex2, weight)};
        WeightedEdges.insert(std::make_pair(vertex1, this_out));
    }//新建边集合
    return true;
}
bool WeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    WeightedEdges.find(vertex1)->second.erase(vertex2);
    return true;
}

int WeightedGraph::CountVertices() const {
    return Vertices.size();
}
int WeightedGraph::CountEdges() const {
    int num = 0;
    for(auto rev : WeightedEdges)
        num += rev.second.size();
    return num;
}

bool WeightedGraph::ContainsVertex(int vertex) const {
    return Vertices.count(vertex);
}
bool WeightedGraph::ContainsEdge(int vertex1, int vertex2) const {
    if(ContainsVertex(vertex1) && ContainsVertex(vertex2)){
        if(WeightedEdges.count(vertex1)){
            auto check= WeightedEdges.find(vertex1)->second;
            if(check.empty()) return false;
            else return check.count(vertex2);
        }else return false;
    }else return false;
}

int WeightedGraph::GetWeight(int vertex1, int vertex2) const {
    if(ContainsEdge(vertex1, vertex2))
        return WeightedEdges.find(vertex1)->second.find(vertex2)->second;
}

std::vector<int> WeightedGraph::GetVertices() const {
    std::vector<int> vertices;
    vertices.assign(Vertices.begin(), Vertices.end());
    return vertices;
}

std::vector<WeightedEdge> WeightedGraph::GetEdges() const {
    std::vector<WeightedEdge> All_Edges;
    for(auto cor1 : WeightedEdges)
        for(auto cor2 : cor1.second)
            All_Edges.push_back(WeightedEdge(cor1.first, cor2.first, cor2.second));
    return All_Edges;
}

std::vector<WeightedEdge> WeightedGraph::GetIncomingEdges(int vertex) const {
    std::vector<WeightedEdge> inComing_Edges;
    if(ContainsVertex(vertex))
        for(auto cor : WeightedEdges)
            if(cor.second.count(vertex))
                inComing_Edges.push_back(WeightedEdge(cor.first, vertex, cor.second.find(vertex)->second));
    return inComing_Edges;
}

std::vector<WeightedEdge> WeightedGraph::GetOutgoingEdges(int vertex) const {
    std::vector<WeightedEdge> outGoing_Edges;
    if(ContainsVertex(vertex))
        if(WeightedEdges.count(vertex)){
            for(auto cor : WeightedEdges.find(vertex)->second)
                outGoing_Edges.push_back(WeightedEdge(vertex, cor.first, cor.second));
        }
    return outGoing_Edges;
}

int WeightedGraph::GetDegree(int vertex) const {
    if(ContainsVertex(vertex)){
        if(WeightedEdges.count(vertex))
            return WeightedEdges.find(vertex)->second.size();
        else return 0;
    }else return 0;
}

std::vector<int> WeightedGraph::GetNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if(ContainsVertex(vertex))
        if(WeightedEdges.count(vertex))
            for(auto cor : WeightedEdges.find(vertex)->second)
                neighbors.push_back(cor.first);
    return neighbors;
}