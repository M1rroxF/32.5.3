#ifndef SKILLBOX_GRAPHS_H
#define SKILLBOX_GRAPHS_H

#include <iostream>
#include <vector>
using namespace std;

class IGraph {
public:
    virtual ~IGraph() {}
    IGraph() {};
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount() = 0; // Метод должен считать текущее количество вершин
    virtual void GetNextVertices(int vertex, vector<int> &vertices) = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual void GetPrevVertices(int vertex, vector<int> &vertices) = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};


class Graph : public virtual IGraph
{
  private:
    vector<vector<int>> matrixGraph;
    vector<vector<int>> listGraph;

  public:


    // для матрици смежности
    static void resizeMatrixVector(vector<vector<int>>& vec, const int& from, const int& to)
    {
        // изменяем размер на нужный
        bool fx = false;
        if (vec.size() <= from + 1) { vec.resize(from+1); fx = true; }
        if (vec[0].size() < to + 1) for (auto& i : vec) i.resize(to+1);
        else if (fx) for (auto& i : vec) i.resize(vec[0].size());
        // дописываем нужные элементы
        for (int i = 0; i < vec.size(); i++) vec[i][0] = i;
        for (int i = 0; i < vec[0].size(); i++) vec[0][i] = i;
    }
    // для списка смежности
    static void resizeListVector(vector<vector<int>>& vec, const int& from, const int& to)
    {
        // изменяем размер
        if (vec.size() < from) vec.resize(from);
        for (auto& i : vec) if (i.empty()) i.resize(1);
        // дописываем элементы
        for (int i = 0; i < vec.size(); i++) vec[i][0] = i+1;
    }void AddEdge(int from, int to) final
    {
        // матрица
        {
            resizeMatrixVector(matrixGraph, from, to); // меняем размер
            matrixGraph[from][to] = -1; // добавляем соединение в матрицу
        }
        // список
        {
            resizeListVector(listGraph, from, to); // изменяем размер
            listGraph[from-1].push_back(to); // добавляем соединение в матрицу
        }
    }

    int VerticesCount() final
    {
        return (matrixGraph.size() > matrixGraph[0].size() ? matrixGraph.size()-1 : matrixGraph[0].size()-1);
    }

    void GetNextVertices(int vertex, vector<int> &vertices) final
    {
        for (int i = 1; i < listGraph[vertex].size(); i++) vertices.push_back(listGraph[vertex][i]); // добавляем всё из листа
    }

    void GetPrevVertices(int vertex, vector<int> &vertices) final
    {
        bool h = true;
        for (int i = 0; i < listGraph.size(); i++){
            for (int j = 1; j < listGraph[i].size() && h; j++)
            {
                if (listGraph[i][j] == vertex) {vertices.push_back(listGraph[i][0]); h = false;}
            }
        }
    }

    void printGraph()
    {
        for (int i = 0; i < matrixGraph.size(); i++){
            for (int j = 0; j < matrixGraph[i].size(); j++)
            {
                cout << (matrixGraph[i][j] > -1 ? "  " : " ") << matrixGraph[i][j];
            }
            cout << endl;
        }
        cout << "-+-+-+-+-+-+-+-+-+-\n";
        for (int i = 0; i < listGraph.size(); i++) {
            cout << listGraph[i][0];
            for (int j = 1; j < listGraph[i].size(); j++)
            {
                cout << " -> " << listGraph[i][j];
            }
            cout << endl;
        }
    }
};

#endif //SKILLBOX_GRAPHS_H
