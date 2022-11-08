#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <cassert>
#include <vector>
#include <optional>
#include<functional>
#include <queue>
#include <map>
#include <utility>

template <template<class> class TGraph, typename TValue>
class ShortestPaths {
public:
    ShortestPaths() = delete;
    ShortestPaths(const TGraph<TValue> *graph, int source);
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

template <template<class> class TGraph, class TValue>
void ShortestPaths<TGraph, TValue>::ShortestPathAddVertex(int vertex, std::vector<int> *container) const {
    if(vertex == Source){
        assert(container->empty());
        container->push_back(Source);
        return;
    }
    ShortestPathAddVertex(ShortestInformations.find(vertex)->second.second, container);
    container->push_back(vertex);
    return;
}
template <template<class> class TGraph, class TValue>
        ShortestPaths<TGraph, TValue>::ShortestPaths(const TGraph<TValue> *graph, int source): Source(source) {}
template <template<class> class TGraph, class TValue>
        ShortestPaths<TGraph, TValue>::~ShortestPaths<TGraph, TValue>() {}
template <template<class> class TGraph, class TValue>
bool ShortestPaths<TGraph, TValue>::HasPathTo(int destination) const {
    return ShortestInformations.count(destination);
}
template <template<class> class TGraph, class TValue>
std::optional<TValue> ShortestPaths<TGraph, TValue>::TryGetDistanceTo(int destination) const {
    if(HasPathTo(destination))
        return ShortestInformations.find(destination)->second.first;
    return std::nullopt;
}
template <template<class> class TGraph, class TValue>
std::optional<std::vector<int>> ShortestPaths<TGraph, TValue>::TryGetShortestPathTo(int destination) const {
    if(HasPathTo(destination)){
        std::vector<int> thisPath;
        ShortestPathAddVertex(destination, &thisPath);
        return thisPath;
    }
    return std::nullopt;
}


#endif
