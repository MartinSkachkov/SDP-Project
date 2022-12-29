#include "SkipList.hpp"
#include <string>
#include <vector>

template <typename T>
void search(const SkipListEl<T> *start, size_t key, vector<T> &result) {
    const SkipListEl<T> *curr = start;

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
    SkipList<string> list;

    ///////////////////////////////////////////////////////////////
    string town;
    size_t n;

    cout << "Number of towns through which the train passes: ";
    cin >> n;

    // initialize the skip list, 'i' represents the town's unique search key
    cout << "Enter the towns: ";
    for (size_t i = 0; i < n; i++) {
        cin >> town;
        list.pushBack(i, town);
    }
    cout << '\n';
    ///////////////////////////////////////////////////////////////

    pair<string, string> directLanes;
    cout << "Number of direct lanes between two towns: ";
    cin >> n;

    // initialize the direct lanes between two towns
    cout << "Enter the direct lanes:\n";
    for (size_t i = 0; i < n; i++) {
        cout << "From: ";
        cin >> directLanes.first;
        cout << "To: ";
        cin >> directLanes.second;
        list.linkTowns(directLanes.first, directLanes.second);
    }
    cout << '\n';
    ///////////////////////////////////////////////////////////////

    vector<string> townsToVisit;
    string toVisit;

    townsToVisit.push_back(list.front());

    cout << "Number of towns to visit: ";
    cin >> n;

    // initialize the desired towns to visit
    cout << "Desired towns to visit: ";
    for (size_t i = 0; i < n; i++) {
        cin >> toVisit;
        townsToVisit.push_back(toVisit);
    }

    townsToVisit.push_back(list.back());
    ///////////////////////////////////////////////////////////////

    vector<string> result;
    result.push_back(townsToVisit.front());

    // find the most optimal way between two given towns by performing a search of the unique key of the given town
    for (size_t i = 0; i < townsToVisit.size() - 1; i++) {
        search(list.getElem(townsToVisit[i]), list.getKey(townsToVisit[i + 1]), result);
    }

    cout << "Result: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << ' ';
    }

    return 0;
}