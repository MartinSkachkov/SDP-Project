#ifndef _BOX_LIST_HPP_
#define _BOX_LIST_HPP_
#include "Box.hpp"

/// @brief BoxList is the class which contains all different boxes that can be found in the file (in out example they are 10)
class BoxList {
private:
    vector<Box *> boxList;

    void free();
    void copy(const BoxList &other);

public:
    BoxList(const int &size = 0);
    BoxList(const Box &other);
    BoxList &operator=(const BoxList &other);
    ~BoxList();

    void addBox(const string &label);
    void addInnerBox(const string &label, const string &parent);
    void addSouvenir(const string &label, const string &souvenir);
    void optimise();
    void printList() const;
};

void BoxList::free() {
    for (auto b : boxList)
        delete b;
}

void BoxList::copy(const BoxList &other) {
    for (size_t i = 0; i < other.boxList.size(); i++) {
        boxList.push_back(other.boxList[i]->copyBox());
    }
}

BoxList::BoxList(const int &size) {
    // от тук прочетох как работи reserve и защо да използвам него:
    // https://myprogrammingexperiencecom.wordpress.com/2019/05/09/reserve-vs-resize-in-c-stdvector/
    boxList.reserve(size);
}

BoxList::BoxList(const Box &other) {
    copy(other);
}

BoxList &BoxList::operator=(const BoxList &other) {
    if (this == &other) {
        return *this;
    }
    free();
    copy(other);
    return *this;
}

BoxList::~BoxList() {
    free();
}

void BoxList::addBox(const string &label) {
    boxList.push_back(new Box(label));
}

/// @brief this function links two boxes in parent -> child relation
void BoxList::addInnerBox(const string &label, const string &parent) {
    bool done = false;
    for (size_t i = 0; i < boxList.size(); i++) {
        // first we find the parent
        if (boxList[i]->getLabel() == parent) {
            // once found, then we search again for the subbox we want to add(it's name)
            for (size_t j = 0; j < boxList.size(); j++) {
                if (boxList[j]->getLabel() == label) {
                    // once we found the desired box to add, we push_back it to the parent
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