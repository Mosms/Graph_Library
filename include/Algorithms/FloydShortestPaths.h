#ifndef FLOYD_SHORTEST_PATHS_H
#define FLOYD_SHORTEST_PATHS_H

#include <Algorithms/MultiSourceShortestPaths.h>

template <class TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph>{
public:
    FloydShortestPaths() = delete;
    explicit FloydShortestPaths(const TGraph *graph);
    ~FloydShortestPaths() {}
};

template <class TGraph>
FloydShortestPaths<TGraph>::FloydShortestPaths(const TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph) {
    //------------------First----Initialization-----------------//
    for(auto ecor : graph->GetEdges()){
        FloydShortestPaths<TGraph>::ShortestInfors.insert
        (std::make_pair(std::make_pair(ecor.GetSource(), ecor.GetDestination()),
                        std::make_pair(ecor.GetWeight(), ecor.GetSource())));
    }
    auto Vertices = graph->GetVertices();
    for(auto choice : Vertices)
        for(auto i : Vertices)
            for(auto j : Vertices) {
                auto FindIchoice = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(i, choice));
                auto FindchoiceJ = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(choice, j));
                auto FindIJ = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(i, j));
                if(FindIchoice != nullptr && FindchoiceJ != nullptr)
                    if(FindIJ == nullptr || FindIchoice->second.first + FindchoiceJ->second.first < FindIJ->second.first) {
                        FindIJ->second.first = FindIchoice->second.first +FindchoiceJ->second.first;
                        FindIJ->second.second = FindchoiceJ->second.second;
                    }
            }
    return;
}

#endif //FLOYD_SHORTEST_PATHS_H
