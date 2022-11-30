#ifndef MULTI_SOURCE_SHORTEST_PATHS
#define MULTI_SOURCE_SHORTEST_PATHS

#include <Algorithms/ShortestPaths.h>

template <typename TGraph>
class MultiSourceShortestPaths {
 public:
  MultiSourceShortestPaths() = delete;
  explicit MultiSourceShortestPaths(const TGraph *graph);
  virtual ~MultiSourceShortestPaths();
 public:
  bool HasPathOf(int source, int destination) const;
  std::optional<TValue> TryGetDistanceOf(int source, int destination) const;
  std::optional<std::vector<int>> TryGetShortestPathOf(int source, int destination) const;

private:
    void ShortestPathAddVertex(int source, int vertex, std::vector<int> *container) const;

protected:
    std::map<std::pair<int, int>, std::pair<TValue, int>> ShortestInfors;
};

template <typename TGraph>
MultiSourceShortestPaths<TGraph>::MultiSourceShortestPaths(const TGraph *graph) {}
template <typename TGraph>
MultiSourceShortestPaths<TGraph>::~MultiSourceShortestPaths<TGraph>() {}
template <typename TGraph>
bool MultiSourceShortestPaths<TGraph>::HasPathOf(int source, int destination) const {
    return ShortestInfors.count(std::make_pair(source, destination));
}
template <typename TGraph>
std::optional<TValue>
MultiSourceShortestPaths<TGraph>::TryGetDistanceOf(int source, int destination) const {
    if(!ShortestInfors.count(std::make_pair(source, destination)))
        return std::nullopt;
    else
        return ShortestInfors.find(std::make_pair(source, destination))->second.first;
}
template <typename TGraph>
std::optional<std::vector<int>>
MultiSourceShortestPaths<TGraph>::TryGetShortestPathOf(int source, int destination) const {
    if(HasPathOf(source, destination)){
        std::vector<int> thisPath;
        ShortestPathAddVertex(source,destination, &thisPath);
        return thisPath;
    }
    return std::nullopt;
}

template <class TGraph>
void MultiSourceShortestPaths<TGraph>::ShortestPathAddVertex(int source, int vertex, std::vector<int> *container) const {
    if(vertex == source) {
        assert(container->empty());
        container->push_back(source);
        return;
    }
    ShortestPathAddVertex(source, ShortestInfors.find(std::make_pair(source, vertex))->second.second, container);
    container->push_back(vertex);
    return;
}

#endif
