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
    assert(g.AddEdge(1,2)== false);
    assert(g.AddEdge(1,3)== false);
    assert(g.AddVertex(3)==true);
    assert(g.AddEdge(1,3)== true);

    return 0;
}