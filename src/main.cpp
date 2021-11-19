#include <iostream>
#include "Graphs.h"
using namespace std;

int main() {
    MatrixGraph g1(0);

    g1.AddEdge(1, 2);
    g1.AddEdge(1, 4);
    g1.AddEdge(1, 2);
    g1.AddEdge(100, 100);
    g1.AddEdge(100, 100);
    g1.AddEdge(-1, 1);

    ListGraph g2;
    g2 = g1;

    g1.print();
    g2.print();
}