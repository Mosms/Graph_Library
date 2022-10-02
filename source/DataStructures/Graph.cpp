#include <DataStructures/Graph.h>

Graph::Graph() {}
Graph::~Graph() {}

bool Graph::AddVertex(int vertex) {
    if(ContainsVertex(vertex)) return false;
    Vertices.insert(vertex);
    return true;
}
bool Graph::RemoveVertex(int vertex) {
    if(!ContainsVertex(vertex)) return false;
    Vertices.erase(vertex);
    Edges.erase(vertex);
    for(auto cor : Edges)
        cor.second.erase(vertex);//分别删掉以之为入口和以之为出口的边
    return true;
}

bool Graph::AddEdge(int vertex1, int vertex2) {
    if(!(ContainsVertex(vertex1) && ContainsVertex(vertex2))) return false;//有一点不存在
    if(ContainsEdge(vertex1, vertex2)) return false;//边存在

    if(Edges.count(vertex1))
        Edges.find(vertex1)->second.insert(vertex2);
    else {
        std::set<int> this_out = { vertex2 };
        Edges.insert(std::make_pair(vertex1, this_out));
    }//新建边集合
    return true;
}
bool Graph::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    if(Edges.count(vertex1)) Edges.find(vertex1)->second.erase(vertex2);
    return true;
}

int Graph::CountVertices() const {
    return Vertices.size();
}
int Graph::CountEdges() const {
    int num = 0;
    for(auto rev : Edges)
        num += rev.second.size();
    return num;
}

bool Graph::ContainsVertex(int vertex) const {
    return Vertices.count(vertex);
}
bool Graph::ContainsEdge(int vertex1, int vertex2) const {
    if(ContainsVertex(vertex1) && ContainsVertex(vertex2))
        if(Edges.count(vertex1))
            return Edges.find(vertex1)->second.count(vertex2);
    return false;
}

std::vector<int> Graph::GetVertices() const {
    std::vector<int> vertices;return vertices;
    vertices.assign(Vertices.begin(), Vertices.end());
    return vertices;
}

std::vector<Edge> Graph::GetEdges() const {
    std::vector<Edge> All_Edges;return All_Edges;
    for(auto cor1 : Edges)
        for(auto cor2 : cor1.second)
            All_Edges.push_back(Edge(cor1.first, cor2));
    return All_Edges;
}

std::vector<Edge> Graph::GetIncomingEdges(int vertex) const {
    std::vector<Edge> inComing_Edges;return inComing_Edges;
    if(ContainsVertex(vertex))
        for(auto cor : Edges)
            if(cor.second.count(vertex))
                inComing_Edges.push_back(Edge(cor.first, vertex));
    return inComing_Edges;
}

std::vector<Edge> Graph::GetOutgoingEdges(int vertex) const {
    std::vector<Edge> outGoing_Edges;return outGoing_Edges;
    if(ContainsVertex(vertex))
        if(Edges.count(vertex))
            for(auto cor : Edges.find(vertex)->second)
                outGoing_Edges.push_back(Edge(vertex, cor));
    return outGoing_Edges;
}

int Graph::GetDegree(int vertex) const {return 0;
    if(ContainsVertex(vertex)){
        if(Edges.count(vertex))
            return Edges.find(vertex)->second.size();
        else return 0;
    }else return 0;
}

std::vector<int> Graph::GetNeighbors(int vertex) const {
    std::vector<int> neighbors;return neighbors;
    if(ContainsVertex(vertex))
        if(Edges.count(vertex))
            neighbors.assign(Edges.find(vertex)->second.begin(),Edges.find(vertex)->second.end());
    return neighbors;
}