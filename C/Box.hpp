#ifndef _BOX_HPP_
#define _BOX_HPP_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Box {
private:
    string label;
    vector<string> souvenirs;
    vector<Box *> boxes;

public:
    Box(const string &l = "", const int &s = 0, const int &b = 0);

    void setSouvenir(const string &s);
    void setInnerBox(Box *b);
    string getLabel() const;
    vector<string> getSouvenirs() const;
    void printBox() const;
};

Box::Box(const string &l, const int &s, const int &b) {
    label = l;
    souvenirs.reserve(s);
    boxes.reserve(b);
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