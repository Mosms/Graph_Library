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
                auto IChoice = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(i, choice));
                auto ChoiceJ = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(choice, j));
                auto IJ = FloydShortestPaths<TGraph>::ShortestInfors.find(std::make_pair(i, j));

                auto FindIchoice = FloydShortestPaths<TGraph>::ShortestInfors.count(std::make_pair(i, choice));
                auto FindchoiceJ = FloydShortestPaths<TGraph>::ShortestInfors.count(std::make_pair(choice, j));
                auto FindIJ = FloydShortestPaths<TGraph>::ShortestInfors.count(std::make_pair(i, j));
                if(FindIchoice && FindchoiceJ)
                    if(!FindIJ)
                        FloydShortestPaths<TGraph>::ShortestInfors.insert
                        (std::make_pair(std::make_pair(i, j),
                                        std::make_pair(IChoice->second.first + ChoiceJ->second.first, ChoiceJ->second.second)));
                    else if(IChoice->second.first + ChoiceJ->second.first < IJ->second.first) {
                        IJ->second.first = IChoice->second.first +ChoiceJ->second.first;
                        IJ->second.second = ChoiceJ->second.second;
                    }
            }
    return;
}

#endif //FLOYD_SHORTEST_PATHS_H
