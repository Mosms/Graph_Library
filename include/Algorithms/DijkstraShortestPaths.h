#ifndef DIJKSTRASHORTEST_PATHS_H
#define DIJKSTRASHORTEST_PATHS_H

#include <Algorithms/ShortestPaths.h>
#include <set>

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
        return a.second > b.second;
    };
    std::set<int> vis;
    std::priority_queue<std::pair<int, TValue>, std::vector<std::pair<int, TValue>>, decltype(CompareDValue)> ExtractMin(CompareDValue);
    DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.insert(std::make_pair(source, std::make_pair(TValue(), source)));
    ExtractMin.push(std::make_pair(source, TValue()));
    while(!ExtractMin.empty()) {
        auto nowVisit = ExtractMin.top();
        ExtractMin.pop();

        if(vis.count(nowVisit.first))
            continue;
        else vis.insert(nowVisit.first);

        for(auto cor : graph->GetOutgoingEdges(nowVisit.first)){
            assert(nowVisit.second == (DijkstraShortestPaths<TGraph, TValue>::ShortestInformations).find(cor.GetSource())->second.first);
            auto ValueDNew = DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.find(cor.GetSource())->second.first + cor.GetWeight();
            if(DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.count(cor.GetDestination())){
                if(ValueDNew < DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.find(cor.GetDestination())->second.first){
                    DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.find(cor.GetDestination())->second.first = ValueDNew;
                    DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.find(cor.GetDestination())->second.second = cor.GetSource();
                    ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
                }
            }
            else {
                DijkstraShortestPaths<TGraph, TValue>::ShortestInformations.insert(std::make_pair(cor.GetDestination(), std::make_pair(ValueDNew, cor.GetSource())));
                ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
            }
        }
    }
}


#endif //DIJKSTRASHORTEST_PATHS_H
