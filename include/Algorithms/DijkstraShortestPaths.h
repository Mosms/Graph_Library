#ifndef DIJKSTRASHORTEST_PATHS_H
#define DIJKSTRASHORTEST_PATHS_H

#include <Algorithms/ShortestPaths.h>

template <template<class> class TGraph, typename TValue>
class DijkstraShortestPaths : public ShortestPaths<TGraph, TValue>{
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph<TValue> *graph, int source);
    ~DijkstraShortestPaths() {}
};

template <template<class> class TGraph, class TValue>
DijkstraShortestPaths<TGraph, TValue>::DijkstraShortestPaths(const TGraph<TValue> *graph, int source){
    auto CompareDValue = [](std::pair<int, std::map<int, TValue>*> &a, std::pair<int, std::map<int, TValue>*> &b)->bool{
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
    DijkstraShortestPaths<TGraph, TValue>::VertexDValue.insert(std::make_pair(source, TValue()));
    for(auto vercor : graph->GetVertices())
        ExtractMin.push(std::make_pair(vercor, &DijkstraShortestPaths<TGraph, TValue>::VertexDValue));
    while(!ExtractMin.empty()) {
        auto nowVisit = ExtractMin.top();
        ExtractMin.pop();
        if(DijkstraShortestPaths<TGraph, TValue>::VertexDValue.count(nowVisit.first))//没有的话代表不可达，结果为0
            for(auto cor : graph->GetOutgoingEdges(nowVisit.first))
                RelaxEdge(cor.GetSource(), cor.GetDestination(), cor.GetWeight());
    }
}


#endif //DIJKSTRASHORTEST_PATHS_H
