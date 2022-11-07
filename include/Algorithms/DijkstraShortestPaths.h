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
DijkstraShortestPaths<TGraph, TValue>::DijkstraShortestPaths(const TGraph<TValue> *graph, int source): ShortestPaths<TGraph, TValue>(graph, source){
    auto CompareDValue = [](std::pair<int, TValue> &a, std::pair<int, TValue> &b)->bool{
        return a.second < b.second;
    };
    std::priority_queue<std::pair<int, TValue>, std::vector<std::pair<int, TValue>>, decltype(CompareDValue)> ExtractMin(CompareDValue);
    DijkstraShortestPaths<TGraph, TValue>::VertexDValue.insert(std::make_pair(source, TValue()));
    ExtractMin.push(std::make_pair(source, TValue()));
    while(!ExtractMin.empty()) {
        auto nowVisit = ExtractMin.top();
        ExtractMin.pop();
        if(DijkstraShortestPaths<TGraph, TValue>::VertexDValue.count(nowVisit.first))//没有的话代表不可达，结果为0
            for(auto cor : graph->GetOutgoingEdges(nowVisit.first)){
                auto ValueDNew = DijkstraShortestPaths<TGraph, TValue>::VertexDValue.find(cor.GetSource())->second + cor.GetWeight();
                if(DijkstraShortestPaths<TGraph, TValue>::VertexDValue.count(cor.GetDestination())){
                    auto ValueDBefore = DijkstraShortestPaths<TGraph, TValue>::VertexDValue.find(cor.GetDestination())->second;
                    if(ValueDNew < ValueDBefore){
                        DijkstraShortestPaths<TGraph, TValue>::VertexDValue.find(cor.GetDestination())->second = ValueDNew;
                        DijkstraShortestPaths<TGraph, TValue>::VertexPiValue.find(cor.GetDestination())->second = cor.GetSource();
                        ExtractMin.push(cor.GetDestination, ValueDNew);
                    }
                }
                else {
                    DijkstraShortestPaths<TGraph, TValue>::VertexDValue.insert(cor.GetDestination(), ValueDNew);
                    DijkstraShortestPaths<TGraph, TValue>::VertexPiValue.insert(cor.GetDestination(), cor.GetSource());
                }
            }

    }
}


#endif //DIJKSTRASHORTEST_PATHS_H
