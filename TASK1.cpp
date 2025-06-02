#include <iostream>
#include <fstream>

const int SIZE = 500000;

int main() {
    std::ifstream file("array.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла :(" << std::endl;
        return 1;
    }

    int array[SIZE];
    int index = 0;

    while (index < SIZE && file >> array[index]) {
        index++;
   
