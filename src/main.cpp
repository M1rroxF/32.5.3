#include <iostream>
#include "Graphs.h"
using namespace std;

int main() {
    MatrixGraph g2;
    g2.AddEdge(3, 5);
    g2.AddEdge(3, 6);
    g2.AddEdge(2, 3);

    ListGraph g1;
    g1 = g2;
    g1.print();
    g2.print();
}