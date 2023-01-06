#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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

Path findOptimalWay(ifstream &file, map<size_t, string> &numToLandmark) {
    size_t v, e;

    file >> v >> e;
    cout << "Graph will have " << v << " vertices and " << e << " edges.\n";
    Graph g(v);
    cout << '\n';

    map<string, size_t> landmarkToNum;
    vector<string> landmarks;
    string from, to;
    size_t weight;

    for (size_t i = 0; i < e; i++) {
        file >> from >> to >> weight;
        landmarks.push_back(from);
        landmarks.push_back(to);
    }

    // removing duplicating strings
    // https://www.techiedelight.com/remove-duplicates-vector-cpp/
    auto end = landmarks.end();
    auto begin = landmarks.begin();
    for (auto it = begin; it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
    landmarks.erase(end, landmarks.end());

    size_t counter = 0;
    cout << "Landmarks that can be visited in this town:\n";
    for (const auto &landmark : landmarks) {
        cout << landmark << "\n";
        landmarkToNum[landmark] = counter;
        numToLandmark[counter] = landmark;
        counter++;
    }
    cout << "\n";

    cout << "Number representation -> Landmark:\n";
    for (const auto &elem : numToLandmark) {
        cout << elem.first << " -> " << elem.second << "\n";
    }
    cout << '\n';

    size_t timeLimit;
    file >> timeLimit;
    file.seekg(3); // set the pointer in the file to point to the strings (a.k.a skip r & k)

    for (size_t i = 0; i < e; i++) {
        file >> from >> to >> weight;
        g.addEdge(landmarkToNum[from], landmarkToNum[to], weight);
    }

    cout << "Adjacency list for each vertex:\n";
    for (size_t i = 0; i < 6; i++) {
        vector<vertex_t> successors = g.getSuccessors(i);
        cout << "vertex: " << i << '\n';
        for (size_t i = 0; i < successors.size(); i++) {
            cout << successors[i] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

    Path best_path;
    BFS(g, 0, timeLimit, best_path);

    return best_path;
}

int main() {
    ifstream file("map.txt");

    if (!file.is_open()) {
        cout << "Couldn't open the file!" << '\n';
        return -1;
    }

    map<size_t, string> numToLandmark;
    Path best_path = findOptimalWay(file, numToLandmark);
    cout << "In " << best_path.length << " minutes visited " << best_path.visited.size() << " places:\n";
    for (const auto &v : best_path.visited) {
        cout << numToLandmark[v] << "\n";
    }
    cout << numToLandmark[0] << '\n';

    file.close();
    return 0;
}