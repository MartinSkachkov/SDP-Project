#include "SkipList.hpp"
#include <string>
#include <vector>

/// @brief this function finds the shortest path between two towns
/// first iteration will look like this (we start from Sofia and want to go to Plovdiv):
/// @param start Sofia
/// @param key 2 (which is the key of Plovdiv)
/// @param result Sofia Pazardzhik Plovdiv is the most efficient path in this example so we save it to the result. In the next iteration we will go from Plovdiv to 4 (StaraZagora)
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
    string town;
    size_t n;

    cout << "Number of towns through which the train passes: ";
    cin >> n;

    /// @brief first we initialize the skip list, 'i' represents the town's uniqie key
    /// @return |0|Sofia|NIL| -> |1|Pazardzhik|NIL| -> |2|Plovdiv|NIL| -> |3|Dimitrovgrad|NIL| -> |4|StaraZagora|NIL| -> |5|NovaZagora|NIL| -> |6|Yambol|NIL| -> |7|Karnobat|NIL| -> |8|Burgas|NIL| -> NIL
    cout << "Enter the towns: ";
    for (size_t i = 0; i < n; i++) {
        cin >> town;
        list.pushBack(i, town);
    }
    cout << '\n';

    pair<string, string> directLanes;
    cout << "Number of direct lanes between two towns: ";
    cin >> n;

    /// @brief  initialize the direct lanes between two towns
    /// @return |0|Sofia|Plovdiv| -> |1|Pazardzhik|NIL| -> |2|Plovdiv|NovaZagora| -> |3|Dimitrovgrad|NovaZagora| -> |4|StaraZagora|Yambol| -> |5|NovaZagora|Burgas| -> |6|Yambol|NIL| -> |7|Karnobat|NIL| -> |8|Burgas|NIL| -> NIL
    cout << "Enter the direct lanes:\n";
    for (size_t i = 0; i < n; i++) {
        cout << "From: ";
        cin >> directLanes.first;
        cout << "To: ";
        cin >> directLanes.second;
        list.linkTowns(directLanes.first, directLanes.second);
    }
    cout << '\n';

    vector<string> townsToVisit;
    string toVisit;

    /// @brief we need to add our starting destination to the places we want to visit
    /// @return townsToVisit = Sofia
    townsToVisit.push_back(list.front());

    cout << "Number of towns to visit: ";
    cin >> n;

    /// @brief add the mid towns between the start and ending point
    /// @return townsToVisit = Sofia Plovdiv StaraZagora Yambol
    cout << "Desired towns to visit: ";
    for (size_t i = 0; i < n; i++) {
        cin >> toVisit;
        townsToVisit.push_back(toVisit);
    }

    /// @brief add the final destination
    /// @return townsToVisit = Sofia Plovdiv StaraZagora Yambol Burgas
    townsToVisit.push_back(list.back());

    vector<string> result;
    /// @brief since result will contain the solution we need to add the starting destination to it
    /// @return result = Sofia
    result.push_back(townsToVisit.front());

    /// @brief find the most optimal way between two given towns by performing a search of the unique key of the given town
    /// @return result = Sofia Plovdiv Dimitrovgrad StaraZagora Yambol Karnobat Burgas
    for (size_t i = 0; i < townsToVisit.size() - 1; i++) {
        search(list.getElem(townsToVisit[i]), list.getKey(townsToVisit[i + 1]), result);
    }

    cout << "Result: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << ' ';
    }

    return 0;
}