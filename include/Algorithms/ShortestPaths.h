#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <cassert>
#include <vector>
#include <optional>
#include<functional>
#include <queue>
#include <map>
#include <utility>

template <template<class> class TGraph, typename TValue>
class ShortestPaths {
public:
    ShortestPaths() = delete;
    ShortestPaths(const TGraph<TValue> *graph, int source);
    virtual ~ShortestPaths();
public:
    bool HasPathTo(int destination) const;
    std::optional<TValue> TryGetDistanceTo(int destination) const;
    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const;

private:
    void RelaxEdge(int from, int to, TValue weight);
    void ShortestPathAddVertex(int vertex, std::vector<int>* container);

protected:
    std::map<int, TValue> VertexDValue;
    std::map<int, int> VertexPiValue;
    int Source;
};

template <template<class> class TGraph, class TValue>
void ShortestPaths<TGraph, TValue>::RelaxEdge(int from, int to, TValue weight) {
    assert(VertexDValue.count(from));
    if(VertexDValue.count(to)){
        assert(VertexPiValue.count(to));
        if(VertexDValue.find(to)->second > VertexDValue.find(from)->second + weight) {
            VertexDValue.find(to)->second = VertexDValue.find(from)->second + weight;
            VertexPiValue.find(to)->second = from;
        }
    }
    else {
        assert(!VertexPiValue.count(to));
        VertexDValue.insert(std::make_pair(to,VertexDValue.find(from)->second + weight));
        VertexPiValue.insert(std::make_pair(to,from));
    }
    return;
}
template <template<class> class TGraph, class TValue>
void ShortestPaths<TGraph, TValue>::ShortestPathAddVertex(int vertex, std::vector<int> *container) {
    if(vertex == Source){
        assert(container->empty());
        container->push_back(Source);
        return;
    }
    ShortestPathAddVertex(VertexPiValue.find(vertex)->second, container);
    container->push_back(vertex);
    return;
}
template <template<class> class TGraph, class TValue>
        ShortestPaths<TGraph, TValue>::ShortestPaths(const TGraph<TValue> *graph, int source): Source(source) {
            /*auto CompareDValue = [](std::pair<int, std::map<int, TValue>*> &a, std::pair<int, std::map<int, TValue>*> &b)->bool{
                auto NowMap = a.second;
                assert(NowMap == b.second);
                bool Havea = NowMap->count(a.first), Haveb = NowMap->count(b.first);
                if(Havea && Haveb)
                    return NowMap->find(a.first)->second < NowMap->find(b.first)->second;
                else if(Havea && !Haveb)
                    return true;
                else if(!Havea && Haveb)
                    return false;
                return true;
            };
            std::priority_queue<std::pair<int, std::map<int, TValue>*>, std::vector<std::pair<int, std::map<int, TValue>*>>, decltype(CompareDValue)> ExtractMin(CompareDValue);
            VertexDValue.insert(std::make_pair(source, TValue()));
            for(auto vercor : graph->GetVertices())
                ExtractMin.push(std::make_pair(vercor, &VertexDValue));
            while(!ExtractMin.empty()) {
                auto nowVisit = ExtractMin.top();
                ExtractMin.pop();
                if(VertexDValue.count(nowVisit.first))//没有的话代表不可达，结果为0
                    for(auto cor : graph->GetOutgoingEdges(nowVisit.first))
                        RelaxEdge(cor.GetSource(), cor.GetDestination(), cor.GetWeight());
            }*/
        }

template <template<class> class TGraph, class TValue>
        ShortestPaths<TGraph, TValue>::~ShortestPaths<TGraph, TValue>() {}
template <template<class> class TGraph, class TValue>
bool ShortestPaths<TGraph, TValue>::HasPathTo(int destination) const {
    return VertexDValue.count(destination);
}
template <template<class> class TGraph, class TValue>
std::optional<TValue> ShortestPaths<TGraph, TValue>::TryGetDistanceTo(int destination) const {
    if(HasPathTo(destination))
        return VertexDValue.find(destination)->second;
    return std::nullopt;
}
template <template<class> class TGraph, class TValue>
std::optional<std::vector<int>> ShortestPaths<TGraph, TValue>::TryGetShortestPathTo(int destination) const {
    if(HasPathTo(destination)){
        std::vector<int> paths;
        ShortestPathAddVertex(destination, &paths);
        return paths;
    }
    return std::nullopt;
}


#endif
