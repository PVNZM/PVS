#include <iostream>
#include <fstream>
#include <array>
#include <limits>
#include <stdexcept>
#include <omp.h>

const size_t ROWS = 800;
const size_t COLS = 800;

void loadArrayFromFile(const std::string& filename, std::array<std::array<double, COLS>, ROWS>& arr) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            if (!(file >> arr[i][j])) {
                throw std::runtime_error("Ошибка чтения данных из файла: " + filename);
            }
        }
    }
}

void printArray(const std::array<std::array<double, COLS>, ROWS>& arr) {
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "..." << std::endl;
    }
}

int main() {
    std::array<std::array<double, COLS>, ROWS> matrix1;
    std::array<std::array<double, COLS>, ROWS> matrix2;
    std::array<std::array<double, COLS>, ROWS> resultAdd;
    std::array<std::array<double, COLS>, ROWS> resultSub;
    std::array<std::array<double, COLS>, ROWS> resultMul;
    std::array<std::array<double, COLS>, ROWS> resultDiv;

    try {
        loadArrayFromFile("matrix1.txt", matrix1);
        loadArrayFromFile("matrix2.txt", matrix2);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    #pragma omp parallel for
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            resultAdd[i][j] = matrix1[i][j] + matrix2[i][j];
            resultSub[i][j] = matrix1[i][j] - matrix2[i][j];
            resultMul[i][j] = matrix1[i][j] * matrix2[i][j];

            if (matrix2[i][j] != 0) {
                resultDiv[i][j] = matrix1[i][j] / matrix2[i][j];
            } else {
                resultDiv[i][j] = std::numeric_limits<double>::quiet_NaN();
            }
        }
    }

    std::cout << "First 10x10 elements of addition result:" << std::endl;
    printArray(resultAdd);

    return 0;
}
