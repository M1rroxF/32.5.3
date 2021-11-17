#include <iostream>
#include "Graphs.h"
using namespace std;

int main()
{
    Graph graph;

    // что бы не вводить значения
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);
    graph.AddEdge(7, 1);
    graph.AddEdge(5, 7);
    graph.AddEdge(5, 7);
    graph.AddEdge(4, 3);
    graph.AddEdge(2, 3);
    graph.AddEdge(6, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(1, 3);

    graph.printGraph();

    cout << "-+-+-+-+-+-+-+-+-+-\n";

    vector<int> f1, f2;
    graph.GetNextVertices(3, f1); // 3 -> f1[i]
    graph.GetPrevVertices(3, f2); // f2[i] -> 3

    for (int i : f1) cout << i << " "; cout << "- Next with 3" << endl;
    for (int i : f2) cout << i << " "; cout << "- Prev with 3" << endl;
}