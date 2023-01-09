#ifndef _BOX_HPP_
#define _BOX_HPP_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// @brief Box class represents how a single box will look like
class Box {
private:
    string label;
    vector<string> souvenirs;
    vector<Box *> boxes;

    void free();
    void copy(const Box &other);

public:
    Box(const string &l = "", const int &s = 0, const int &b = 0);
    Box(const Box &other);
    Box &operator=(const Box &other);
    ~Box();

    void setSouvenir(const string &s);
    void setInnerBox(Box *b);
    string getLabel() const;
    vector<string> getSouvenirs() const;
    void printBox() const;
    Box *copyBox();
};

void Box::free() {
    for (auto b : boxes)
        delete b;
}

void Box::copy(const Box &other) {
    label = other.label;
    souvenirs = other.souvenirs;
    for (size_t i = 0; i < other.boxes.size(); i++) {
        boxes.push_back(other.boxes[i]->copyBox());
    }
}

Box *Box::copyBox() {
    return new Box(*this);
}

Box::Box(const string &l, const int &s, const int &b) {
    // от тук прочетох как работи reserve и защо да използвам него:
    // https://myprogrammingexperiencecom.wordpress.com/2019/05/09/reserve-vs-resize-in-c-stdvector/
    label = l;
    souvenirs.reserve(s);
    boxes.reserve(b);
}

Box::Box(const Box &other) {
    copy(other);
}

Box &Box::operator=(const Box &other) {
    if (this == &other) {
        return *this;
    }
    free();
    copy(other);
    return *this;
}

Box::~Box() {
    free();
}

void Box::setSouvenir(const string &s) {
    souvenirs.push_back(s);
}

void Box::setInnerBox(Box *b) {
    boxes.push_back(b);
}

string Box::getLabel() const {
    return label;
}

vector<string> Box::getSouvenirs() const {
    return souvenirs;
}

void Box::printBox() const {
    cout << "Label: " << label << '\n';

    if (souvenirs.empty()) {
        cout << "No souvenirs!";
    } else {
        cout << "Souvenirs: ";
        for (size_t i = 0; i < souvenirs.size(); i++) {
            cout << souvenirs[i] << ' ';
        }
    }
    cout << '\n';

    if (boxes.empty()) {
        cout << "No inner boxes!";
    } else {
        cout << "Inner boxes: ";
        for (size_t i = 0; i < boxes.size(); i++) {
            cout << boxes[i]->label << ' ';
        }
    }
    cout << '\n';
}

#endif