#ifndef FLOYD_SHORTEST_PATHS_H
#define FLOYD_SHORTEST_PATHS_H

#include <Algorithms/MultiSourceShortestPaths.h>
#include <Exceptions/NegativeCycleException.h>

#define FloydInfors FloydShortestPaths<TGraph>::ShortestInfors

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
        if(FloydInfors.count(std::make_pair(ecor.GetSource(), ecor.GetDestination()))){
            if(ecor.GetWeight() < FloydInfors.find(std::make_pair(ecor.GetSource(), ecor.GetDestination()))->second.first){
                FloydInfors.find(std::make_pair(ecor.GetSource(), ecor.GetDestination()))->second.first = ecor.GetWeight();
                FloydInfors.find(std::make_pair(ecor.GetSource(), ecor.GetDestination()))->second.second = ecor.GetSource();
            }
        }
        else FloydInfors.insert(std::make_pair(std::make_pair(ecor.GetSource(), ecor.GetDestination()),
                                               std::make_pair(ecor.GetWeight(), ecor.GetSource())));
    }

    auto Vertices = graph->GetVertices();
    for(auto i : Vertices)
        FloydInfors.insert(std::make_pair(std::make_pair(i, i),
                                          std::make_pair(TValue(), i)));

    for(auto choice : Vertices)
        for(auto i : Vertices)
            for(auto j : Vertices) {
                auto IChoice = FloydInfors.find(std::make_pair(i, choice));
                auto ChoiceJ = FloydInfors.find(std::make_pair(choice, j));
                auto IJ = FloydInfors.find(std::make_pair(i, j));

                auto FindIchoice = FloydInfors.count(std::make_pair(i, choice));
                auto FindchoiceJ = FloydInfors.count(std::make_pair(choice, j));
                auto FindIJ = FloydInfors.count(std::make_pair(i, j));
                if(FindIchoice && FindchoiceJ)
                    if(!FindIJ)
                        FloydInfors.insert
                        (std::make_pair(std::make_pair(i, j),
                                        std::make_pair(IChoice->second.first + ChoiceJ->second.first, ChoiceJ->second.second)));
                    else if(IChoice->second.first + ChoiceJ->second.first < IJ->second.first) {
                        IJ->second.first = IChoice->second.first + ChoiceJ->second.first;
                        IJ->second.second = ChoiceJ->second.second;
                    }
            }
    for(auto i : Vertices)
        if(FloydInfors.find(std::make_pair(i, i))->second.first + epsilon<TValue>() < TValue())
            throw NegativeCycleException(MultiSource_Floyd);

    return;
}

#endif //FLOYD_SHORTEST_PATHS_H
