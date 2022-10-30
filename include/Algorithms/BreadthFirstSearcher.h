#ifndef BREADTH_FIRST_SEARCHER
#define BREADTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <vector>
#include <set>
#include <queue>

template <typename TGraph>
class BreadthFirstSearcher {
public:
    static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
    static std::optional<int> FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);
};
template <typename TGraph>
void BreadthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action) {
    std::set<int> visited;
    std::queue<int> ToVisit({start});
    while(!ToVisit.empty()){
        int nowVisit = ToVisit.front();
        ToVisit.pop();
        visited.emplace(nowVisit);

        if(graph->ContainsVertex(nowVisit))
            action(nowVisit);
        for(auto cor : graph->GetNeighbors(nowVisit))
            if(!visited.count(cor))
                ToVisit.push(cor);
    }
    return;
}

template <typename TGraph>
std::optional<int>
BreadthFirstSearcher<TGraph>::FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate) {
    std::set<int> visited;
    std::queue<int> ToVisit({start});
    while(!ToVisit.empty()){
        int nowVisit = ToVisit.front();
        ToVisit.pop();
        visited.emplace(nowVisit);

        if(graph->ContainsVertex(nowVisit) && predicate(nowVisit))
            return nowVisit;
        for(auto cor : graph->GetNeighbors(nowVisit))
            if(!visited.count(cor))
                ToVisit.push(cor);
    }
    return std::nullopt;
}

#endif