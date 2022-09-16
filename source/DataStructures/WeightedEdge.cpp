#include <DataStructures/WeightedEdge.h>

WeightedEdge::WeightedEdge(int source, int destination, int weight): Edge(source, destination), weight(weight) {}

WeightedEdge::~WeightedEdge() {}

int WeightedEdge::GetWeight() const { return weight;}