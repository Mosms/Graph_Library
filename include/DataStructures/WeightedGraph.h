#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <DataStructures/WeightedEdge.h>
#include <vector>
#include <set>
#include <map>

template<typename T>
class WeightedGraph {
public:
    typedef T EdgeValueType;
public:
    WeightedGraph() {}
    ~WeightedGraph() {}
public:
    bool AddVertex(int vertex);
    bool RemoveVertex(int vertex);
    bool AddEdge(int vertex1, int vertex2, T weight);
    virtual bool RemoveEdge(int vertex1, int vertex2);
public:
    int CountVertices() const ;
    int CountEdges() const ;
    bool ContainsVertex(int vertex) const ;
    virtual bool ContainsEdge(int vertex1, int vertex2) const ;
    virtual T GetWeight(int vertex1, int vertex2) const ;
    std::vector<int> GetVertices() const ;
    virtual std::vector<WeightedEdge<T>> GetEdges() const ;
    virtual std::vector<WeightedEdge<T>> GetIncomingEdges(int vertex) const ;
    virtual std::vector<WeightedEdge<T>> GetOutgoingEdges(int vertex) const ;
    virtual int GetDegree(int vertex) const ;
    virtual std::vector<int> GetNeighbors(int vertex) const ;

protected:
    std::set<int> Vertices;
    std::map<int, std::map<int, T>> WeightedEdges;
};



template<class T>
bool WeightedGraph<T>::AddVertex(int vertex) {
    if(ContainsVertex(vertex)) return false;
    Vertices.insert(vertex);
    return true;
}

template<class T>
bool WeightedGraph<T>::RemoveVertex(int vertex) {
    if(!ContainsVertex(vertex)) return false;
    Vertices.erase(vertex);
    WeightedEdges.erase(vertex);
    for(auto cor : WeightedEdges)
        cor.second.erase(vertex);//分别删掉以之为入口和以之为出口的边
    return true;
}
template<class T>
bool WeightedGraph<T>::AddEdge(int vertex1, int vertex2, T weight) {
    if(!(ContainsVertex(vertex1) && ContainsVertex(vertex2))) return false;//有一点不存在
    if(ContainsEdge(vertex1, vertex2)) return false; //边存在

    if(WeightedEdges.count(vertex1))
        WeightedEdges.find(vertex1)->second.insert({vertex2, weight});
    else {
        std::map<int, T> this_out= {{vertex2, weight}};
        WeightedEdges.insert(std::make_pair(vertex1, this_out));
    }//新建边集合
    return true;
}
template<class T>
bool WeightedGraph<T>::RemoveEdge(int vertex1, int vertex2) {
    if(!ContainsEdge(vertex1, vertex2)) return false;
    if(WeightedEdges.count(vertex1)) WeightedEdges.find(vertex1)->second.erase(vertex2);
    return true;
}
template<class T>
int WeightedGraph<T>::CountVertices() const {
    return Vertices.size();
}
template<class T>
int WeightedGraph<T>::CountEdges() const {
    int num = 0;
    for(auto rev : WeightedEdges)
        num += rev.second.size();
    return num;
}
template<class T>
bool WeightedGraph<T>::ContainsVertex(int vertex) const {
    return Vertices.count(vertex);
}
template<class T>
bool WeightedGraph<T>::ContainsEdge(int vertex1, int vertex2) const {
    if(ContainsVertex(vertex1) && ContainsVertex(vertex2)){
        if(WeightedEdges.count(vertex1))
            return WeightedEdges.find(vertex1)->second.count(vertex2);
        else return false;
    }else return false;
}
template<class T>
T WeightedGraph<T>::GetWeight(int vertex1, int vertex2) const {
    if(ContainsEdge(vertex1, vertex2))
        if(WeightedEdges.count(vertex1))
            if(WeightedEdges.find(vertex1)->second.count(vertex2))
                return WeightedEdges.find(vertex1)->second.find(vertex2)->second;
    return 0;//error
}
template<class T>
std::vector<int> WeightedGraph<T>::GetVertices() const {
    std::vector<int> vertices;
    vertices.assign(Vertices.begin(), Vertices.end());
    return vertices;
}
template<class T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetEdges() const {
    std::vector<WeightedEdge<T>> All_Edges;
    for(auto cor1 : WeightedEdges)
        for(auto cor2 : cor1.second)
            All_Edges.push_back(WeightedEdge<T>(cor1.first, cor2.first, cor2.second));
    return All_Edges;
}
template<class T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetIncomingEdges(int vertex) const {
    std::vector<WeightedEdge<T>> inComing_Edges;
    if(ContainsVertex(vertex))
        for(auto cor : WeightedEdges)
            if(cor.second.count(vertex))
                inComing_Edges.push_back(WeightedEdge<T>(cor.first, vertex, cor.second.find(vertex)->second));
    return inComing_Edges;
}
template<class T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetOutgoingEdges(int vertex) const {
    std::vector<WeightedEdge<T>> outGoing_Edges;
    if(ContainsVertex(vertex))
        if(WeightedEdges.count(vertex))
            for(auto cor : WeightedEdges.find(vertex)->second)
                outGoing_Edges.push_back(WeightedEdge<T>(vertex, cor.first, cor.second));
    return outGoing_Edges;
}
template<class T>
int WeightedGraph<T>::GetDegree(int vertex) const{
    if(ContainsVertex(vertex)){
        if(WeightedEdges.count(vertex))
            return WeightedEdges.find(vertex)->second.size();
        else return 0;
    }else return 0;
}
template<class T>
std::vector<int> WeightedGraph<T>::GetNeighbors(int vertex) const{
    std::vector<int> neighbors;
    if(ContainsVertex(vertex))
        if(WeightedEdges.count(vertex))
            for(auto cor : WeightedEdges.find(vertex)->second)
                neighbors.push_back(cor.first);
    return neighbors;
}




#endif //WEIGHTED_GRAPH_H
