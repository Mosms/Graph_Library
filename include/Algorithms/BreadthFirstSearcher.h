#ifndef BREADTH_FIRST_SEARCHER
#define BREADTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <vector>
#include <set>
#include <queue>

template <class TGraph>
class BreadthFirstSearcher {
public:
    static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
    static std::optional<int> TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);

};


template <class TGraph>
void BreadthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action) {
    std::set<int> visited;
    std::queue<int> ToVisit({start});
    while(!ToVisit.empty()){
        int nowVisit = ToVisit.front();

        if(graph->ContainsVertex(nowVisit) && !visited.count(nowVisit)) {
            action(nowVisit);
            for(auto cor : graph->GetNeighbors(nowVisit))
                if(!visited.count(cor))
                    ToVisit.push(cor);
        }
        ToVisit.pop();
        visited.emplace(nowVisit);
    }
    return;
}

template <class TGraph>
std::optional<int>
BreadthFirstSearcher<TGraph>::TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate) {
    std::set<int> visited;
    std::queue<int> ToVisit({start});
    while(!ToVisit.empty()){
        int nowVisit = ToVisit.front();

        if(graph->ContainsVertex(nowVisit) && !visited.count(nowVisit)) {
            if(predicate(nowVisit))
                return nowVisit;
            for (auto cor: graph->GetNeighbors(nowVisit))
                if (!visited.count(cor))
                    ToVisit.push(cor);
        }
        ToVisit.pop();
        visited.emplace(nowVisit);
    }
    return std::nullopt;
}

#endif