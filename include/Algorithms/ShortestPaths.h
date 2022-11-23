#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <cassert>
#include <vector>
#include <optional>
#include<functional>
#include <queue>
#include <map>
#include <utility>

template <class TGraph>
class ShortestPaths {
public:
    ShortestPaths() = delete;
    ShortestPaths(const TGraph *graph, int source);
    virtual ~ShortestPaths();
public:
    bool HasPathTo(int destination) const;
    std::optional<typename TGraph::EdgeValueType> TryGetDistanceTo(int destination) const;
    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const;

private:
    void ShortestPathAddVertex(int vertex, std::vector<int> *container) const;

protected:
    std::map<int, std::pair<typename TGraph::EdgeValueType, int>> ShortestInformations;
    int Source;
};


template <class TGraph>
ShortestPaths<TGraph>::ShortestPaths(const TGraph *graph, int source) {
    static_assert(std::is_same(decltype(typename TGraph::EdgeValueType()), std::true_type),
            "TValue requires default constructor");
}
template <class TGraph>
void ShortestPaths<TGraph>::ShortestPathAddVertex(int vertex, std::vector<int> *container) const {
    if(vertex == Source){
        assert(container->empty());
        container->push_back(Source);
        return;
    }
    ShortestPathAddVertex(ShortestInformations.find(vertex)->second.second, container);
    container->push_back(vertex);
    return;
}
template <class TGraph>
        ShortestPaths<TGraph>::ShortestPaths(const TGraph *graph, int source): Source(source) {}
template <class TGraph>
        ShortestPaths<TGraph>::~ShortestPaths<TGraph>() {}
template <class TGraph>
bool ShortestPaths<TGraph>::HasPathTo(int destination) const {
    return ShortestInformations.count(destination);
}
template <class TGraph>
std::optional<typename TGraph::EdgeValueType> ShortestPaths<TGraph>::TryGetDistanceTo(int destination) const {
    if(HasPathTo(destination))
        return ShortestInformations.find(destination)->second.first;
    return std::nullopt;
}
template <class TGraph>
std::optional<std::vector<int>> ShortestPaths<TGraph>::TryGetShortestPathTo(int destination) const {
    if(HasPathTo(destination)){
        std::vector<int> thisPath;
        ShortestPathAddVertex(destination, &thisPath);
        return thisPath;
    }
    return std::nullopt;
}


#endif
