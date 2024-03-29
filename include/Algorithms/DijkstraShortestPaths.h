#ifndef DIJKSTRASHORTEST_PATHS_H
#define DIJKSTRASHORTEST_PATHS_H

#include <Algorithms/ShortestPaths.h>
#include <set>

#define DijkInfors DijkstraShortestPaths<TGraph>::ShortestInformations


template <class TGraph>
class DijkstraShortestPaths : public ShortestPaths<TGraph>{
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph *graph, int source);
    ~DijkstraShortestPaths() {}
};

template <class TGraph>
DijkstraShortestPaths<TGraph>::DijkstraShortestPaths(const TGraph *graph, int source): ShortestPaths<TGraph>(graph, source){
    auto CompareDValue = [](std::pair<int, TValue> &a, std::pair<int, TValue> &b)->bool{
        return a.second > b.second;
    };
    std::set<int> vis;
    std::priority_queue<std::pair<int, TValue>, std::vector<std::pair<int, TValue>>, decltype(CompareDValue)> ExtractMin(CompareDValue);
    DijkInfors.insert(std::make_pair(source, std::make_pair(TValue(), source)));
    ExtractMin.push(std::make_pair(source, TValue()));
    while(!ExtractMin.empty()) {
        auto nowVisit = ExtractMin.top();
        ExtractMin.pop();

        if(vis.count(nowVisit.first))
            continue;
        else vis.insert(nowVisit.first);

        for(auto cor : graph->GetOutgoingEdges(nowVisit.first)){
            assert(nowVisit.second == DijkInfors.find(cor.GetSource())->second.first);
            auto ValueDNew = DijkInfors.find(cor.GetSource())->second.first + cor.GetWeight();
            if(DijkInfors.count(cor.GetDestination())){
                if(ValueDNew < DijkInfors.find(cor.GetDestination())->second.first){
                    DijkInfors.find(cor.GetDestination())->second.first = ValueDNew;
                    DijkInfors.find(cor.GetDestination())->second.second = cor.GetSource();
                    ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
                }
            }
            else {
                DijkInfors.insert(std::make_pair(cor.GetDestination(), std::make_pair(ValueDNew, cor.GetSource())));
                ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
            }
        }
    }
}


#endif //DIJKSTRASHORTEST_PATHS_H
