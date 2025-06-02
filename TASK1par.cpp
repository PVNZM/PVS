#include <iostream>
#include <fstream>
#include <omp.h>

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
    }
    file.close();

    int sum = 0;
    #pragma omp parallel
    {
        int localSum = 0;
        #pragma omp for
        for (int i = 0; i < index; i++) {
            localSum += array[i];
        }
        #pragma omp critical
        sum += localSum;
    }

    std::cout << "Сумма элементов: " << sum << std::endl;
    return 0;
}
