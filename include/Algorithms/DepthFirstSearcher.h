#ifndef DEPTH_FIRST_SEARCHER
#define DEPTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <set>

template <typename TGraph>
class DepthFirstSearcher {
public:
    static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
    static std::optional<int> FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);

private:
    static void visitsAction(const TGraph *graph, int nowvis, std::function<void(int)> action, std::set<int> *check);
    static std::optional<int> visitsFind(const TGraph *graph, int nowvis, std::function<bool(int)> predicate, std::set<int> *check);
};
template <typename TGraph>
void DepthFirstSearcher<TGraph>::visitsAction(const TGraph *graph, int nowvis, std::function<void(int)> action,
                                              std::set<int> *check) {
    if(graph->ContainsVertex(nowvis) && !check->count(nowvis))
        action(nowvis);
    check->emplace(nowvis);
    for(auto cor : graph->GetNeighbors(nowvis))
        visitsAction(graph, cor, action, check);
    return;
}

template <typename TGraph>
std::optional<int>
DepthFirstSearcher<TGraph>::visitsFind(const TGraph *graph, int nowvis, std::function<bool(int)> predicate,
                                       std::set<int> *check) {
    if(graph->ContainsVertex(nowvis) && !check->count(nowvis))
        if(predicate(nowvis))
            return nowvis;
    check->emplace(nowvis);
    for(auto cor : graph->GetNeighbors(nowvis)) {
        std::optional<int> Ret = visitsAction(graph, cor, predicate, check);
        if (Ret != std::nullopt)
            return Ret;
    }
    return std::nullopt;
}

template <typename TGraph>
void DepthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action) {
    std::set<int> visited;
    visitsAction(graph, start, action, &visited);
    return;
}

template <typename TGraph>
std::optional<int> DepthFirstSearcher<TGraph>::FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate) {
    std::set<int> visited;
    return visitsFind(graph, start, predicate, &visited);
}
#endif
