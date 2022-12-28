#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "SkipList.hpp"

template <typename T>
void search(SkipListEl<T> *start, size_t key, vector<T> &result) {
    SkipListEl<T> *curr = start;
    while (curr != nullptr && curr->mNext != nullptr) {
        while (curr->mJump != nullptr && curr->mJump->mKey <= key) {
            curr = curr->mJump;
            result.push_back(curr->mTown);
        }
        if (curr->mKey == key) {
            break;
        } else {
            curr = curr->mNext;
            result.push_back(curr->mTown);
        }
    }
}

int main() {
    SkipList<string> s;
    string town;
    size_t n;

    cout << "Number of cities: ";
    cin >> n;

    // initialize the skip list
    for (size_t i = 0; i < n; i++) {
        cin >> town;
        s.pushBack(i, town);
    }

    pair<string, string> directLanes;
    cout << "Number of direct lanes: ";
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        cout << "From: ";
        cin >> directLanes.first;
        cout << '\n'
             << "To: ";
        cin >> directLanes.second;
        s.linkTowns(directLanes.first, directLanes.second);
    }
    cout << endl;

    vector<string> townsToVisit;
    string toVisit;
    cout << "Start gara:";
    cin >> toVisit;
    townsToVisit.push_back(toVisit);

    cout << "Number of towns to visit: ";
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        cin >> toVisit;
        townsToVisit.push_back(toVisit);
    }

    cout << "End gara: ";
    cin >> toVisit;
    townsToVisit.push_back(toVisit);

    vector<string> result;
    result.push_back(townsToVisit.front());

    for (size_t i = 0; i < townsToVisit.size() - 1; i++) {
        search(s.getElem(townsToVisit[i]), s.getKey(townsToVisit[i + 1]), result);
    }

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << ' ';
    }

    return 0;
}