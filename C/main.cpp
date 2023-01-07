#include "BoxList.hpp"
#include <fstream>

void initializeBoxList(ifstream &file) {
    size_t totalBoxCount;
    file >> totalBoxCount;
    BoxList boxList(totalBoxCount);

    string boxLabel;
    file.seekg(4); // put the file get pointer at the correct position in the file

    // https://stackoverflow.com/questions/66602986/getting-first-word-of-each-line-in-file
    for (size_t i = 0; i < totalBoxCount; i++) {
        getline(file, boxLabel);
        boxList.addBox(boxLabel.substr(0, boxLabel.find_first_of(" ")));
    }

    file.seekg(4); // reset the file get pointer
    size_t boxCount;
    size_t souvenirsCount;
    string souvenirName;
    string parentBox;

    for (size_t i = 0; i < totalBoxCount; i++) {
        file >> parentBox >> souvenirsCount;
        for (size_t i = 0; i < souvenirsCount; i++) {
            file >> souvenirName;
            boxList.addSouvenir(parentBox, souvenirName);
        }

        file >> boxCount;
        for (size_t i = 0; i < boxCount; i++) {
            file >> boxLabel;
            boxList.addInnerBox(boxLabel, parentBox);
        }
    }

    boxList.printList();
    // boxList.optimise();
    // cout << "======================\n";
    // boxList.printList();
}

int main() {
    ifstream file("boxesList.txt");

    if (!file.is_open()) {
        cout << "Couldn't open the file!" << '\n';
        return -1;
    }

    initializeBoxList(file);

    file.close();
    return 0;
}
