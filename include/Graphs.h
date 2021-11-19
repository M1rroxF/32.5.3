#pragma once

#include <iostream>
#include <vector>
using namespace std;

class IGraph {
public:
    vector<vector<int>> graph;
    virtual ~IGraph() {}
    IGraph() {};
    virtual IGraph& operator=(IGraph& _oth) = 0;
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount() = 0; // Метод должен считать текущее количество вершин
    virtual void GetNextVertices(int vertex, vector<int> &vertices) = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual void GetPrevVertices(int vertex, vector<int> &vertices) = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
    virtual void print() = 0;
};

class MatrixGraph: public IGraph
{
  public:
    MatrixGraph(const int& n){ graph = {{n}}; }

    static int search(const vector<vector<int>>& vec, int num)
    {
        // ищем элемент
        for (int i = 0; i < vec.size(); i++) if (num == vec[i][0]) return i;
        // если не нашли выдаём -1
        return -1;
    }

    static void add_num_to_matrix(vector<vector<int>>& vec, int num)
    {
        // добавляем числа
        vec.push_back({num});
        vec[0].push_back({num});

        // изменяем размер всех строк
        for (auto& i : vec)
            i.resize(vec[0].size());

        // вписываем нули
        for (auto& i : vec) for (auto& j : i) if (j < -1) j = 0;
    }

    static void add_and_set(vector<vector<int>>& vec, int from, int to)
    {
        if (search(vec, from) == -1) add_num_to_matrix(vec, from);
        if (search(vec, to) == -1) add_num_to_matrix(vec, to);
        // ищем элементы и соединяем их
        vec[search(vec, from)][search(vec, to)] = -1;
    }

    void AddEdge(int from, int to) final
    {
        // если элемент тот же то выходим
        if (from == to) return;
        // если вершина менше 1
        if (from < 1 || to < 1) return;
        // ну тут понятно
        add_and_set(graph, from, to);
    }

    MatrixGraph& operator=(IGraph& _oth) final
    {
        // если мы хотим присвоить себя
        if (this == &_oth) return *this;
        // если граф пуст
        if (_oth.graph.empty() || _oth.graph[0].empty()) return *this;
        // если это такой же граф
        if (_oth.graph[0][0] == 0) { graph = _oth.graph; return *this; }

        for (int i = 0; i < _oth.graph.size(); i++) {
            for (int j = 1; j < _oth.graph[i].size(); j++)
                add_and_set(graph, _oth.graph[i][0], _oth.graph[i][j]);
        }

        return *this;
    }

    int VerticesCount() final { return graph.size()-1; }

    void GetNextVertices(int vertex, vector<int> &vertices) final
    {
        // ищем в высоте нашу точку
        int y = search(graph, vertex);
        // добавляем в вектор все точки с которыми соединена наша
        if (y != -1) for (int i = 1; i < graph.size(); i++) if (graph[y][i] != 0) vertices.push_back(graph[0][i]);
    }

    void GetPrevVertices(int vertex, vector<int> &vertices) final
    {
        // ищем в ширине нашу точку
        int x = search(graph, vertex);
        // добавляем в вектор все точки с которыми соединена наша
        if (x != -1) for (int i = 1; i < graph.size(); i++) if (graph[i][x] != 0) vertices.push_back(graph[i][0]);
    }

    void print() final
    {
        cout << "-------------\n";
        for (auto& i : graph)
        {
            for (auto& j : i)
            {
                cout << (j >= 0 ? "  " : " ") << j;
            }
            cout << endl;
        }
        vector<int> next; GetNextVertices(3, next);
        vector<int> prev; GetPrevVertices(3, prev);
        for (auto& i : next) cout << (i >= 0 ? "  " : " ") << i; cout << " - next" << endl;
        for (auto& i : prev) cout << (i >= 0 ? "  " : " ") << i; cout << " - prev" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ListGraph: public IGraph
{
  public:

    static int search(vector<vector<int>>& vec, int num)
    {
        for (int i = 0; i < vec.size(); i++) if (vec[i][0] == num) return i;
        return -1;
    }
    static int search(vector<int>& vec, int num)
    {
        for (int i = 1; i < vec.size(); i++) if (vec[i] == num) return i;
        return -1;
    }

    static void push(vector<vector<int>>& vec, int num, int count = -1)
    {
        if (count == -1) vec.push_back({num});
        else vec[count].push_back(num);
    }

    ListGraph& operator=(IGraph& _oth) final
    {
        // если мы хотим присвоить себя
        if (this == &_oth) return *this;
        // если граф пуст
        if (_oth.graph.empty() || _oth.graph[0].empty()) return *this;
        // если это такой же граф
        if (_oth.graph[0][0] != 0) { graph = _oth.graph; return *this; }

        for (int i = 1; i < _oth.graph.size(); i++)
        {
            graph.push_back({_oth.graph[i][0]});
            for (int j = 1; j < _oth.graph.size(); j++)
                if (_oth.graph[i][j]!=0) graph[i-1].push_back(_oth.graph[0][j]);
        }

        return *this;
    }

    void AddEdge(int from, int to) final
    {
        // если элемент тот же то выходим
        if (from == to) return;
        // если вершина менше 1
        if (from < 1 || to < 1) return;
        // если данное ребро уже есть то выходим
        if (search(graph, from) != -1 && search(graph, to) != -1) return;

        // добавляем
        if (search(graph, from) == -1) push(graph, from);
        if (search(graph, to) == -1) push(graph, to);
        if (search(graph[search(graph, from)], to) == -1) push(graph, to, search(graph, from));
    }

    int VerticesCount() final
    {
        return graph.size();
    }

    void GetNextVertices(int vertex, vector<int> &vertices) final
    {
        // ищем данную точку
        int y = search(graph, vertex);
        // добавляем в вектор все точки с которыми соединена наша
        if (y != -1) for (int i = 1; i < graph[y].size(); i++) vertices.push_back(graph[y][i]);
    }

    void GetPrevVertices(int vertex, vector<int> &vertices) final
    {
        // ищем элементы и добавляем
        for (int i = 0; i < graph.size(); i++)
        {
            bool fx = true;
            for (int j = 1; fx && j < graph[i].size(); j++)
                if (graph[i][j] == vertex) { vertices.push_back(graph[i][0]); fx = false; }
        }
    }

    void print() final
    {
        cout << "-------------\n";
        for (auto& i : graph)
        {
            cout << "  " << i[0];
            for (int j = 1; j < i.size(); j++)
            {
                cout << " -> " << i[j];
            }
            cout << endl;
        }
        vector<int> next; GetNextVertices(3, next);
        vector<int> prev; GetPrevVertices(3, prev);
        for (auto& i : next) cout << (i >= 0 ? "  " : " ") << i; cout << " - next" << endl;
        for (auto& i : prev) cout << (i >= 0 ? "  " : " ") << i; cout << " - prev" << endl;
    }
};