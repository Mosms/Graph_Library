#include <DataStructures/UndirectedWeightedGraph.h>
#include <DataStructures/UndirectedGraph.h>
#include <Algorithms/DepthFirstSearcher.h>
#include <Algorithms/BreadthFirstSearcher.h>
#include <Algorithms/ShortestPaths.h>
#include <Algorithms/DijkstraShortestPaths.h>
#include <Algorithms/BellmanFordShortestPaths.h>
#include <Algorithms/FloydShortestPaths.h>
#include <cstdio>
//#include <cassert>
//#include <iostream>
//#include <cstring>
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
static void test3() {
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

    MultiSourceShortestPaths<WeightedGraph<int>> *p = nullptr;
    p = new FloydShortestPaths<WeightedGraph<int>>(g);
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 6; ++j){
            printf("%d", p->HasPathOf(i, j));
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

    //WeightedGraph<bb> sw;
    //ShortestPaths<WeightedGraph<bb>> jskajak(&sw, 1);


    test1();
    test2();
    printf("\n");
    test3();
    return 0;
}