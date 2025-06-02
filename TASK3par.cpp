#include <iostream>
#include <fstream>
#include <array>
#include <stdexcept>
#include <limits>
#include <omp.h>

const size_t SIZE = 500000;

void loadArrayFromFile(const std::string& filename, std::array<double, SIZE>& arr) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    for (size_t i = 0; i < SIZE; ++i) {
        if (!(file >> arr[i])) {
            throw std::runtime_error("Ошибка чтения данных из файла: " + filename);
        }
    }
}

void printArray(const std::array<double, SIZE>& arr) {
    for (size_t i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "..." << std::endl;
}

int main() {
    std::array<double, SIZE> array1;
    std::array<double, SIZE> array2;
    std::array<double, SIZE> resultAdd;
    std::array<double, SIZE> resultSub;
    std::array<double, SIZE> resultMul;
    std::array<double, SIZE> resultDiv;

    try {
        loadArrayFromFile("array1.txt", array1);
        loadArrayFromFile("array2.txt", array2);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Выполнение операций с параллелизацией
    #pragma omp parallel for
    for (size_t i = 0; i < SIZE; ++i) {
        resultAdd[i] = array1[i] + array2[i];
        resultSub[i] = array1[i] - array2[i];
        resultMul[i] = array1[i] * array2[i];

        // Проверка на деление на ноль
        if (array2[i] != 0) {
            resultDiv[i] = array1[i] / array2[i];
        } else {
            resultDiv[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    // Печать результатов
    std::cout << "Сложение (первые 10 элементов): ";
    printArray(resultAdd);

    std::cout << "Вычитание (первые 10 элементов): ";
    printArray(resultSub);

    std::cout << "Умножение (первые 10 элементов): ";
    printArray(resultMul);

    std::cout << "Деление (первые 10 элементов): ";
    printArray(resultDiv);

    return 0;
}
