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

#endif
