#ifndef WEIGHTEDEDGE_H
#define WEIGHTEDEDGE_H

#include <DataStructures/Edge.h>

template<class T>
class WeightedEdge: public Edge {
public:
    WeightedEdge(int source, int destination, T weight) : Edge(source, destination), weight(weight) {}
    ~WeightedEdge() {}
public:
    T GetWeight() const { return weight; }
private:
    T weight;
};

#endif //WEIGHTEDEDGE_H
