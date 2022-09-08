#include <DataStructures/Edge.h>

Edge::Edge(int source, int destination):source(source), destination(destination) {}

Edge::~Edge() {}

int Edge::GetSource() const { return source; }

int Edge::GetDestination() const { return destination; }