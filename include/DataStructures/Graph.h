#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <map>
#include <DataStructures/Edge.h>

class Graph {
 public:
  Graph();
  ~Graph();
 public:
  bool AddVertex(int vertex);
  bool RemoveVertex(int vertex);
  bool AddEdge(int vertex1, int vertex2);
  virtual bool RemoveEdge(int vertex1, int vertex2);
 public:
  int CountVertices() const;
  int CountEdges() const;
  bool ContainsVertex(int vertex) const;
  virtual bool ContainsEdge(int vertex1, int vertex2) const;
  std::vector<int> GetVertices() const;
  std::vector<Edge> GetEdges() const;
  virtual std::vector<Edge> GetIncomingEdges(int vertex) const;
  virtual std::vector<Edge> GetOutgoingEdges(int vertex) const;
  virtual int GetDegree(int vertex) const;
  virtual std::vector<int> GetNeighbors(int vertex) const;

protected:
    std::set<int> Vertices;
    std::map<int, std::set<int>> Edges;
};

#endif
