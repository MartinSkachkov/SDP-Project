#include "BoxList.hpp"
#include <fstream>

/// В тази задача успях да реализирам само функцията, която по подаден входен файл създава списък от кутии
/// отговарящи на описанието във файла. (пробвах се да направя и функцията, която оптимизира броя на използваните кутии, но не успях)

/// @brief this is the function which reads from a file, initializes the data and prints it
/// @param file input file
void initializeBoxList(ifstream &file) {
    size_t totalBoxCount;
    file >> totalBoxCount;
    BoxList boxList(totalBoxCount);

    string boxLabel;
    file.seekg(4); // put the file get pointer at the correct position in the file

    // първоначално инициализирам boxList, като в него вкарвам всички възможни различни кутии (в нашия пример 10 бр.)
    // за взимането на първата дума от ред във файл съм гледал от тук:
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

    // след което инициализирам отделните кутии и ги "навързвам" една към друга спрямо това една кутия какви подкутии има
    for (size_t i = 0; i < totalBoxCount; i++) {
        file >> parentBox >> souvenirsCount;
        for (size_t i = 0; i < souvenirsCount; i++) {
            file >> souvenirName;
            boxList.addSouvenir(parentBox, souvenirName);
        }

        // тук става "навързването"
        file >> boxCount; // брой подкутии
        for (size_t i = 0; i < boxCount; i++) {
            file >> boxLabel;
            boxList.addInnerBox(boxLabel, parentBox);
        }
    }

    boxList.printList();
    // опитът за оптимизация (не работи коректно):
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
