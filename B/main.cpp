#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
using namespace std;

/// Задачата не работи изцяло коректно. Намира правилното време, за което да се направи разходката в графа, но понеже използвам set за пазенето на посетените
/// върхове, то не изрежда последователността и бройката коректно накрая.
/// Ресурси, които съм чел и използвал за решаването на задачата:
/// идеята за обхождане на граф в който може да повтаряме върхове - https://www.techiedelight.com/least-cost-path-digraph-source-destination-m-edges/
/// идеята за обхождане на граф в който може да повтаряме върхове - https://www.techiedelight.com/maximum-cost-path-graph-source-destination/
/// идеята за обхождане на граф в който може да повтаряме върхове - https://stackoverflow.com/questions/13718869/traverse-a-graph-from-a-starting-point-and-ending-at-the-starting-point-c
/// map & set - https://github.com/stoychoX/Data-structures-and-algorithms/tree/main/Seminar10

/// @brief Path struct keeps track of the visited vertices while we are traversing the graph to find the most optimal way
struct Path {
    vertex_t v;
    weight_t length;
    set<vertex_t> visited;
};

/// @brief this function is a modified version of BFS where we allow traversing a given vertex several times (the idea is taken from the above sources)
/// @param g the graph we are traversing
/// @param start 0 -> Railway station
/// @param threshold this is the time limit taken from the file (in our exemple - 68)
/// @param best_path helps me to store the the most optimal way (more precisely we store it in the set<vertex_t> visited)
/// Причината, заради която пазя посетените върхове в set, е че по този начин не зацикля BFS-a. Пробвах с вектор, но зацикляше.
void BFS(const Graph &g, vertex_t start, weight_t threshold, Path &best_path) {
    queue<Path> q;
    // започваме от start, пътя все ище ни е 0, и не сме посетили нито един връх
    q.push({start, 0, {}});

    while (!q.empty()) {
        Path cur = q.front();
        q.pop();

        for (auto &succ : g.getSuccessors(cur.v)) // vector<vertex_t> {1,5}
        {
            Path new_path = cur;
            // тъй като пътя само нараства, това гарантира, че ще имаме невалидни обхождания
            new_path.length += g.getWeight(cur.v, succ);
            // затова ако е невалиден пътя то:
            if (new_path.length > threshold) {
                // премахваме го като опция
                continue;
            }

            // ако обаче все още е валиден път, то се придвижваме с един връх напред
            new_path.v = succ;
            // маркираме го като обходен
            new_path.visited.insert(succ);
            // по-късно в итерацията ще гледаме дали от него -> нататък ще има валиден път
            q.push(new_path);

            if (new_path.v == start && new_path.visited.size() > best_path.visited.size()) {
                best_path = new_path;
            }
        }
    }
}

/// @brief function which reads the data from the file
/// @param file file we are reading from
/// @param numToLandmark на всяко число съпоставям съответната забележителност. Това го правя, защото в по-късен етап, като трябва да взимам наследниците на даден връх
/// getSuccessors(v) ще бъде много по-лесно чрез int-ове да проверявам дали има ребро между два върха в матрицата.
/// @return не изкрава правилно пътя, но правилно калкулира времето за което се "извървява" този път.
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

    /// @brief запазваме във вектор всички забележителности, но с повторение
    for (size_t i = 0; i < e; i++) {
        file >> from >> to >> weight;
        landmarks.push_back(from);
        landmarks.push_back(to);
    }

    /// @brief премахваме повторенията
    /// @return landmarks = Railstation ArtGallery RomanStadium DzhumayaSquare HistoricalMuseum AntiqueTheatre
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
    file.seekg(3); // set the pointer in the file to point to the strings (a.k.a skip r & k part in the file)

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
    /// @brief we map back from vetex indexes (0, 1 ...) -> names (strings)
    /// @return Railstation, ArtGallery, RomanStadium, DzhumayaSquare, AntiqueTheatre
    for (const auto &v : best_path.visited) {
        cout << numToLandmark[v] << "\n";
    }
    cout << numToLandmark[0] << '\n'; // since we need to go back to where we started, just print the finish point

    file.close();
    return 0;
}