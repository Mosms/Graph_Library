#ifndef BELLMANFORD_SHORTESTPATHS_H
#define BELLMANFORD_SHORTESTPATHS_H
#include <Algorithms/ShortestPaths.h>
#include <set>

template <class TGraph>
class BellmanFordShortestPaths : public ShortestPaths<TGraph>{
public:
    BellmanFordShortestPaths() = delete;
    BellmanFordShortestPaths(const TGraph *graph, int source);
    ~BellmanFordShortestPaths() {}
};

template <class TGraph>
BellmanFordShortestPaths<TGraph>::BellmanFordShortestPaths(const TGraph *graph, int source): ShortestPaths<TGraph>(graph, source){
    BellmanFordShortestPaths<TGraph>::ShortestInformations.insert(std::make_pair(source, std::make_pair(TValue(), source)));
    int nNumber = graph->CountVertices();
    for(int i = 1; i < nNumber; i++) {// n - 1 times
        for(auto corE : graph->GetEdges())
            if(BellmanFordShortestPaths<TGraph>::ShortestInformations.count(corE.GetSource())) {
                auto ValueDNew = BellmanFordShortestPaths<TGraph>::ShortestInformations.find(corE.GetSource())->second.first + corE.GetWeight();
                if(BellmanFordShortestPaths<TGraph>::ShortestInformations.count(corE.GetDestination())){
                    if(ValueDNew < BellmanFordShortestPaths<TGraph>::ShortestInformations.find(corE.GetDestination())->second.first){
                        BellmanFordShortestPaths<TGraph>::ShortestInformations.find(corE.GetDestination())->second.first = ValueDNew;
                        BellmanFordShortestPaths<TGraph>::ShortestInformations.find(corE.GetDestination())->second.second = corE.GetSource();
                    }
                }
                else {
                    BellmanFordShortestPaths<TGraph>::ShortestInformations.insert(std::make_pair(corE.GetDestination(), std::make_pair(ValueDNew, corE.GetSource())));
                }
            }

    }
}


#endif //BELLMANFORD_SHORTESTPATHS_H
