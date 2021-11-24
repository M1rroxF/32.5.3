#pragma once

#include <iostream>
#include <map>
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

class ListGraph: public IGraph {
  private:
    std::map<int, std::vector<int>> _nextVert;
    std::map<int, std::vector<int>> _prevVert;

    bool find(map<int, vector<int>>::iterator key, int num)
    {
        for (auto& i : key->second)
            if (i == num) return true;
        return false;
    }

  public:

    std::map<int, vector<int>> get_next() { return _nextVert; }

    void AddEdge(int from, int to) final {
        if (auto it = _nextVert.find(from); it == _nextVert.cend()) {
            _nextVert.insert(pair<int, vector<int>> (from, {to}));
        } else if (!find(it, to)) {
            it->second.push_back(to);
        }

        if (auto it = _prevVert.find(to); it == _prevVert.cend()) {
            _prevVert.insert(pair<int, vector<int>> (to, {from}));
        } else if (!find(it, from)) {
            it->second.push_back(from);
        }
    }

    template<class T>
    ListGraph& operator=(T _oth)
    {
        vector<vector<int>> matrix = _oth.get_matrix();
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 1) AddEdge(matrix[i][0], matrix[0][j]);
            }
        }
        return *this;
    }

    int VerticesCount() final {
        return _nextVert.size();
    }

    void GetNextVertices(int vertex, vector<int> &vertices) final {
        vertices = _nextVert.find(vertex)->second;
    }
    void GetPrevVertices(int vertex, vector<int> &vertices) final {
        vertices = _prevVert.find(vertex)->second;
    }

    void print()
    {
        for (auto& it : _nextVert)
        {
            cout << it.first;
            for (auto& i : it.second) cout << " -> " << i;
            cout << endl;
        }

        vector<int> next, prev;
        GetPrevVertices(3, prev);
        GetNextVertices(3, next);

        for (auto& i : next) cout << i << " "; cout << endl;
        for (auto& i : prev) cout << i << " "; cout << endl;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MatrixGraph: public IGraph {
  private:
    vector<int> allVertex;
    map<int, int> vertex_index;
    vector<std::vector<int>> matrix = {{0}};

    int _getIndex(int vertex) {
        if (auto pos = vertex_index.find(vertex); pos != vertex_index.end()) {
            return pos->second;
        }

        allVertex.push_back(vertex);
        const int res = matrix.size();
        matrix.push_back({vertex});
        for (int i = 1; i < matrix[0].size(); i++) matrix[matrix.size()-1].push_back(0);
        matrix[0].push_back(vertex);
        for (int i = 1; i < matrix.size(); i++) matrix[i].push_back(0);
        vertex_index[vertex] = res;
        return res;
    }

    int _getNotSetIdx(int vertex)
    {
        if (auto pos = vertex_index.find(vertex); pos != vertex_index.end()) {
            return pos->second;
        }
        return -1;
    }

  public:

    vector<vector<int>> get_matrix() { return matrix; }

    MatrixGraph& operator = (ListGraph _oth)
    {
        matrix.clear();
        allVertex.clear();
        vertex_index.clear();

        std::map<int, std::vector<int>> next = _oth.get_next();

        for (auto it : next) {
            for (int i : it.second) {
                AddEdge(it.first, it.second[i]);
            }
        }
        return *this;
    }

    void AddEdge(int from, int to) final {
        if (from == to) return;
        auto from_idx = _getIndex(from), to_idx = _getIndex(to);
        matrix[from_idx][to_idx] = 1;
    }

    int VerticesCount() final { return allVertex.size(); }

    void GetNextVertices(int vertex, vector<int> &vertices) final {
        int idx = _getNotSetIdx(vertex);
        if (idx == -1) return;

        for (int i = 1; i < matrix.size(); i++) {
            if (matrix[idx][i] == 1) vertices.push_back(matrix[i][0]);
        }
    }
    void GetPrevVertices(int vertex, vector<int> &vertices) final {
        int idx = _getNotSetIdx(vertex);
        if (idx == -1) return;

        for (int i = 1; i < matrix.size(); i++) {
            if (matrix[i][idx] == 1) vertices.push_back(matrix[i][0]);
        }
    }

    void print() {
        cout << "-----------\n";
        for (auto& i : matrix)
        {
            for (auto& j : i)
            {
                cout << j << " ";
            }cout << endl;
        }

        vector<int> next, prev;
        GetPrevVertices(3, prev);
        GetNextVertices(3, next);

        for (auto& i : next) cout << i << " "; cout << endl;
        for (auto& i : prev) cout << i << " "; cout << endl;
    }
};