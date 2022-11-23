#ifndef DIJKSTRASHORTEST_PATHS_H
#define DIJKSTRASHORTEST_PATHS_H

#include <Algorithms/ShortestPaths.h>
#include <set>

template <class TGraph>
class DijkstraShortestPaths : public ShortestPaths<TGraph>{
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph *graph, int source);
    ~DijkstraShortestPaths() {}
};

template <class TGraph>
DijkstraShortestPaths<TGraph>::DijkstraShortestPaths(const TGraph *graph, int source): ShortestPaths<TGraph>(graph, source){
    auto CompareDValue = [](std::pair<int, typename TGraph::EdgeValueType> &a, std::pair<int, typename TGraph::EdgeValueType> &b)->bool{
        return a.second > b.second;
    };
    std::set<int> vis;
    std::priority_queue<std::pair<int, typename TGraph::EdgeValueType>, std::vector<std::pair<int, typename TGraph::EdgeValueType>>, decltype(CompareDValue)> ExtractMin(CompareDValue);
    DijkstraShortestPaths<TGraph>::ShortestInformations.insert(std::make_pair(source, std::make_pair(typename TGraph::EdgeValueType(), source)));
    ExtractMin.push(std::make_pair(source, typename TGraph::EdgeValueType()));
    while(!ExtractMin.empty()) {
        auto nowVisit = ExtractMin.top();
        ExtractMin.pop();

        if(vis.count(nowVisit.first))
            continue;
        else vis.insert(nowVisit.first);

        for(auto cor : graph->GetOutgoingEdges(nowVisit.first)){
            assert(nowVisit.second == (DijkstraShortestPaths<TGraph>::ShortestInformations).find(cor.GetSource())->second.first);
            auto ValueDNew = DijkstraShortestPaths<TGraph>::ShortestInformations.find(cor.GetSource())->second.first + cor.GetWeight();
            if(DijkstraShortestPaths<TGraph>::ShortestInformations.count(cor.GetDestination())){
                if(ValueDNew < DijkstraShortestPaths<TGraph>::ShortestInformations.find(cor.GetDestination())->second.first){
                    DijkstraShortestPaths<TGraph>::ShortestInformations.find(cor.GetDestination())->second.first = ValueDNew;
                    DijkstraShortestPaths<TGraph>::ShortestInformations.find(cor.GetDestination())->second.second = cor.GetSource();
                    ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
                }
            }
            else {
                DijkstraShortestPaths<TGraph>::ShortestInformations.insert(std::make_pair(cor.GetDestination(), std::make_pair(ValueDNew, cor.GetSource())));
                ExtractMin.push(std::make_pair(cor.GetDestination(), ValueDNew));
            }
        }
    }
}


#endif //DIJKSTRASHORTEST_PATHS_H
