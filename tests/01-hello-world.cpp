#include <DataStructures/UndirectedWeightedGraph.h>
#include <DataStructures/UndirectedGraph.h>
#include <cassert>
#include <iostream>
int main()
{
    UndirectedGraph g; // 创建一张新的图
    assert(g.AddVertex(1)==true);
    assert(g.AddVertex(2)==true);
    assert(g.AddEdge(2,1)==true);
    assert(g.ContainsEdge(1,2)==true);

    return 0;
}