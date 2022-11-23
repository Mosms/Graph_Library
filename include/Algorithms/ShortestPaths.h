#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <cassert>
#include <vector>
#include <optional>
#include<functional>
#include <queue>
#include <map>
#include <utility>
#include <type_traits>
#define TValue typename TGraph::EdgeValueType

template <class TGraph>
class ShortestPaths {
    static_assert(std::is_default_constructible_v<TValue>,
                  "TValue requires default constructor");
public:
    ShortestPaths() = delete;
    ShortestPaths(const TGraph *graph, int source);
    virtual ~ShortestPaths();
public:
    bool HasPathTo(int destination) const;
    std::optional<TValue> TryGetDistanceTo(int destination) const;
    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const;

private:
    void ShortestPathAddVertex(int vertex, std::vector<int> *container) const;

protected:
    std::map<int, std::pair<TValue, int>> ShortestInformations;
    int Source;
};


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
        ShortestPaths<TGraph>::~ShortestPaths() {}
template <class TGraph>
bool ShortestPaths<TGraph>::HasPathTo(int destination) const {
    return ShortestInformations.count(destination);
}
template <class TGraph>
std::optional<TValue> ShortestPaths<TGraph>::TryGetDistanceTo(int destination) const {
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
