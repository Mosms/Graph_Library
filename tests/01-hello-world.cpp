#include <DataStructures/UndirectedWeightedGraph.h>
#include <DataStructures/UndirectedGraph.h>
#include <Algorithms/DepthFirstSearcher.h>
#include <Algorithms/BreadthFirstSearcher.h>
#include <Algorithms/ShortestPaths.h>
#include <Algorithms/DijkstraShortestPaths.h>
#include <Algorithms/BellmanFordShortestPaths.h>
#include <cassert>
#include <iostream>
#include <cstring>
static void test1() {
    auto *g = new WeightedGraph<int>();
    for (int i = 1; i <= 6; ++i) {
        g->AddVertex(i);
    }
    g->AddEdge(1, 2, 1);
    g->AddEdge(2, 3, 2);
    g->AddEdge(3, 4, 3);
    g->AddEdge(4, 1, 4);
    g->AddEdge(5, 6, 5);
    g->AddEdge(6, 5, 6);

    ShortestPaths<WeightedGraph<int>> *p = nullptr;
    for (int i = 1; i <= 6; ++i) {
        p = new DijkstraShortestPaths<WeightedGraph<int>>(g, i);
        for (int j = 1; j <= 6; ++j) {
            printf("%d", p->HasPathTo(j));
        }

        printf("\n");
        delete p;
    }

    delete g;
}
static void test2() {
    auto *g = new WeightedGraph<int>();
    for (int i = 1; i <= 6; ++i) {
        g->AddVertex(i);
    }
    g->AddEdge(1, 2, 1);
    g->AddEdge(2, 3, 2);
    g->AddEdge(3, 4, 3);
    g->AddEdge(4, 1, 4);
    g->AddEdge(5, 6, 5);
    g->AddEdge(6, 5, 6);

    ShortestPaths<WeightedGraph<int>> *p = nullptr;
    for (int i = 1; i <= 6; ++i) {
        p = new BellmanFordShortestPaths<WeightedGraph<int>>(g, i);
        for (int j = 1; j <= 6; ++j) {
            printf("%d", p->HasPathTo(j));
        }

        printf("\n");
        delete p;
    }

    delete g;
}
class bb{
    bb()=delete;
};
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
    assert(g.ContainsEdge(3,1)==true);
    assert(g.GetDegree(1)==2);
    assert(g.GetDegree(2)==1);
    assert(g.GetDegree(3)==1);
    assert(g.AddEdge(1,1)==true);
    assert(g.GetDegree(1)==4);
    assert(g.RemoveEdge(3,1)==true);
    for(auto i : g.GetNeighbors(1))
        std::cout<<i<<std::endl;
    std::cout<<g.GetDegree(1)<<std::endl;

    UndirectedWeightedGraph<std::string> w;
    assert(w.AddVertex(1)==true);
    assert(w.AddVertex(2)==true);
    assert(w.AddVertex(3)==true);
    assert(w.RemoveEdge(1,2)==false);
    assert(w.ContainsEdge(1,2)==false);
    assert(w.AddEdge(1,2,"yes")==true);
    assert(w.AddEdge(1,2,"no")==false);
    assert(w.AddEdge(1,3,"no")==true);
    assert(w.GetWeight(2,1)=="yes");
    for(auto i : w.GetNeighbors(1))
        std::cout<<i<<std::endl;
    for(auto i : w.GetIncomingEdges(1))
        std::cout<<i.GetDestination()<<" "<<i.GetSource()<<" "<<i.GetWeight()<<std::endl;
    for(auto i : w.GetOutgoingEdges(1))
        std::cout<<i.GetDestination()<<" "<<i.GetSource()<<" "<<i.GetWeight()<<std::endl;
    assert(w.ContainsEdge(1,2)==true);
    assert(w.CountEdges()==2);
    assert(w.RemoveEdge(1,2)==true);
    for(auto i : w.GetNeighbors(1))
        std::cout<<i<<std::endl;
    for(auto i : w.GetIncomingEdges(1))
        std::cout<<i.GetDestination()<<" "<<i.GetSource()<<" "<<i.GetWeight()<<std::endl;
    for(auto i : w.GetOutgoingEdges(1))
        std::cout<<i.GetDestination()<<" "<<i.GetSource()<<" "<<i.GetWeight()<<std::endl;

    Graph r;
    assert(r.AddVertex(1)==true);
    assert(r.AddVertex(2)==true);
    assert(r.AddVertex(3)==true);
    assert(r.AddEdge(1,2)==true);
    assert(r.AddEdge(1,3)==true);
    for(auto cor : r.GetNeighbors(1))
        std::cout << cor << std::endl;

    std::function<void(int)> prin = [](int a){ printf("%d", a); };

    BreadthFirstSearcher<Graph> check1;
    check1.VisitAllVertices(&r, 1, prin);
    DepthFirstSearcher<Graph> check2;
    check2.VisitAllVertices(&r, 1, prin);
    printf("\n");

    WeightedGraph<bb> sw;
    ShortestPaths<WeightedGraph<bb>> jskajak(&sw, 1);


    test1();
    test2();
    return 0;
}