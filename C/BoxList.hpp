#ifndef _BOX_LIST_HPP_
#define _BOX_LIST_HPP_
#include "Box.hpp"

class BoxList {
private:
    vector<Box *> boxList;

public:
    BoxList(const int &size = 0);

    void addBox(const string &label);
    void addInnerBox(const string &label, const string &parent);
    void addSouvenir(const string &label, const string &souvenir);
    void optimise();
    void printList() const;
};

BoxList::BoxList(const int &size) {
    boxList.reserve(size);
}

void BoxList::addBox(const string &label) {
    boxList.push_back(new Box(label));
}

void BoxList::addInnerBox(const string &label, const string &parent) {
    bool done = false;
    for (size_t i = 0; i < boxList.size(); i++) {
        if (boxList[i]->getLabel() == parent) {
            for (size_t j = 0; j < boxList.size(); j++) {
                if (boxList[j]->getLabel() == label) {
                    boxList[i]->setInnerBox(boxList[j]);
                    done = true;
                    break;
                }
            }
        }
        if (done) {
            break;
        }
    }
}

void BoxList::addSouvenir(const string &label, const string &souvenir) {
    for (size_t i = 0; i < boxList.size(); i++) {
        if (boxList[i]->getLabel() == label) {
            boxList[i]->setSouvenir(souvenir);
        }
    }
}

void BoxList::optimise() {
    for (size_t i = 0; i < boxList.size(); i++) {
        if (boxList[i]->getSouvenirs().empty()) {
            // https://iq.opengenus.org/ways-to-remove-elements-from-vector-cpp/
            boxList.erase(boxList.begin() + i);
        }
    }
}

void BoxList::printList() const {
    for (size_t i = 0; i < boxList.size(); i++) {
        boxList[i]->printBox();
        cout << '\n';
    }
    cout << '\n';
}

#endif