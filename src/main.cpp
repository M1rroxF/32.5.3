#include <iostream>
#include "Graphs.h"
using namespace std;

int main()
{
    Graph graph;
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);
    graph.AddEdge(7, 1);
    graph.AddEdge(5, 7);

    graph.printGraph();
}