#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

using vertex_t = size_t;
using weight_t = size_t;

class Graph {
private:
    vector<vector<weight_t>> data;

public:
    Graph(size_t v);

    void addVertex();
    void addDirectedEdge(vertex_t from, vertex_t to, weight_t w);
    void addEdge(vertex_t from, vertex_t to, weight_t w);

    bool validVertex(vertex_t) const;
    weight_t getWeight(vertex_t v1, vertex_t v2) const;
    size_t vertexCount() const;
    bool hasAdjacent(vertex_t from, vertex_t to) const;

    vector<vertex_t> getSuccessors(vertex_t v) const;
    vector<vertex_t> getPredecessors(vertex_t v) const;
};

Graph::Graph(size_t v) {
    data = vector<vector<weight_t>>(v, vector<weight_t>(v, 0));
}

void Graph::addVertex() {
    for (auto &v : data) {
        v.push_back(0);
    }
    data.push_back(vector<weight_t>());
}

void Graph::addDirectedEdge(vertex_t from, vertex_t to, weight_t w) {
    if (!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";

    data[from][to] = w;
}

void Graph::addEdge(vertex_t from, vertex_t to, weight_t w) {
    addDirectedEdge(from, to, w);
    addDirectedEdge(to, from, w);
}

bool Graph::validVertex(vertex_t v) const {
    return v < data.size();
}

weight_t Graph::getWeight(vertex_t v1, vertex_t v2) const {
    if (!validVertex(v1) || !validVertex(v2))
        throw "Invalid vertex";

    return data[v1][v2];
}

size_t Graph::vertexCount() const {
    return data.size();
}

bool Graph::hasAdjacent(vertex_t from, vertex_t to) const {
    if (!validVertex(from) || !validVertex(to))
        throw "Invalid vertex";

    return data[from][to] > 0;
}

vector<vertex_t> Graph::getSuccessors(vertex_t v) const {
    if (!validVertex(v))
        throw "Invalid vertex";

    vector<vertex_t> result;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[v][i] > 0) {
            result.push_back(i);
        }
    }
    return result;
}

vector<vertex_t> Graph::getPredecessors(vertex_t from) const {
    if (!validVertex(from))
        throw "Invalid vertex";

    vector<vertex_t> result;

    for (size_t i = 0; i < data.size(); i++)
        if (data[i][from] > 0)
            result.push_back(i);

    return result;
}

#endif