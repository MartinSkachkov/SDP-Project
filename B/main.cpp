#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;

struct Path {
    vertex_t v;
    weight_t length;
    set<vertex_t> visited;
};

void BFS(const Graph &g, vertex_t start, weight_t threshold, Path &best_path) {
    queue<Path> q;
    q.push({start, 0, {}});

    while (!q.empty()) {
        Path cur = q.front();
        q.pop();

        for (auto &succ : g.getSuccessors(cur.v)) // vector<vertex_t> {1,5}
        {
            Path new_path = cur;
            new_path.length += g.getWeight(cur.v, succ);
            if (new_path.length > threshold) {
                continue;
            }

            new_path.v = succ;
            new_path.visited.insert(succ);
            q.push(new_path);

            if (new_path.v == start && new_path.visited.size() > best_path.visited.size()) {
                best_path = new_path;
            }
        }
    }
}

int main() {
    /* ifstream file("map.txt");

     if (!file.is_open()) {
         cout << "Error!" << endl;
         return -1;
     }*/

    Graph g(6);
    g.addEdge(0, 1, 26);
    g.addEdge(1, 2, 7);
    g.addEdge(2, 3, 12);
    g.addEdge(1, 3, 14);
    g.addEdge(3, 4, 18);
    g.addEdge(1, 4, 5);
    g.addEdge(5, 4, 2);
    g.addEdge(5, 0, 20);

    // print vertices and it's adjacent
    for (size_t i = 0; i < 6; i++) {
        vector<vertex_t> successors = g.getSuccessors(i);
        cout << "vertex: " << i << endl;
        for (size_t i = 0; i < successors.size(); i++) {
            cout << successors[i] << ' ';
        }
        cout << endl;
    }

    Path best_path;
    BFS(g, 0, 68, best_path);

    cout << "In " << best_path.length << " minutes visited " << best_path.visited.size() << " places:\n";
    for (auto &v : best_path.visited) {
        cout << v << "\n";
    }
    cout << '0';
    // for (size_t i = 0; i < v.size(); i++)
    //{
    //	cout << v[i];
    // }
    //  file.close();
    return 0;
}