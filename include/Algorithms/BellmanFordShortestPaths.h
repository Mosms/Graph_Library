#ifndef BELLMANFORD_SHORTESTPATHS_H
#define BELLMANFORD_SHORTESTPATHS_H
#include <Algorithms/ShortestPaths.h>
#include <Exceptions/NegativeCycleException.h>
#include <set>

#define BF_infors BellmanFordShortestPaths<TGraph>::ShortestInformations

template <class TGraph>
class BellmanFordShortestPaths : public ShortestPaths<TGraph>{
public:
    BellmanFordShortestPaths() = delete;
    BellmanFordShortestPaths(const TGraph *graph, int source);
    ~BellmanFordShortestPaths() {}
};

template <class TGraph>
BellmanFordShortestPaths<TGraph>::BellmanFordShortestPaths(const TGraph *graph, int source): ShortestPaths<TGraph>(graph, source){
    BF_infors.insert(std::make_pair(source, std::make_pair(TValue(), source)));
    int nNumber = graph->CountVertices();
    for(int i = 1; i < nNumber; i++) {// n - 1 times
        for(auto corE : graph->GetEdges())
            if(BF_infors.count(corE.GetSource())) {
                auto ValueDNew = BF_infors.find(corE.GetSource())->second.first + corE.GetWeight();
                if(BF_infors.count(corE.GetDestination())){
                    if(ValueDNew < BF_infors.find(corE.GetDestination())->second.first){
                        BF_infors.find(corE.GetDestination())->second.first = ValueDNew;
                        BF_infors.find(corE.GetDestination())->second.second = corE.GetSource();
                    }
                }
                else {
                    BF_infors.insert(std::make_pair(corE.GetDestination(), std::make_pair(ValueDNew, corE.GetSource())));
                }
            }
    }

    for(auto corE : graph->GetEdges()){
        if(BF_infors.count(corE.GetSource())) {
            auto ValueDNew = BF_infors.find(corE.GetSource())->second.first + corE.GetWeight();
            if(BF_infors.count(corE.GetDestination())){
                if(ValueDNew < BF_infors.find(corE.GetDestination())->second.first){
                    throw NegativeCycleException(SingleSource_BellmanFord);
                }
            }
        }
    }
}


#endif //BELLMANFORD_SHORTESTPATHS_H
